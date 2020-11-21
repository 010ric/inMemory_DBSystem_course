// ---------------------------------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------------------------------
#include "imlab/schemac/schema_parse_context.h"
#include "./gen/schema_parser.h"
#include <sstream>
#include <unordered_set>
#include "imlab/infra/error.h"
// ---------------------------------------------------------------------------------------------------
using SchemaParseContext = imlab::schemac::SchemaParseContext;
using Table = imlab::schemac::Table;
using Schema = imlab::schemac::Schema;
using Type = imlab::schemac::Type;
// ---------------------------------------------------------------------------------------------------
Type Type::Integer()    { Type t; t.tclass = kInteger; return t; }
Type Type::Timestamp()  { Type t; t.tclass = kTimestamp; return t; }
Type Type::Numeric(unsigned length, unsigned precision) {
    Type t;
    t.tclass = kNumeric;
    t.length = length;
    t.precision = precision;
    return t;
}
Type Type::Char(unsigned length) {
    Type t;
    t.tclass = kChar;
    t.length = length;
    return t;
}
Type Type::Varchar(unsigned length) {
    Type t;
    t.tclass = kVarchar;
    t.length = length;
    return t;
}
// ---------------------------------------------------------------------------------------------------
const char *Type::Name() const {
    switch (tclass) {
        case kInteger:      return "Integer";
        case kTimestamp:    return "Timestamp";
        case kNumeric:      return "Numeric";
        case kChar:         return "Character";
        case kVarchar:      return "Varchar";
        default:            return "Unknown";
    }
}
// ---------------------------------------------------------------------------------------------------
// Constructor
SchemaParseContext::SchemaParseContext(bool trace_scanning, bool trace_parsing)
    : trace_scanning_(trace_scanning), trace_parsing_(trace_parsing) {}
// ---------------------------------------------------------------------------------------------------
// Destructor
SchemaParseContext::~SchemaParseContext() {}
// ---------------------------------------------------------------------------------------------------
// Parse a string
Schema SchemaParseContext::Parse(std::istream &in) {
    beginScan(in);
    imlab::schemac::SchemaParser parser(*this);
    parser.set_debug_level(trace_parsing_);
    parser.parse();
    endScan();

    // TODO
<<<<<<< HEAD


    return parsedSchema;
=======
    return localSchema;
>>>>>>> 3a8b70a9d39c4edfe74fe00a010c18d81d728fc6
}
// ---------------------------------------------------------------------------------------------------
// Yield an error
void SchemaParseContext::Error(const std::string& m) {
    throw SchemaCompilationError(m);
}
// ---------------------------------------------------------------------------------------------------
// Yield an error
void SchemaParseContext::Error(uint32_t line, uint32_t column, const std::string &err) {
    std::stringstream ss;
    ss << "[ l=" << line << " c=" << column << " ] " << err << std::endl;
    throw SchemaCompilationError(ss.str());
}

// ---------------------------------------------------------------------------------------------------
<<<<<<< HEAD
// stage1 method
void imlab::schemac::SchemaParseContext::defineSchema(const imlab::schemac::Schema& schema) {
    std::cout << "Schema index size :  " << schema.indexes.size()<< std::endl;
    std::cout << "Schema table size :  " << schema.tables.size()<< std::endl;
    this->parsedSchema = schema;
=======
// Define a schema
void SchemaParseContext::defineSchema(const imlab::schemac::Schema& schema) {
    std::cout << "Schema index size :  " << schema.indexes.size()<< std::endl;
    std::cout << "Schema table size :  " << schema.tables.size()<< std::endl;
    localSchema = schema;
>>>>>>> 3a8b70a9d39c4edfe74fe00a010c18d81d728fc6
};
// ---------------------------------------------------------------------------------------------------
// Define a table
imlab::schemac::Table SchemaParseContext::defineTable(const std::string &table_name, const std::vector<imlab::schemac::Column> &columns,
        const std::vector<Column>& primary_key, const imlab::schemac::IndexType& index_type) {
    std::cout << "TableName:  " << table_name << std::endl;
    for (auto &decl : columns) {
        std::cout << "  Column Name:   " << decl.id << " and the Column Type " << decl.type.Name() << std::endl;
    }

    imlab::schemac::Table t1 = imlab::schemac::Table();
    t1.id = table_name;
    t1.columns = columns;
    t1.primary_key = primary_key;
    t1.index_type = index_type;
    return t1;
};
<<<<<<< HEAD
=======
// ---------------------------------------------------------------------------------------------------
// Define a index
imlab::schemac::Index SchemaParseContext::defineIndex(const std::string &index_name, const std::string &table_name,
        const std::vector<imlab::schemac::Column> &columns, const imlab::schemac::IndexType &index_type) {
    std::cout << "IndexName:  " << index_name << std::endl;
    for (auto &decl : columns) {
        std::cout << "  Column Name:   " << decl.id << " and the Column Type " << decl.type.Name() << std::endl;
    }

    imlab::schemac::Index i1 = imlab::schemac::Index();
    i1.id = index_name;
    i1.table_id = table_name;
    i1.columns = columns;
    i1.index_type = index_type;
    return i1;

};
>>>>>>> 3a8b70a9d39c4edfe74fe00a010c18d81d728fc6
// ---------------------------------------------------------------------------------------------------
