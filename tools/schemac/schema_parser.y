// ---------------------------------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------------------------------
%skeleton "lalr1.cc"
%require "3.0.4"
// ---------------------------------------------------------------------------------------------------
// Write a parser header file
%defines
// Define the parser class name
%define api.parser.class {SchemaParser}
// Create the parser in our namespace
%define api.namespace { imlab::schemac }
// Use C++ variant to store the values and get better type warnings (compared to "union")
%define api.value.type variant
// With variant-based values, symbols are handled as a whole in the scanner
%define api.token.constructor
// Prefix all tokens
%define api.token.prefix {SCHEMA_}
// Check if variants are constructed and destroyed properly
%define parse.assert
// Trace the parser
%define parse.trace
// Use verbose parser errors
%define parse.error verbose
// Enable location tracking.
%locations
// Pass the compiler as parameter to yylex/yyparse.
%param { imlab::schemac::SchemaParseContext &sc }
// ---------------------------------------------------------------------------------------------------
// Added to the header file and parser implementation before bison definitions.
// We include string for string tokens and forward declare the SchemaParseContext.
%code requires {
#include <string>
#include "imlab/schemac/schema_parse_context.h"
}
// ---------------------------------------------------------------------------------------------------
// Import the compiler header in the implementation file
%code {
imlab::schemac::SchemaParser::symbol_type yylex(imlab::schemac::SchemaParseContext& sc);
}
// ---------------------------------------------------------------------------------------------------
// Token definitions
%token <int>                INTEGER_VALUE    "integer_value"
%token <std::string>        IDENTIFIER       "identifier"

%token KSTLUNORDEREDMAP	"kSTLUnorderedMap"
%token KSTLMAP		"kSTLMap"
%token KSTXMAP		"btree_map"

%token LCB              "left_curly_brackets"
%token LRB              "left_round_brackets"
%token RCB              "right_curly_brackets"
%token RRB              "right_round_brackets"
%token DQOUTES          "double_quotes"
%token SEMICOLON        "semicolon"
%token COMMA            "comma"

%token INTEGER          "integer"
%token CHAR             "char"
%token VARCHAR          "varchar"
%token NUMERIC          "numeric"
%token TIMESTAMP        "timestamp"
%token NOTNULL          "not null"
%token INDEX            "index"
%token TABLE            "table"
%token CREATE           "create"

%token PRIMARY          "primary"
%token KEY           	"key"

%token ON               "on"
%token WITH             "with"
%token EQL              "equals"
%token EOF 0            "eof"
// ---------------------------------------------------------------------------------------------------
%type <imlab::schemac::Schema> schema_declaration;
%type <imlab::schemac::Table> parse_table;
%type <imlab::schemac::Index> parse_index;
%type <std::vector<imlab::schemac::Column>> column_declaration_list;
%type <imlab::schemac::Column> column_declaration;
%type <imlab::schemac::Type> column_type;
%type <std::vector<imlab::schemac::Column>> primary_key_list;
%type <imlab::schemac::Column> pk_column_ref;
%type <imlab::schemac::IndexType> index_type;
// ---------------------------------------------------------------------------------------------------
%%

%start schema_statement_list;

schema_statement_list:
    schema_declaration                                                { sc.defineSchema($1); }
 |  %empty
    ;

schema_declaration:
    schema_declaration parse_table                                                          { $1.tables.push_back($2); std::swap($$, $1); }
 |  schema_declaration parse_index                                                          { $1.indexes.push_back($2); std::swap($$, $1); }
 |  parse_index                                                                             { $$.indexes.push_back($1); }
 |  parse_table										    { $$.tables.push_back($1); }
    ;

parse_table:
    CREATE TABLE IDENTIFIER LRB column_declaration_list RRB SEMICOLON                						 				{ $$ = sc.defineTable($3, $5, std::vector<imlab::schemac::Column>(), imlab::schemac::IndexType(kSTLMap) ); }
 |  CREATE TABLE DQOUTES IDENTIFIER DQOUTES LRB column_declaration_list RRB SEMICOLON       		 			 				{ $$ = sc.defineTable($4, $7, std::vector<imlab::schemac::Column>(), imlab::schemac::IndexType(kSTLMap) ); }
 |  CREATE TABLE IDENTIFIER LRB column_declaration_list RRB WITH LRB IDENTIFIER EQL index_type RRB SEMICOLON							{ $$ = sc.defineTable($3, $5, std::vector<imlab::schemac::Column>(), $11 ); }
 |  CREATE TABLE DQOUTES IDENTIFIER DQOUTES LRB column_declaration_list RRB WITH LRB IDENTIFIER EQL index_type RRB SEMICOLON            			{ $$ = sc.defineTable($4, $7, std::vector<imlab::schemac::Column>(), $13 ); }
 |  CREATE TABLE IDENTIFIER LRB column_declaration_list COMMA PRIMARY KEY LRB primary_key_list RRB RRB SEMICOLON								{ $$ = sc.defineTable($3, $5, $10, imlab::schemac::IndexType(kSTLMap) ); }
 |  CREATE TABLE DQOUTES IDENTIFIER DQOUTES LRB column_declaration_list COMMA PRIMARY KEY LRB primary_key_list RRB RRB SEMICOLON						{ $$ = sc.defineTable($4, $7, $12, imlab::schemac::IndexType(kSTLMap) ); }
 |  CREATE TABLE IDENTIFIER LRB column_declaration_list COMMA PRIMARY KEY LRB primary_key_list RRB RRB WITH LRB IDENTIFIER EQL index_type RRB SEMICOLON			{ $$ = sc.defineTable($3, $5, $10, $17 ); }
 |  CREATE TABLE DQOUTES IDENTIFIER DQOUTES LRB column_declaration_list COMMA PRIMARY KEY LRB primary_key_list RRB RRB WITH LRB IDENTIFIER EQL index_type RRB SEMICOLON	{ $$ = sc.defineTable($4, $7, $12, $19 ); }
    ;

index_type:
    KSTLUNORDEREDMAP															{ $$ = imlab::schemac::IndexType(kSTLUnorderedMap);}
 |  KSTLMAP																{ $$ = imlab::schemac::IndexType(kSTLMap);}
 |  KSTXMAP																{ $$ = imlab::schemac::IndexType(kSTXMap);}
    ;

parse_index:
    CREATE INDEX IDENTIFIER ON IDENTIFIER LRB primary_key_list RRB SEMICOLON                                                         { $$ = sc.defineIndex($3, $5, $7, imlab::schemac::IndexType(kSTLMap) ); }
 |  CREATE INDEX IDENTIFIER ON DQOUTES IDENTIFIER DQOUTES LRB primary_key_list RRB SEMICOLON                                         { $$ = sc.defineIndex($3, $6, $9, imlab::schemac::IndexType(kSTLMap) ); }
 |  CREATE INDEX IDENTIFIER ON IDENTIFIER LRB primary_key_list RRB WITH LRB IDENTIFIER EQL index_type RRB SEMICOLON                      { $$ = sc.defineIndex($3, $5, $7, $13 ); }
 |  CREATE INDEX IDENTIFIER ON DQOUTES IDENTIFIER DQOUTES LRB primary_key_list RRB WITH LRB IDENTIFIER EQL index_type RRB SEMICOLON      { $$ = sc.defineIndex($3, $6, $9, $15 ); }
    ;

primary_key_list:
    primary_key_list COMMA pk_column_ref					    { $1.push_back($3); std::swap($$, $1); }
 |  pk_column_ref								    { $$ = std::vector<imlab::schemac::Column> { $1 }; }
 |  %empty									    {}
    ;

pk_column_ref:
    IDENTIFIER									    { $$.id = $1; $$.type = Type::Integer(); }
    ;

column_declaration_list:
    column_declaration_list COMMA column_declaration                                { $1.push_back($3); std::swap($$, $1); }
 |  column_declaration                                                              { $$ = std::vector<imlab::schemac::Column> { $1 }; }
 |  %empty                                                                          {}
    ;

column_declaration:
    IDENTIFIER column_type NOTNULL 	                                            { $$.id = $1; $$.type = $2; }
    ;

column_type:
    INTEGER                                                                         { $$ = Type::Integer(); }
 |  CHAR LRB INTEGER_VALUE RRB                                                      { $$ = Type::Char($3); }
 |  VARCHAR LRB INTEGER_VALUE RRB                                                   { $$ = Type::Varchar($3); }
 |  NUMERIC LRB INTEGER_VALUE COMMA INTEGER_VALUE RRB                               { $$ = Type::Numeric($3, $5); }
 |  TIMESTAMP                                                                       { $$ = Type::Timestamp(); }
    ;

%%
// ---------------------------------------------------------------------------------------------------
// Define error function
void imlab::schemac::SchemaParser::error(const location_type& l, const std::string& m) {
    sc.Error(l.begin.line, l.begin.column, m);
}
// ---------------------------------------------------------------------------------------------------