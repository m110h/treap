#ifndef _TREAP_H_
#define _TREAP_H_

#include <chrono>
#include <random>
#include <limits>

// https://en.wikipedia.org/wiki/Treap
// http://blog.ruofeidu.com/treap-in-45-lines-of-c/
// https://habr.com/en/post/112394/
// https://e-maxx.ru/algo/treap

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
        int c {0}; // an amount of nodes that belong a subtree (include this Node)

        Node *l {nullptr};
        Node *r {nullptr};

        Node(): data(0) {}
        Node(const T& _data): data(_data) {}

        ~Node() {}
    };

private:
    Node *root {nullptr};
    Node *null {nullptr};

public:
    explicit Treap() { null=new Node; null->y=INF; root=null; }

    Treap(Treap& src) = delete;

    Treap(Treap&& src)
    {
        root=src.root; null=src.null;
        src.root=src.null=nullptr;
    }

    Treap& operator=(const Treap& r) = delete;

    ~Treap()
    {
        Clear();
        if (null) { delete null; null=nullptr; }
    }

    void Insert(Node *&p, const T& _data)
    {
        if (p == null)
        {
            p = new Node(_data); p->c=1; p->y=Rnd(); p->l=null; p->r=null;
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
        if (p == null) return;

        if (p->data == _data)
            Remove(p);
        else if (_data < p->data)
            Remove(p->l, _data);
        else
            Remove(p->r, _data);

        if (p!=null) Update(p);
    }

    void Remove(Node *&p)
    {
        if ( p->l == null && p->r == null )
        {
            delete p; p=null; return;
        }

        if ( p->l->y < p->r->y )
        {
            RotateLeft(p); Remove(p->r);
        }
        else
        {
            RotateRight(p); Remove(p->l);
        }

        Update(p);
    }

    void Remove(const T& _data){ Remove(root, _data); }

    /*
    bool Find(Node *&p, T _data)
    {
        if (p == null)
            return false;

        if (_data == p->data)
            return true;

        if (_data < p->data)
            return Find(p->l, _data);
        else
            return Find(p->r, _data);
    }
    */

    bool Find(Node *&p, const T& _data)
    {
        Node* tmp(p);

        while (tmp != null)
        {
            if (tmp->data == _data)
            {
                return true;
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

        return false;
    }

    bool Find(T _data){ return Find(root, _data); }

    Node* FindBestFit(Node *&p, const T& _data)
    {
        Node* tmp(p);
        Node* bestfit {nullptr};

        while (tmp != null)
        {
            if (tmp->data == _data)
            {
                bestfit = tmp; break;
            }
            else if (tmp->data < _data)
            {
                //std::cout << "(right) in to " << tmp->r->data << " from " << tmp->data << std::endl;
                tmp = tmp->r;
            }
            else
            {
                //std::cout << "(left) in to " << tmp->l->data << " from " << tmp->data << std::endl;
                bestfit = tmp; tmp = tmp->l;
            }
        }

        return bestfit;
    }

    Node* FindBestFit(const T& _data) { return FindBestFit(root, _data); }

    int Depth(Node *&p, int current_depth)
    {
        if (p == null) return current_depth;

        int ldepth = Depth(p->l, current_depth + 1);
        int rdepth = Depth(p->r, current_depth + 1);

        return (ldepth < rdepth) ? rdepth : ldepth;
    }

    int Depth()
    {
        return Depth(root, 0);
    }

    void Clear()
    {
        if (root && null) while (root != null) Remove(root);
    }

private:
    int Rnd()
    {
        static std::mt19937 _generator(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> _range(0, INF);
        return _range(_generator);
    }

    void Update(Node *&p)
    {
        if (p != null)
        {
            p->c = p->l->c + p->r->c + 1;
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
