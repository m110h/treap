#include "gtest/gtest.h"
#include "treap.h"

#include <random>
#include <chrono>

TEST(treap, depth)
{
	m110h::Treap<int> t;

    std::mt19937 _generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> _range(0, std::numeric_limits<int>::max());

	int _depth = t.Depth();

	ASSERT_EQ(_depth, 0);

    for (int i=0; i<10000; i++)
    {
        t.Insert(_range(_generator));
    }

    t.Clear();
    _depth = t.Depth();

	ASSERT_EQ(_depth, 0);
}
