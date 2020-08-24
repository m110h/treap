# Treap

Description from wiki:

"In computer science, the treap and the randomized binary search tree are two closely related forms of binary search tree data structures that maintain a dynamic set of ordered keys and allow binary searches among the keys. After any sequence of insertions and deletions of keys, the shape of the tree is a random variable with the same probability distribution as a random binary tree; in particular, with high probability its height is proportional to the logarithm of the number of keys, so that each search, insertion, or deletion operation takes logarithmic time to perform."

https://en.wikipedia.org/wiki/Treap

# About

It's a header only implementation that uses STL for generating random priorities.

# Additional material

* http://blog.ruofeidu.com/treap-in-45-lines-of-c/ (Eng)
* https://habr.com/en/post/112394/ (Rus)
* https://e-maxx.ru/algo/treap (Rus)

# Build

$ git clone https://github.com/m110h/treap.git
$ cd treap
$ mkdir build
$ cd build
$ cmake ..
$ make

# License

MIT
