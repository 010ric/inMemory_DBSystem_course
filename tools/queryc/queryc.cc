#include <iostream>
#include <fstream>
#include <imlab/schema.h>

#include "gflags/gflags.h"
#include "imlab/algebra/inner_join.h"
#include "imlab/algebra/iu.h"
#include "imlab/algebra/operator.h"
#include "imlab/algebra/print.h"
#include "imlab/algebra/selection.h"
#include "imlab/algebra/table_scan.h"

DEFINE_string(out_cc, "", "Header path");
DEFINE_string(out_h, "", "Implementation path");

static bool ValidateWritable(const char *flagname, const std::string &value) {
    std::ofstream out(value);
    return out.good();
}
static bool ValidateReadable(const char *flagname, const std::string &value) {
    std::ifstream in(value);
    return in.good();
}

DEFINE_validator(out_cc, &ValidateWritable);
DEFINE_validator(out_h, &ValidateWritable);



int main(int argc, char *argv[]) {
    gflags::SetUsageMessage("queryc --out_cc <H> --out_h <CC>");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    // Prepare
    std::filebuf fb;
    fb.open ("out.cc",std::ios::out);
    std::ostream outPut = std::ostream(&fb);

    imlab::TableScan tbsC = imlab::TableScan("customer");
    imlab::TableScan tbsO = imlab::TableScan("\"order\"");
    imlab::TableScan tbsOl = imlab::TableScan("orderline");

    std::unique_ptr<imlab::TableScan> child_Tbsc;
    *child_Tbsc = tbsC;

    std::unique_ptr<imlab::TableScan> child_Tbso;
    *child_Tbso = tbsO;

    std::unique_ptr<imlab::TableScan> child_TbsOl;
    *child_TbsOl = tbsOl;

    // Prepare the different IU´s for the selection and innerjoins
    const imlab::IU iu1 = imlab::IU("customer", "c_id", imlab::schemac::Type().Integer());
    const imlab::IU iu2 = imlab::IU("customer", "c_d_id", imlab::schemac::Type().Integer());
    const imlab::IU iu3 = imlab::IU("customer", "c_w_id", imlab::schemac::Type().Integer());
    const imlab::IU iu4 = imlab::IU("\"order\"", "o_id", imlab::schemac::Type().Integer());
    const imlab::IU iu5 = imlab::IU("\"order\"", "o_d_id", imlab::schemac::Type().Integer());
    const imlab::IU iu6 = imlab::IU("\"order\"", "o_w_id", imlab::schemac::Type().Integer());
    const imlab::IU iu7 = imlab::IU("\"order\"", "o_c_id", imlab::schemac::Type().Integer());
    const imlab::IU iu8 = imlab::IU("orderline", "ol_o_id", imlab::schemac::Type().Integer());
    const imlab::IU iu9 = imlab::IU("orderline", "ol_d_id", imlab::schemac::Type().Integer());
    const imlab::IU iu10 = imlab::IU("orderline", "ol_w_id", imlab::schemac::Type().Integer());

    // Construct the selection
    std::pair<const imlab::IU*, std::string> p1;
    p1.first = &iu1;
    p1.second = "322";
    std::pair<const imlab::IU*, std::string> p2;
    p1.first = &iu2;
    p1.second = "1";
    std::pair<const imlab::IU*, std::string> p3;
    p1.first = &iu3;
    p1.second = "1";

    // std::vector<std::pair<const IU*, std::string>> predicates for selection;
    std::vector<std::pair<const imlab::IU*, std::string>> predSelection {p1, p2, p3};

    imlab::Selection selection1 = imlab::Selection(std::move(child_Tbsc), predSelection);
    // Prepare table customer for selection
    // tbsC.Prepare(tbsC.CollectIUs(), &selection1);

    // Construct the selection
    std::pair<const imlab::IU*, std::string> p4;
    p1.first = &iu1;
    p1.second = "o_d_id";
    std::pair<const imlab::IU*, std::string> p5;
    p1.first = &iu2;
    p1.second = "o_w_id";
    std::pair<const imlab::IU*, std::string> p6;
    p1.first = &iu3;
    p1.second = "o_c_id";

    // std::vector<std::pair<const IU*, std::string>> predicates for first innerJoin;
    std::vector<std::pair<const imlab::IU*, std::string>> predSelectionInnJoin1;

    // Prepare the innerJoin of customer and order
    std::unique_ptr<imlab::Selection> leftChild_selectPtr;
    *leftChild_selectPtr = (std::move(selection1));

    imlab::InnerJoin ij1 = imlab::InnerJoin(leftChild_selectPtr, std::move(child_Tbso), predSelectionInnJoin1);
    // Construct the first innerJoin std::pairs


    // std::vector<std::pair<const IU*, std::string>> predicates for second innerJoin;
    std::vector<std::pair<const imlab::IU*, std::string>> predSelectionInnJoin2;
    // Construct the second innerJoin std::pairs

    // on their columns o_w_id = c_w_id; o_d_id = c_d_id; o_c_id = c_id


    // Prepare the second innerJoin
    // imlab::Print pr1;

    // imlab::InnerJoin ij1;
    // imlab::InnerJoin ij2;

    // Prepare the order
    // tbsO.Prepare(tbsO.CollectIUs(), ij1);
    // Prepare the orderline
    // tbsO.Prepare(tbsO.CollectIUs(), ij2);


}

