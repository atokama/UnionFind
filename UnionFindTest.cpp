#include <vector>

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

class UnionFind {
public:
    UnionFind(std::size_t size) {
        arr_.resize(size);
        for (std::size_t i{0}; i != arr_.size(); ++i) {
            arr_[i] = i;
        }
        size_.assign(arr_.size(), 1);
    }

    void unite(std::size_t a, std::size_t b) {
        check(a, b);
        auto ra = root(a);
        auto rb = root(b);
        if (size_[ra] < size_[rb]) {
            arr_[ra] = arr_[rb];
            size_[rb] += size_[ra];
        } else {
            arr_[rb] = arr_[ra];
            size_[ra] += size_[rb];
        }
    }

    bool find(std::size_t a, std::size_t b) {
        check(a, b);
        return root(a) == root(b);
    }

private:
    std::size_t root(std::size_t a) {
        while (arr_[a] != a) {
            a = arr_[a];
        }
        return a;
    }

    void check(std::size_t a, std::size_t b) {
        if (a < arr_.size() && b < arr_.size()) {
            return;
        } else throw std::runtime_error{"Out of range"};
    }

    std::vector<std::size_t> arr_, size_;
};

TEST_CASE("UnionFind", "[UnionFind]") {
    UnionFind uf{8};
    REQUIRE(!uf.find(1, 2));
    uf.unite(1, 2);
    REQUIRE(uf.find(1, 2));

    uf.unite(3, 4);
    uf.unite(2, 3);
    REQUIRE(uf.find(1, 4));


}