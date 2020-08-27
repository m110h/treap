#include "gtest/gtest.h"
#include "treap.h"

TEST(treap, move)
{
    m110h::Treap<int> t;

    int n = 100000;

    for (int i=0; i<n; i++)
        t.Insert(i);

    auto t2 = std::move(t);

    for (int i=0; i<n; i++)
        EXPECT_TRUE(t2.IsExists(i));
}
