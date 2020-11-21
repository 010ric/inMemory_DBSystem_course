// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_ALGEBRA_INNER_JOIN_H_
#define INCLUDE_IMLAB_ALGEBRA_INNER_JOIN_H_
// ---------------------------------------------------------------------------
#include <memory>
#include <utility>
#include <vector>
#include "imlab/algebra/iu.h"
#include "imlab/algebra/operator.h"
// ---------------------------------------------------------------------------
namespace imlab {
// ---------------------------------------------------------------------------
class InnerJoin: public Operator {
 protected:
    // Left child operator
    std::unique_ptr<Operator> left_child_;
    // Right child operator
    std::unique_ptr<Operator> right_child_;
    // Hash predicates
    std::vector<std::pair<const IU*, const IU*>> hash_predicates_;

    // Required ius
    std::vector<const IU*> required_ius_;
    // Consumer
    Operator *consumer_;

 public:
    // Constructor
    InnerJoin(std::unique_ptr<Operator> left,
            std::unique_ptr<Operator> right,
            std::vector<std::pair<const IU*, const IU*>> predicates)
        : left_child_(std::move(left)), right_child_(std::move(right)), hash_predicates_(predicates) {}

    // Collect all IUs produced by the operator
    std::vector<const IU*> CollectIUs();

    // Prepare the operator
    void Prepare(const std::vector<const IU*> &required, Operator* consumer);
    // Produce all tuples
    void Produce();
    // Consume tuple
    void Consume(const Operator* child);
};

    std::vector<const IU *> InnerJoin::CollectIUs() {
        return Operator::CollectIUs();
    }

    void InnerJoin::Produce() {
        Operator::Produce();
    }

    void InnerJoin::Consume(const Operator *child) {
        Operator::Consume(child);
    }

    void InnerJoin::Prepare(const std::vector<const IU *> &required, Operator *consumer) {
        Operator::Prepare(required, consumer);
    }
// ---------------------------------------------------------------------------
}  // namespace imlab
// ---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_ALGEBRA_INNER_JOIN_H_
// ---------------------------------------------------------------------------

