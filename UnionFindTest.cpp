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
    }

    void unite(std::size_t a, std::size_t b) {
        if (check(a, b)) {
            auto t{arr_[b]};
            for(std::size_t i{0}; i != arr_.size(); ++i) {
                if (arr_[i] == t) {
                    arr_[i] = arr_[a];
                }
            }
        }
    }

    bool find(std::size_t a, std::size_t b) {
        if (check(a, b)) {
            return arr_[a] == arr_[b];
        }
        return false;
    }

private:
    bool check(std::size_t a, std::size_t b) {
        return a < arr_.size() && b < arr_.size();
    }

    std::vector<std::size_t> arr_;
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