#include "gtest/gtest.h"
#include "treap.h"

TEST(treap, find)
{
    m110h::Treap<int> t;

    t.Insert(10);
    t.Insert(20);
    t.Insert(20);
    t.Insert(30);

    EXPECT_TRUE(t.Find(10));
    EXPECT_TRUE(t.Find(20));
    EXPECT_TRUE(t.Find(30));

    t.Remove(10);

    EXPECT_FALSE(t.Find(10));
    EXPECT_TRUE(t.Find(20));
    EXPECT_TRUE(t.Find(30));

    t.Remove(20);
    EXPECT_TRUE(t.Find(20));

    t.Remove(20);
    EXPECT_FALSE(t.Find(20));
}
