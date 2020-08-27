#include "gtest/gtest.h"

#include "treap.h"

TEST(treap, depth)
{
	m110h::Treap<int> t;

	ASSERT_EQ(t.Depth(), 0);

	int n = 10;

	// 10^2
	n *= 10;
	for (int i=0; i<n; i++) t.Insert(i);
	EXPECT_TRUE(t.Depth() <= 20);
	t.Clear();

	// 10^3
	n *= 10;
	for (int i=0; i<n; i++) t.Insert(i);
	EXPECT_TRUE(t.Depth() <= 30);
	t.Clear();

	// 10^4
	n *= 10;
	for (int i=0; i<n; i++) t.Insert(i);
	EXPECT_TRUE(t.Depth() <= 40);
	t.Clear();

	// 10^5
	n *= 10;
	for (int i=0; i<n; i++) t.Insert(i);
	EXPECT_TRUE(t.Depth() <= 50);
	t.Clear();

	// 10^6
	n *= 10;
	for (int i=0; i<n; i++) t.Insert(i);
	EXPECT_TRUE(t.Depth() <= 60);
	t.Clear();

    t.Clear();
	ASSERT_EQ(t.Depth(), 0);
}
