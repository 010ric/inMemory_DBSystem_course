// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------

#include "imlab/database.h"
#include <array>
#include <sstream>
#include "imlab/infra/error.h"
#include "imlab/infra/types.h"

namespace imlab {

void Database::LoadWarehouse(std::istream &in) {
    tpcc::Warehouse* w1;
    std::string line, part;
    size_t c = 0;
    int i = 0;
    while (std::getline(in, line)) {
        std::stringstream lineStream(line);
        std::getline(lineStream, part, '|');
        if(!lineStream.good())
            break;
        w1 = new tpcc::Warehouse();
        w1->w_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        w1->w_name = Varchar<10>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        w1->w_street_1 = Varchar<20>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        w1->w_street_2 = Varchar<20>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        w1->w_city = Varchar<20>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        w1->w_state = Char<2>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        w1->w_zip = Char<9>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        w1->w_tax = Numeric<4, 4>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        w1->w_ytd = Numeric<12, 2>::castString(part.c_str(), part.size());
        // Warehouse: Primary Key: W_ID
        warehouseKeyIndex.insert({Key(w1->w_id),c});
        warehouseVec.push_back(*w1);
        delete w1;
        c++;
        i++;
    }
}

void Database::LoadDistrict(std::istream &in) {
    tpcc::District* d1;
    std::string line, part;
    size_t c = 0;
    int i = 0;
    while (std::getline(in, line)) {
        std::stringstream lineStream(line);
        std::getline(lineStream, part, '|');
        if(!lineStream.good())
            break;
        d1 = new tpcc::District();
        d1->d_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        d1->d_w_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        d1->d_name = Varchar<10>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        d1->d_street_1 = Varchar<20>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        d1->d_street_2 = Varchar<20>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        d1->d_city = Varchar<20>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        d1->d_state = Char<2>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        d1->d_zip = Char<9>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        d1->d_tax = Numeric<4, 4>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        d1->d_ytd = Numeric<12, 2>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        d1->d_next_o_id = Integer::castString(part.c_str(), part.size());
        // District : Primary Key: (D_W_ID, D_ID)
        districtKeyIndex.insert({Key(d1->d_w_id, d1->d_id),c});
        districtVec.push_back(*d1);
        delete d1;
        c++;
        i++;
    }
}

void Database::LoadCustomer(std::istream &in) {
    tpcc::Customer* c1;
    std::string line, part;
    size_t c = 0;
    int i = 0;
    while (std::getline(in, line)) {
        std::stringstream lineStream(line);
        std::getline(lineStream, part, '|');
        if(!lineStream.good())
            break;
        c1 = new tpcc::Customer();
        c1->c_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_d_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_w_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_first = Varchar<16>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_middle = Char<2>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_last = Varchar<16>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_street_1 = Varchar<20>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_street_2 = Varchar<20>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_city = Varchar<20>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_state = Char<2>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_zip = Char<9>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_phone = Char<16>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_since = Timestamp::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_credit = Char<2>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_credit_lim = Numeric<12, 2>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_discount = Numeric<4, 4>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_balance = Numeric<12, 2>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_ytd_payment = Numeric<12, 2>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_payment_cnt = Numeric<4, 0>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_delivery_cnt = Numeric<4, 0>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        c1->c_data = Varchar<500>::castString(part.c_str(), part.size());
        // Customer : Primary Key: (C_W_ID, C_D_ID, C_ID)
        customerKeyIndex.insert({Key(c1->c_w_id, c1->c_d_id, c1->c_id),c});
        customerVec.push_back(*c1);
        delete c1;
        c++;
        i++;
    }
}

void Database::LoadHistory(std::istream &in) {
    tpcc::History* h1;
    std::string line, part;
    size_t c = 0;
    int i = 0;
    while (std::getline(in, line)) {
        std::stringstream lineStream(line);
        std::getline(lineStream, part, '|');
        if(!lineStream.good())
            break;
        h1 = new tpcc::History();
        h1->h_c_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        h1->h_c_d_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        h1->h_c_w_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        h1->h_d_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        h1->h_w_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        h1->h_date = Timestamp::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        h1->h_amount = Numeric<6, 2>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        h1->h_data = Varchar<24>::castString(part.c_str(), part.size());
        // History table has no primary key.
        historyVec.push_back(*h1);
        delete h1;
        c++;
        i++;
    }
}

void Database::LoadNewOrder(std::istream &in) {
    tpcc::NewOrder* no1;
    std::string line, part;
    size_t c = 0;
    int i = 0;
    while (std::getline(in, line)) {
        std::stringstream lineStream(line);
        std::getline(lineStream, part, '|');
        if(!lineStream.good())
            break;
        no1 = new tpcc::NewOrder();
        no1->no_o_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        no1->no_d_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        no1->no_w_id = Integer::castString(part.c_str(), part.size());
        // NewOrder : Primary Key: (NO_W_ID, NO_D_ID, NO_O_ID)
        newOrderKeyIndex.insert({Key(no1->no_w_id, no1->no_d_id, no1->no_o_id),c});
        newOrderVec.push_back(*no1);
        delete no1;
        c++;
        i++;
    }
}

void Database::LoadOrder(std::istream &in) {
    tpcc::Order* o1;
    std::string line, part;
    size_t c = 0;
    int i = 0;
    while (std::getline(in, line)) {
        std::stringstream lineStream(line);
        std::getline(lineStream, part, '|');
        if(!lineStream.good())
            break;
        o1 = new tpcc::Order();
        o1->o_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        o1->o_d_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        o1->o_w_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        o1->o_c_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        o1->o_entry_d = Timestamp::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        o1->o_carrier_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        o1->o_ol_cnt = Numeric<2, 0>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        o1->o_all_local = Numeric<1, 0>::castString(part.c_str(), part.size());
        // Order : Primary Key: (O_W_ID, O_D_ID, O_ID)
        orderKeyIndex.insert({Key(o1->o_w_id, o1->o_d_id, o1->o_id),c});
        orderVec.push_back(*o1);
        delete o1;
        c++;
        i++;
    }
}

void Database::LoadOrderLine(std::istream &in) {
    tpcc::OrderLine* ol1;
    std::string line, part;
    size_t c = 0;
    int i = 0;
    while (std::getline(in, line)) {
        std::stringstream lineStream(line);
        std::getline(lineStream, part, '|');
        if(!lineStream.good())
            break;
        ol1 = new tpcc::OrderLine();
        ol1->ol_o_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        ol1->ol_d_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        ol1->ol_w_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        ol1->ol_number = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        ol1->ol_i_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        ol1->ol_supply_w_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        ol1->ol_delivery_d = Timestamp::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        ol1->ol_quantity = Numeric<2, 0>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        ol1->ol_amount = Numeric<6, 2>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        ol1->ol_dist_info = Char<24>::castString(part.c_str(), part.size());
        // OrderLine : Primary Key: (OL_W_ID, OL_D_ID, OL_O_ID, OL_NUMBER)
        orderLineKeyIndex.insert({Key(ol1->ol_w_id, ol1->ol_d_id, ol1->ol_o_id, ol1->ol_number),c});
        orderLineVec.push_back(*ol1);
        delete ol1;
        c++;
        i++;
    }
}

void Database::LoadItem(std::istream &in) {
    tpcc::Item* it1;
    std::string line, part;
    size_t c = 0;
    int i = 0;
    while (std::getline(in, line)) {
        std::stringstream lineStream(line);
        std::getline(lineStream, part, '|');
        if(!lineStream.good())
            break;
        it1 = new tpcc::Item();
        it1->i_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        it1->i_im_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        it1->i_name = Varchar<24>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        it1->i_price = Numeric<5, 2>::castString(part.c_str(), part.size());
        // Item : Primary Key: I_ID
        itemKeyIndex.insert({Key(it1->i_id),c});
        itemVec.push_back(*it1);
        delete it1;
        c++;
        i++;
    }
}

void Database::LoadStock(std::istream& in) {
    tpcc::Stock* st1;
    std::string line, part;
    size_t c = 0;
    int i = 0;
    while (std::getline(in, line)) {
        std::stringstream lineStream(line);
        std::getline(lineStream, part, '|');
        if(!lineStream.good())
            break;
        st1 = new tpcc::Stock();
        st1->s_i_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_w_id = Integer::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_quantity = Numeric<4, 0>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_dist_01 = Char<24>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_dist_02 = Char<24>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_dist_03 = Char<24>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_dist_04 = Char<24>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_dist_05 = Char<24>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_dist_06 = Char<24>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_dist_07 = Char<24>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_dist_08 = Char<24>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_dist_09 = Char<24>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_dist_10 = Char<24>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_ytd = Numeric<8, 0>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_order_cnt = Numeric<4, 0>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_remote_cnt = Numeric<4, 0>::castString(part.c_str(), part.size());
        std::getline(lineStream, part, '|');
        st1->s_data = Varchar<50>::castString(part.c_str(), part.size());
        // Stock : Primary Key: (S_W_ID, S_I_ID)
        stockKeyIndex.insert({Key(st1->s_w_id, st1->s_i_id),c});
        stockVec.push_back(*st1);
        delete st1;
        c++;
        i++;
    }
}

void Database::NewOrder(
        Integer w_id,
        Integer d_id,
        Integer c_id,
        Integer items,
        std::array<Integer, 15> &supware,
        std::array<Integer, 15> &itemid,
        std::array<Integer, 15> &qty,
        Timestamp datetime) {
    // select w_tax from warehouse w where w.w_id=w_id;
    Numeric<4,4> wTax = warehouseVec[warehouseKeyIndex.at(Key(w_id))].w_tax;
    // select c_discount from customer c where c.c_w_id=w_id and c.c_d_id=d_id and c.c_id=c_id;
    Numeric<4,4> cDiscount = customerVec[customerKeyIndex.at(Key(w_id,d_id,c_id))].c_discount;
    // select d_next_o_id as o_id,d_tax from district d where d.d_w_id=w_id and d.d_id=d_id;
    Numeric<4,4> dTax = districtVec[districtKeyIndex.at(Key(w_id,d_id))].d_tax;
    Integer oID = districtVec[districtKeyIndex.at(Key(w_id,d_id))].d_next_o_id;
    // update district set d_next_o_id=o_id+1 where d_w_id=w_id and district.d_id=d_id;
    districtVec[districtKeyIndex.at(Key(w_id,d_id))].d_next_o_id=(oID).operator+=(Integer(1));
    // forsequence
    int all_local = 1;
    for (int j = 0; j < items.value; j++) {
        if (w_id == supware[j]) {
            all_local = 0;
        }
    }
    // insert into "order" values (o_id,d_id,w_id,c_id,datetime,0,items,all_local);
    tpcc::Order* o1 = new tpcc::Order();
    o1->o_id = oID;
    o1->o_d_id = d_id;
    o1->o_w_id = w_id;
    o1->o_c_id = c_id;
    o1->o_entry_d = datetime;
    o1->o_carrier_id = Integer(0);
    o1->o_ol_cnt = Numeric<2,0>(items);
    o1->o_all_local = Numeric<1,0>(all_local);
    // Order : Primary Key: (O_W_ID, O_D_ID, O_ID)
    orderKeyIndex.insert({Key(o1->o_w_id, o1->o_d_id, o1->o_id),orderVec.size()});
    Database::orderVec.push_back(*o1);
    delete o1;

    // insert into neworder values (o_id,d_id,w_id);
    tpcc::NewOrder* no1 = new tpcc::NewOrder();
    no1->no_o_id = oID;
    no1->no_d_id = d_id;
    no1->no_w_id = w_id;
    // NewOrder : Primary Key: (NO_W_ID, NO_D_ID, NO_O_ID)
    newOrderKeyIndex.insert({Key(no1->no_w_id, no1->no_d_id, no1->no_o_id), newOrderVec.size()});
    Database::newOrderVec.push_back(*no1);
    delete no1;

    // forsequence (index between 0 and items-1) {
    for (int index = 0; index < items.value; index++) {
        // select i_price from item where i_id=itemid[index];
        Numeric<5,2> iPrice;
        iPrice = itemVec[itemKeyIndex.at(Key(itemid[index]))].i_price;
        //         select s_quantity,s_remote_cnt,s_order_cnt,case d_id when 1 then s_dist_01 when 2 then s_dist_02
        //         when 3 then s_dist_03 when 4 then s_dist_04 when 5 then s_dist_05 when 6 then s_dist_06 when 7
        //         then s_dist_07 when 8 then s_dist_08 when 9 then s_dist_09 when 10 then s_dist_10 end as s_dist
        //         from stock where s_w_id=supware[index] and s_i_id=itemid[index];
        Numeric<4, 0> sQuantity = stockVec[stockKeyIndex.at(Key(supware[index], itemid[index]))].s_quantity;
        Char<24> sDistPicked;
        switch(d_id.value){
            case 1:
                sDistPicked = stockVec[supware[index].value].s_dist_01;
                break;
            case 2:
                sDistPicked = stockVec[supware[index].value].s_dist_02;
                break;
            case 3:
                sDistPicked = stockVec[supware[index].value].s_dist_03;
                break;
            case 4:
                sDistPicked = stockVec[supware[index].value].s_dist_04;
                break;
            case 5:
                sDistPicked = stockVec[supware[index].value].s_dist_05;
                break;
            case 6:
                sDistPicked = stockVec[supware[index].value].s_dist_06;
                break;
            case 7:
                sDistPicked = stockVec[supware[index].value].s_dist_07;
                break;
            case 8:
                sDistPicked = stockVec[supware[index].value].s_dist_08;
                break;
            case 9:
                sDistPicked = stockVec[supware[index].value].s_dist_09;
                break;
            case 10:
                sDistPicked = stockVec[supware[index].value].s_dist_10;
                break;
        }


        // if (s_quantity>qty[index]) {
        //            update stock set s_quantity=s_quantity-qty[index] where s_w_id=supware[index] and s_i_id=itemid[index];
        //        } else {
        //            update stock set s_quantity=s_quantity+91-qty[index] where s_w_id=supware[index] and s_i_id=itemid[index];
        //        }
        if( sQuantity.operator>( Numeric<4,0>(qty[index]) ) ){
                stockVec[stockKeyIndex.at(Key(supware[index], qty[index]))].s_quantity.operator+=(-Numeric<4,0>(qty[index]));
        } else {
            stockVec[stockKeyIndex.at(Key(supware[index], qty[index]))].s_quantity.operator+=(-Numeric<4,0>(qty[index]) + Numeric<4,0>(91));
        }

        // if (supware[index]<>w_id) {
        //            update stock set s_remote_cnt=s_remote_cnt+1 where s_w_id=w_id and s_i_id=itemid[index];
        //        } else {
        //            update stock set s_order_cnt=s_order_cnt+1 where s_w_id=w_id and s_i_id=itemid[index];
        //        }
        if( supware[index].operator==(w_id) ) {
            stockVec[stockKeyIndex.at(Key(w_id, itemid[index]))].s_remote_cnt.operator+=(Numeric<4,0>(1));
        } else {
            stockVec[stockKeyIndex.at(Key(w_id, itemid[index]))].s_order_cnt.operator+=(Numeric<4,0>(1));
        }

        // var numeric(6,2) ol_amount=qty[index]*i_price*(1.0+w_tax+d_tax)*(1.0-c_discount);
        Numeric<6,2> olAmount = Numeric<6,2>( qty[index].value * (iPrice.value) * (1.0 + wTax.value + dTax.value) * (1.0 - cDiscount.value));
        // insert into orderline values (o_id,d_id,w_id,index+1,itemid[index],supware[index],0,qty[index],ol_amount,s_dist);
        tpcc::OrderLine* orL1 = new tpcc::OrderLine();
        orL1->ol_o_id = oID;
        orL1->ol_d_id = d_id;
        orL1->ol_w_id = w_id;
        orL1->ol_number = Integer(index+1);
        orL1->ol_i_id = itemid[index];
        orL1->ol_supply_w_id = supware[index];
        orL1->ol_delivery_d = Timestamp(0);
        orL1->ol_quantity = Numeric<2,0>(qty[index]);
        orL1->ol_amount = olAmount;
        orL1->ol_dist_info = sDistPicked;
        // OrderLine : Primary Key: (OL_W_ID, OL_D_ID, OL_O_ID, OL_NUMBER)
        orderLineKeyIndex.insert({Key(orL1->ol_w_id, orL1->ol_d_id, orL1->ol_o_id, orL1->ol_number), orderLineVec.size()});
        Database::orderLineVec.push_back(*orL1);
        delete orL1;
    }
}

void Database::Delivery(
        Integer w_id,
        Integer o_carrier_id,
        Timestamp datetime) {
    for(int dID = 1; dID <= 10; dID++){
        /*
         *
         select min(no_o_id) as o_id from neworder where no_w_id=w_id and no_d_id=d_id order by no_o_id else { continue; } -- ignore this district if no row found
         */
        Integer minOID = Integer(newOrderVec.size());
        for(int j = 0; j < newOrderVec.size(); j++){
            // Count up the no_o_id till you get to element which has required w_id && d_id
            // Check if there is an element and pick the first one, while counting up
            if(newOrderVec[j].no_w_id == w_id && newOrderVec[j].no_d_id == Integer(dID) && newOrderVec[j].no_o_id.operator<(minOID)){
                minOID = newOrderVec[j].no_o_id;
            }
        }
        // delete from neworder where no_w_id=w_id and no_d_id=d_id and no_o_id=o_id;
        size_t rememb;
        if(newOrderKeyIndex.find(Key(w_id, Integer(dID), minOID)) != newOrderKeyIndex.end()){
            rememb = newOrderKeyIndex.at(Key(w_id, Integer(dID), minOID));
        }
        // overwrite element which should be deleted
        if(newOrderKeyIndex.find(Key(w_id, Integer(dID), minOID)) != newOrderKeyIndex.end()){
            newOrderVec[newOrderKeyIndex.at(Key(w_id, Integer(dID), minOID))] = newOrderVec[newOrderVec.size() - 1];
        }
        // remove the deleted element from the newOrderKeyIndex
        newOrderKeyIndex.erase(Key(w_id, Integer(dID), minOID));
        Key k = Key(newOrderVec[newOrderVec.size() - 1].no_w_id, Integer(dID), newOrderVec[newOrderVec.size() - 1].no_o_id);
        newOrderKeyIndex[k] = rememb;
        newOrderVec.pop_back();
        // select o_ol_cnt,o_c_id from "order" o where o_w_id=w_id and o_d_id=d_id and o.o_id=o_id;
        Numeric<2,0> ordLineCount = orderVec[orderKeyIndex.at(Key(w_id, Integer(dID), minOID))].o_ol_cnt;
        Integer custID = orderVec[orderKeyIndex.at(Key(w_id, Integer(dID), minOID))].o_c_id;
        //update "order" set o_carrier_id=o_carrier_id where o_w_id=w_id and o_d_id=d_id and "order".o_id=o_id;
        orderVec[orderKeyIndex.at(Key(w_id, Integer(dID), minOID))].o_carrier_id = o_carrier_id;
        // var numeric(6,2) ol_total=0;
        Numeric<6,2> olTotal = Numeric<6,2>(0);
        // forsequence (ol_number between 1 and o_ol_cnt) {
        for(int oLNumb = 1; oLNumb <= ordLineCount.value; oLNumb++){
            //    select ol_amount from orderline where ol_w_id=w_id and ol_d_id=d_id and ol_o_id=o_id and orderline.ol_number=ol_number;
            Numeric<6, 2> oLAmount = Numeric<6, 2>( orderLineVec[orderLineKeyIndex.at(Key(w_id, Integer(dID), minOID, Integer(oLNumb)))].ol_amount );
            //    ol_total=ol_total+ol_amount;
            olTotal.operator+=(oLAmount);
            //    update orderline set ol_delivery_d=datetime where ol_w_id=w_id and ol_d_id=d_id and ol_o_id=o_id and orderline.ol_number=ol_number;
            orderLineVec[orderLineKeyIndex.at(Key(w_id, Integer(dID), minOID, Integer(oLNumb)))].ol_delivery_d = datetime;
        }
        // update customer set c_balance=c_balance+ol_total where c_w_id=w_id and c_d_id=d_id and c_id=o_c_id;
        customerVec[customerKeyIndex.at(Key(w_id, Integer(dID), custID))].c_balance.operator+=(Numeric<12, 2>(olTotal.value));
    };
}

Numeric<12, 2> Database::AnalyticalQuerySTL(){
    Numeric<12, 2> result;
    std::unordered_map<Key<Integer, Integer, Integer>, size_t> w1;
    std::unordered_map<Key<Integer, Integer, Integer>, size_t> w2;

    for (auto &customer : customerVec){
        if(*customer.c_last.begin() != char('B')){
            continue;
        }
        w1.insert({Key(customer.c_w_id, customer.c_d_id, customer.c_id),
                   customerKeyIndex.at(Key(customer.c_w_id, customer.c_d_id, customer.c_id))});
    }

    for (auto &order : orderVec){
        // loop trough customer Hashtable w1
        if ( w1.at(Key(order.o_w_id, order.o_d_id, order.o_c_id)) ) {
            w2.insert({Key(order.o_w_id, order.o_d_id, order.o_c_id),
                       orderKeyIndex.at(Key(order.o_w_id, order.o_d_id, order.o_c_id))});
        }
    }

    for (auto &orderline : orderLineVec){
        if ( w2.at(Key(orderline.ol_w_id, orderline.ol_d_id, orderline.ol_o_id)) ) {
            // Calculate sum
            Numeric<12,2> cBal = customerVec[w1.at(Key(orderline.ol_w_id, orderline.ol_d_id,
                    orderVec[w2.at(Key(orderline.ol_w_id, orderline.ol_d_id,
                            orderline.ol_o_id))].o_c_id))].c_balance;
            Numeric<12,2> orderOlCnt = Numeric<12,2> (orderVec[w2.at(Key(orderline.ol_w_id,
                    orderline.ol_d_id, orderline.ol_o_id))].o_ol_cnt.value);
            Numeric<12,2> olQuant = Numeric<12,2>(orderline.ol_quantity.value);
            Numeric<12,2> olAmount = Numeric<12,2>(orderline.ol_amount.value);
            result += Numeric<12,2>((Numeric<12, 4>(olQuant.operator*(olAmount)) -
                    Numeric<12, 4>(cBal.operator*(orderOlCnt))).value);
        }
    }

    return result;
}

template <> size_t Database::Size<tpcc::kCustomer>()    { return customerVec.size(); }
template <> size_t Database::Size<tpcc::kDistrict>()    { return districtVec.size(); }
template <> size_t Database::Size<tpcc::kHistory>()     { return historyVec.size(); }
template <> size_t Database::Size<tpcc::kItem>()        { return itemVec.size(); }
template <> size_t Database::Size<tpcc::kNewOrder>()    { return newOrderVec.size(); }
template <> size_t Database::Size<tpcc::kOrder>()       { return orderVec.size(); }
template <> size_t Database::Size<tpcc::kOrderLine>()   { return orderLineVec.size(); }
template <> size_t Database::Size<tpcc::kStock>()       { return stockVec.size(); }
template <> size_t Database::Size<tpcc::kWarehouse>()   { return warehouseVec.size(); }

}  // namespace imlab
