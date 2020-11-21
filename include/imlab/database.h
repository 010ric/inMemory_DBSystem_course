// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------

#ifndef INCLUDE_IMLAB_DATABASE_H_
#define INCLUDE_IMLAB_DATABASE_H_

#include <istream>
#include <array>
#include <vector>
#include <unordered_map>
#include "imlab/infra/hash.h"
#include "imlab/schema.h"

namespace imlab {

class Database {
 private:
    std::vector<tpcc::Customer> customerVec;
    std::vector<tpcc::District> districtVec;
    std::vector<tpcc::History> historyVec;
    std::vector<tpcc::Item> itemVec;
    std::vector<tpcc::NewOrder> newOrderVec;
    std::vector<tpcc::Order> orderVec;
    std::vector<tpcc::OrderLine> orderLineVec;
    std::vector<tpcc::Stock> stockVec;
    std::vector<tpcc::Warehouse> warehouseVec;

    // Warehouse: Primary Key: W_ID
    std::unordered_map<Key<Integer>, size_t> warehouseKeyIndex;
    // District : Primary Key: (D_W_ID, D_ID)
    std::unordered_map<Key<Integer, Integer>, size_t> districtKeyIndex;
    // Customer : Primary Key: (C_W_ID, C_D_ID, C_ID)
    std::unordered_map<Key<Integer, Integer, Integer>, size_t> customerKeyIndex;
    // History : Primary Key: none
    // Not needed ?! std::unordered_map<Key<Integer, Integer, Integer>, size_t> historyKeyIndex;
    // NewOrder : Primary Key: (NO_W_ID, NO_D_ID, NO_O_ID)
    std::unordered_map<Key<Integer, Integer, Integer>, size_t> newOrderKeyIndex;
    // Order : Primary Key: (O_W_ID, O_D_ID, O_ID)
    std::unordered_map<Key<Integer, Integer, Integer>, size_t> orderKeyIndex;
    // OrderLine : Primary Key: (OL_W_ID, OL_D_ID, OL_O_ID, OL_NUMBER)
    std::unordered_map<Key<Integer, Integer, Integer, Integer>, size_t> orderLineKeyIndex;
    // Item : Primary Key: I_ID
    std::unordered_map<Key<Integer>, size_t> itemKeyIndex;
    // Stock : Primary Key: (S_W_ID, S_I_ID)
    std::unordered_map<Key<Integer, Integer>, size_t> stockKeyIndex;
 public:
    // Load the TPCC data.
    // Call these methods with std::ifstreams to load your data.
    void LoadCustomer(std::istream &in);
    void LoadDistrict(std::istream &in);
    void LoadHistory(std::istream &in);
    void LoadItem(std::istream &in);
    void LoadNewOrder(std::istream &in);
    void LoadOrder(std::istream &in);
    void LoadOrderLine(std::istream &in);
    void LoadStock(std::istream &in);
    void LoadWarehouse(std::istream &in);

    // Place a new order.
    void NewOrder(
        Integer w_id,
        Integer d_id,
        Integer c_id,
        Integer items,
        std::array<Integer, 15> &supware,
        std::array<Integer, 15> &itemid,
        std::array<Integer, 15> &qty,
        Timestamp datetime);

    // Create a delivery
    void Delivery(
        Integer w_id,
        Integer o_carrier_id,
        Timestamp datetime);

    // Run an analytical query with STL datastructures
    Numeric<12, 2> AnalyticalQuerySTL();
    // Run an analytical query with a lazy hash table
    Numeric<12, 2> AnalyticalQueryLHT();

    // Returns the number of tuples in a relation.
    template <tpcc::Relation> size_t Size();
};

}  // namespace imlab

#endif  // INCLUDE_IMLAB_DATABASE_H_
