#include "gtest/gtest.h"
#include "treap.h"

TEST(treap, build)
{
    m110h::Treap<int> t;

    for (int i=0; i<100000; i++)
        t.Insert(i);
}
