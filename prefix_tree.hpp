#pragma  once
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

namespace algos {
    struct Cell;

    using Data = std::vector<std::vector<std::string>>;
    using Dict = std::unordered_map<std::string, Cell>;
    struct Node {
        Dict valToCell;
        bool visited = false;
        size_t noOfEntity = 0;
    };

    struct Cell {
        Cell(std::string attr, size_t leaf_count)
        : value_(std::move(attr)),
        leaf_count_(leaf_count),
        child_(nullptr) {}
        Cell() : value_(), leaf_count_(0), child_(nullptr) {}

        [[nodiscard]] bool is_leaf() const {
            return leaf_count_ > 0;
        }

        const std::string value_;
        size_t leaf_count_{};
        std::shared_ptr<Node> child_ = nullptr;

    };

    std::shared_ptr<Node> merge(std::vector<std::shared_ptr<Node>>& nodes);

    class PrefixTree {
    public:
        PrefixTree(const Data &data);

        void traverse();
        void discard();

        bool no_key() {
            return no_composite_key_;
        }
    private:
        std::shared_ptr<Node> const root_;
        bool no_composite_key_;
        size_t size_;
    };
}