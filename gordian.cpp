#include "prefix_tree.hpp"

#include <iostream>

int main() {
    algos::Data data(4);

    data[0] = {"Michael", "Thompson", "3478", "10"};
    data[1] = {"Sally", "Kwan", "3478", "20"};
    data[2] = {"Michael", "Spencer", "5237", "90"};
    data[3] = {"Michael", "Thompson", "6791", "50"};

    algos::PrefixTree tree(data);
    if (tree.no_key()) {
        std::cout << "no key";
    }
    mer
    return 0;
}
