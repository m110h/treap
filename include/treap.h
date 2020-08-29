#ifndef _TREAP_H_
#define _TREAP_H_

#include <chrono>
#include <random>
#include <limits>

namespace m110h
{

template<typename T>
class Treap
{
    static const int INF = std::numeric_limits<int>::max();

public:
    /*
            [node]
            |    |
        right    left
    */
    struct Node
    {
        T data;

        int y {0}; // a random value for balancing a tree
        int c {0}; // an amount of nodes that belong to subtree (include this Node)

        Node *l {nullptr};
        Node *r {nullptr};

        Node(): data(0) {}
        Node(const T& _data): data(_data) {}

        ~Node() {}
    };

private:
    Node *root {nullptr};

public:
    explicit Treap() {}

    Treap(Treap& src) = delete;

    Treap(Treap&& src)
    {
        root=src.root; src.root=nullptr;
    }

    Treap& operator=(const Treap& r) = delete;

    ~Treap() { Clear(); }

    void Insert(Node *&p, const T& _data)
    {
        if (p == nullptr)
        {
            p = new Node(_data); p->c=1; p->y=Rnd();
        }
        else if (_data < p->data)
        {
            Insert(p->l, _data);
            if (p->l->y < p->y) RotateLeft(p);
        }
        else
        {
            Insert(p->r, _data);
            if (p->r->y < p->y) RotateRight(p);
        }

        Update(p);
    }

    void Insert(const T& _data){ Insert(root, _data); }

    void Remove(Node *&p, const T& _data)
    {
        if (p == nullptr) return;

        if (p->data == _data)
            Remove(p);
        else if (_data < p->data)
            Remove(p->l, _data);
        else
            Remove(p->r, _data);

        if (p) Update(p);
    }

    void Remove(Node *&p)
    {
        if ( p->l == nullptr && p->r == nullptr )
        {
            delete p; p=nullptr; return;
        }

        if (p->l && p->r)
        {
            if ( p->l->y < p->r->y )
            {
                RotateLeft(p); Remove(p->r);
            }
            else
            {
                RotateRight(p); Remove(p->l);
            }
        }
        else if (p->l)
        {
            RotateLeft(p); Remove(p->r);
        }
        else
        {
            RotateRight(p); Remove(p->l);
        }

        if (p) Update(p);
    }

    void Remove(const T& _data){ Remove(root, _data); }

    Node* Find(Node *&p, const T& _data)
    {
        Node* tmp(p);

        while (tmp)
        {
            if (tmp->data == _data)
            {
                return tmp;
            }
            else if (tmp->data > _data)
            {
                tmp = tmp->l;
            }
            else
            {
                tmp = tmp->r;
            }
        }

        return nullptr;
    }

    Node* Find(T _data){ return Find(root, _data); }

    bool IsExists(Node *&p, const T& _data)
    {
        Node* tmp = Find(_data);
        if (tmp) return true;
        return false;
    }

    bool IsExists(T _data){ return IsExists(root, _data); }

    Node* FindBestFit(Node *&p, const T& _data)
    {
        Node* tmp(p);
        Node* bestfit {nullptr};

        while (tmp)
        {
            if (tmp->data == _data)
            {
                bestfit = tmp; break;
            }
            else if (tmp->data < _data)
            {
                tmp = tmp->r;
            }
            else
            {
                bestfit = tmp; tmp = tmp->l;
            }
        }

        return bestfit;
    }

    Node* FindBestFit(const T& _data) { return FindBestFit(root, _data); }

    int Depth(Node *&p, int depth)
    {
        if (p == nullptr) return depth;

        int ldepth = Depth(p->l, depth + 1);
        int rdepth = Depth(p->r, depth + 1);

        return (ldepth < rdepth) ? rdepth : ldepth;
    }

    int Depth()
    {
        return Depth(root, 0);
    }

    void Clear()
    {
        while (root) Remove(root->data);
    }

private:
    int Rnd()
    {
        static std::mt19937 _generator(std::chrono::system_clock::now().time_since_epoch().count());
        static std::uniform_int_distribution<int> _range(0, INF);

        return _range(_generator);
    }

    void Update(Node *&p)
    {
        if (p)
        {
            p->c = 1;

            if (p->l) p->c += p->l->c;
            if (p->r) p->c += p->r->c;
        }
    }

    void RotateLeft(Node *&p)
    {
        Node* tmp=p->l;
        p->l=tmp->r;
        tmp->r=p;

        Update(p);
        Update(tmp);

        p=tmp;
    }

    void RotateRight(Node *&p)
    {
        Node* tmp=p->r;
        p->r=tmp->l;
        tmp->l=p;

        Update(p);
        Update(tmp);

        p=tmp;
    }
};

}

#endif
