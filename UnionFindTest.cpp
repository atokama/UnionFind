#include <vector>

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

class UnionFind {
public:
    using Size = std::size_t;

    UnionFind() {
        arr_[0] = 0;
        size_[0] = 1;
    }

    void unite(Size a, Size b) {
        check(a);
        check(b);
        auto ra = root(a);
        auto rb = root(b);
        if (ra == rb) {
            return;
        } else if (size_[ra] < size_[rb]) {
            arr_[ra] = arr_[rb];
            size_[rb] += size_[ra];
        } else {
            arr_[rb] = arr_[ra];
            size_[ra] += size_[rb];
        }
    }

    bool find(Size a, Size b) {
        check(a);
        check(b);
        return root(a) == root(b);
    }

private:
    Size root(Size a) {
        while (arr_[a] != a) {
            a = arr_[a];
        }
        return a;
    }

    void check(Size a) {
        if (!arr_.count(a)) {
            arr_[a] = a;
            size_[a] = 1;
        }
    }

    std::map<Size, Size> arr_, size_;
};

TEST_CASE("UnionFind", "[UnionFind]") {
    UnionFind uf{};
    REQUIRE(!uf.find(1, 2));
    uf.unite(1, 2);
    REQUIRE(uf.find(1, 2));

    uf.unite(3, 4);
    uf.unite(2, 3);
    REQUIRE(uf.find(1, 4));

    uf.unite(1, 10);
    REQUIRE(uf.find(1, 10));
}