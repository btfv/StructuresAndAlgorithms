#pragma once

#include "ITree.h"

template <typename T>
class AvlTree : public ITree<T>
{
public:
    struct node {
        struct node* left;
        T data;
        int height;
        struct node* right;
    };
private:
    node* root;

    node* _Insert(node* r, const T& data) {
        if (r == nullptr) {
            node* n = new node();
            n->data = data;
            r = n;
            r->left = r->right = nullptr;
            r->height = 1;
            return r;
        }
        else {
            if (data < r->data)
                r->left = _Insert(r->left, data);
            else
                r->right = _Insert(r->right, data);
        }

        r->height = calheight(r);

        if (bf(r) == 2 && bf(r->left) == 1) {
            r = llrotation(r);
        }
        else if (bf(r) == -2 && bf(r->right) == -1) {
            r = rrrotation(r);
        }
        else if (bf(r) == -2 && bf(r->right) == 1) {
            r = rlrotation(r);
        }
        else if (bf(r) == 2 && bf(r->left) == -1) {
            r = lrrotation(r);
        }

        return r;
    }

    node* _Remove(node* p, T& data) {

        if (p->left == nullptr && p->right == nullptr) {
            if (p == this->root)
                this->root = nullptr;
            delete p;
            return nullptr;
        }

        node* t;
        node* q;
        if (p->data < data) {
            p->right = _Remove(p->right, data);
        }
        else if (p->data > data) {
            p->left = _Remove(p->left, data);
        }
        else {
            if (p->left != nullptr) {
                q = inpre(p->left);
                p->data = q->data;
                p->left = _Remove(p->left, q->data);
            }
            else {
                q = insuc(p->right);
                p->data = q->data;
                p->right = _Remove(p->right, q->data);
            }
        }

        if (bf(p) == 2 && bf(p->left) == 1) { p = llrotation(p); }
        else if (bf(p) == 2 && bf(p->left) == -1) { p = lrrotation(p); }
        else if (bf(p) == 2 && bf(p->left) == 0) { p = llrotation(p); }
        else if (bf(p) == -2 && bf(p->right) == -1) { p = rrrotation(p); }
        else if (bf(p) == -2 && bf(p->right) == 1) { p = rlrotation(p); }
        else if (bf(p) == -2 && bf(p->right) == 0) { p = llrotation(p); }


        return p;
    }

    node* inpre(node* p) {
        while (p->right != nullptr)
            p = p->right;
        return p;
    }

    node* insuc(node* p) {
        while (p->left != nullptr)
            p = p->left;

        return p;
    }

    int calheight(node* p) {
        if (p->left && p->right) {
            if (p->left->height < p->right->height)
                return p->right->height + 1;
            else return  p->left->height + 1;
        }
        else if (p->left && p->right == nullptr) {
            return p->left->height + 1;
        }
        else if (p->left == nullptr && p->right) {
            return p->right->height + 1;
        }
        return 0;

    }

    int bf(node* n) {
        if (n->left && n->right) {
            return n->left->height - n->right->height;
        }
        else if (n->left && n->right == nullptr) {
            return n->left->height;
        }
        else if (n->left == nullptr && n->right) {
            return -n->right->height;
        }
    }

    node* _Search(const T& key) {
        node* searchedElement = root;
        while (searchedElement != nullptr) {
            if (searchedElement->data < key)
                searchedElement = searchedElement->right;
            else if (key < searchedElement->data)
                searchedElement = searchedElement->left;
            else if (searchedElement->data == key) {
                return searchedElement;
            }
        }

        return nullptr;
    }

    void _RemoveTree(node* p) {
        if (p == nullptr)
            return;
        node* l = p->left;
        node* r = p->right;
        delete p;
        _RemoveTree(l);
        _RemoveTree(r);
    }
public:
    AvlTree() {
        this->root = nullptr;
    }

    node* llrotation(node* n) {
        node* p;
        node* tp;
        p = n;
        tp = p->left;

        p->left = tp->right;
        tp->right = p;

        return tp;
    }


    node* rrrotation(node* n) {
        node* p;
        node* tp;
        p = n;
        tp = p->right;

        p->right = tp->left;
        tp->left = p;

        return tp;
    }


    node* rlrotation(node* n) {
        node* p;
        node* tp;
        node* tp2;
        p = n;
        tp = p->right;
        tp2 = p->right->left;

        p->right = tp2->left;
        tp->left = tp2->right;
        tp2->left = p;
        tp2->right = tp;

        return tp2;
    }

    node* lrrotation(node* n) {
        node* p;
        node* tp;
        node* tp2;
        p = n;
        tp = p->left;
        tp2 = p->left->right;

        p->left = tp2->right;
        tp->right = tp2->left;
        tp2->right = p;
        tp2->left = tp;

        return tp2;
    }

    void Insert(const T& key) {
        _Insert(root, key);
    }    

    void Remove(T& key) {
        _Remove(root, key);
    }

    bool isEmpty() {
        return root == nullptr;
    }

    bool Search(const T& key) { return _Search(key) != nullptr; }

    ~AvlTree() {
        _RemoveTree(root);
    }
};