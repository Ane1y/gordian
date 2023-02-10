#include "prefix_tree.hpp"

#include <iostream>
#include <memory>

using namespace algos;

algos::PrefixTree::PrefixTree(const Data& dataset)
        : root_(new Node),
          no_composite_key_(false),
          size_(dataset.size())
           {
    for (const auto& entity: dataset) {
        auto node = root_;
        for (const auto & attribute : entity) {
            node->valToCell.try_emplace(attribute, Cell{attribute, 0});
            Cell& cell = node->valToCell[attribute];

            if (&attribute == &entity.back()) {
                cell.leaf_count_ += 1;
                if (cell.leaf_count_ > 1) {
                    no_composite_key_ = true;
                    // сразу говорим что в датасете нет ключей
                    return;
                }
            } else {
                if (!cell.child_) {
                    cell.child_ = std::make_shared<Node>();
                }
                node = cell.child_;
                node->noOfEntity += 1;
            }
        }
    }
}

std::shared_ptr<Node> algos::merge(std::vector<std::shared_ptr<Node>>& nodes) {
    std::shared_ptr<Node> mergedNode;
    if (nodes.size() == 1) {
        mergedNode = nodes[0];
    }

    std::unordered_map<std::string, std::vector<Cell*>> dic;
    bool is_leaf_level = false;
    for (const auto& node: nodes) {
        mergedNode->noOfEntity += node->noOfEntity;
        for (auto& [val, cell] : node->valToCell) {
            auto vec = dic[val];
            vec.push_back(&cell);
            if (cell.is_leaf()) {
                is_leaf_level = true;
            }
        }

        for (const auto& [val, cell_list] : dic) {
            mergedNode->valToCell.emplace(val, Cell{val, 0});
            auto new_cell = mergedNode->valToCell[val];

            if (is_leaf_level) {
                std::vector<std::shared_ptr<Node>> partial_set;
                for (const auto cell : cell_list) {
                     partial_set.push_back(cell->child_);
                }
                new_cell.child_ = merge(partial_set);
            }
        }
    }
    return mergedNode;
}

void algos::PrefixTree::traverse() {

}

void algos::PrefixTree::discard() {

}
