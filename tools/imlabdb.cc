// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------

#include <cstdint>
#include <chrono>  // NOLINT
#include <iostream>
#include <fstream>
#include "imlab/database.h"
#include "imlab/schema.h"
#include "imlab/infra/types.h"

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::time_point ClockTime;

namespace {

const int32_t kWarehouses = 5;

// Uniform random number
int32_t URand(int32_t min, int32_t max) {
    return (random() % (max - min + 1)) + min;
}

// Uniform random number
int32_t URandExcept(int32_t min, int32_t max, int32_t v) {
    if (max <= min)
        return min;
    int32_t r = (random() % (max - min)) + min;
    return (r >= v) ? (r + 1) : r;
}

// Non-uniform random number
int32_t NURand(int32_t A, int32_t x, int32_t y) {
    return ((((random() % A) | (random() % (y - x + 1) + x)) + 42) % (y - x + 1)) + x;
}

// Place a random order
void RandomNewOrder(imlab::Database &db) {
    Timestamp now(0);
    auto w_id = Integer(URand(1, kWarehouses));
    auto d_id = Integer(URand(1, 10));
    auto c_id = Integer(NURand(1023, 1, 3000));
    auto ol_cnt = Integer(URand(5, 15));

    std::array<Integer, 15> supware;
    std::array<Integer, 15> itemid;
    std::array<Integer, 15> qty;
    for (auto i = Integer(0); i < ol_cnt; i += Integer(1)) {
        supware[i.value] = (URand(1, 100) > 1) ? w_id : Integer(URandExcept(1, kWarehouses, w_id.value));
        itemid[i.value] = Integer(NURand(8191, 1, 100000));
        qty[i.value] = Integer(URand(1, 10));
    }

    db.NewOrder(w_id, d_id, c_id, ol_cnt, supware, itemid, qty, now);
}

// Place a random delivery
void RandomDelivery(imlab::Database &db) {
    Timestamp now(0);
    db.Delivery(Integer(URand(1, kWarehouses)), Integer(URand(1, 10)), now);
}


}  // namespace

void load_tbl_files(imlab::Database& db){
    std::ifstream  input1("/Users/mturic/global/privat/studium/Informatik/Semester5/cppPraktikum/tasks/tpcc_5w/tpcc_customer.tbl");
    std::ifstream  input2("/Users/mturic/global/privat/studium/Informatik/Semester5/cppPraktikum/tasks/tpcc_5w/tpcc_district.tbl");
    std::ifstream  input3("/Users/mturic/global/privat/studium/Informatik/Semester5/cppPraktikum/tasks/tpcc_5w/tpcc_history.tbl");
    std::ifstream  input4("/Users/mturic/global/privat/studium/Informatik/Semester5/cppPraktikum/tasks/tpcc_5w/tpcc_item.tbl");
    std::ifstream  input5("/Users/mturic/global/privat/studium/Informatik/Semester5/cppPraktikum/tasks/tpcc_5w/tpcc_neworder.tbl");
    std::ifstream  input6("/Users/mturic/global/privat/studium/Informatik/Semester5/cppPraktikum/tasks/tpcc_5w/tpcc_order.tbl");
    std::ifstream  input7("/Users/mturic/global/privat/studium/Informatik/Semester5/cppPraktikum/tasks/tpcc_5w/tpcc_orderline.tbl");
    std::ifstream  input8("/Users/mturic/global/privat/studium/Informatik/Semester5/cppPraktikum/tasks/tpcc_5w/tpcc_stock.tbl");
    std::ifstream  input9("/Users/mturic/global/privat/studium/Informatik/Semester5/cppPraktikum/tasks/tpcc_5w/tpcc_warehouse.tbl");
    db.LoadCustomer(input1);
    db.LoadDistrict(input2);
    db.LoadHistory(input3);
    db.LoadItem(input4);
    db.LoadNewOrder(input5);
    db.LoadOrder(input6);
    db.LoadOrderLine(input7);
    db.LoadStock(input8);
    db.LoadWarehouse(input9);
}

void print_tuples_database(imlab::Database& db) {
    std::cout << std::endl;
    std::cout << "Number of tuples in table Warehouse: " << db.Size<imlab::tpcc::kWarehouse>() << std::endl;
    std::cout << "Number of tuples in table District: " << db.Size<imlab::tpcc::kDistrict>() << std::endl;
    std::cout << "Number of tuples in table Customer: " << db.Size<imlab::tpcc::kCustomer>() << std::endl;
    std::cout << "Number of tuples in table History: " << db.Size<imlab::tpcc::kHistory>() << std::endl;
    std::cout << "Number of tuples in table Item: " << db.Size<imlab::tpcc::kItem>() << std::endl;
    std::cout << "Number of tuples in table NewOrder: " << db.Size<imlab::tpcc::kNewOrder>() << std::endl;
    std::cout << "Number of tuples in table Order: " << db.Size<imlab::tpcc::kOrder>() << std::endl;
    std::cout << "Number of tuples in table OrderLine: " << db.Size<imlab::tpcc::kOrderLine>() << std::endl;
    std::cout << "Number of tuples in table Stock: " << db.Size<imlab::tpcc::kStock>() << std::endl;
    std::cout << std::endl;
}

void execute_newOrder(int times, imlab::Database& db) {
    for(int i=0; i < times; i++){
        RandomNewOrder(db);
    }
}

void printExecutionTime(ClockTime start_time, ClockTime end_time)
{
    auto execution_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    auto execution_time_ms = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    auto execution_time_sec = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
    auto execution_time_min = std::chrono::duration_cast<std::chrono::minutes>(end_time - start_time).count();
    auto execution_time_hour = std::chrono::duration_cast<std::chrono::hours>(end_time - start_time).count();

    std::cout << "\nExecution Time: ";
    if(execution_time_hour > 0)
        std::cout << "" << execution_time_hour << " Hours, ";
    if(execution_time_min > 0)
        std::cout << "" << execution_time_min % 60 << " Minutes, ";
    if(execution_time_sec > 0)
        std::cout << "" << execution_time_sec % 60 << " Seconds, ";
    if(execution_time_ms > 0)
        std::cout << "" << execution_time_ms % long(1E+3) << " MicroSeconds, ";
    if(execution_time_ns > 0)
        std::cout << "" << execution_time_ns % long(1E+6) << " NanoSeconds, ";
}


int main(int argc, char *argv[]) {
    imlab::Database db1;
    // 0.) Load the data from the .tbl files
    load_tbl_files(db1);
    /*
    // 1.) Print the number of tuples in the database tables before transactions
    print_tuples_database(db1);
    auto t1 = std::chrono::high_resolution_clock::now();
    // 2.) Execute New Order transaction 1 Million times
    execute_newOrder(1000000,db1);
    auto t2 = std::chrono::high_resolution_clock::now();
    // 3.) Print the number of tuples in the database tables after transactions
    print_tuples_database(db1);
    printExecutionTime(t1, t2);

    // TODO

    for (int i = 0; i < 1000000; ++i) {
        if (URand(1, 100) <= 10) {
            RandomDelivery(db1);
        } else {
            RandomNewOrder(db1);
        }
    }

    db1.AnalyticalQuerySTL();
    std::cout << " the result of the query is :  " << db1.AnalyticalQuerySTL().value << " end";
     */

    return 0;
}
