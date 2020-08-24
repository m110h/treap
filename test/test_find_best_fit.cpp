#include "gtest/gtest.h"
#include "treap.h"

TEST(treap, find_best_fit)
{
    m110h::Treap<int> t;

    t.Insert(32);
    t.Insert(64);
    t.Insert(128);
    t.Insert(256);
    t.Insert(512);
    t.Insert(1024);

    ASSERT_TRUE(t.Find(32));
    ASSERT_TRUE(t.Find(64));
    ASSERT_TRUE(t.Find(128));
    ASSERT_TRUE(t.Find(256));
    ASSERT_TRUE(t.Find(512));
    ASSERT_TRUE(t.Find(1024));

    EXPECT_EQ(t.FindBestFit(30)->data, 32);
    EXPECT_EQ(t.FindBestFit(254)->data, 256);
    EXPECT_EQ(t.FindBestFit(999)->data, 1024);
    EXPECT_EQ(t.FindBestFit(1024)->data, 1024);
    EXPECT_EQ(t.FindBestFit(32)->data, 32);
}
