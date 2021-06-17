#pragma once

#include "ITree.h"

template <typename T>
class AvlTree : public ITree<T>
{
public:
    struct node {
        struct node* left;
        T data;
        char balance;
        struct node* right;
        node(const T& key) { data = key; left = nullptr; right = nullptr; balance = 0; }
    };
private:
    node* root;
    node* smallLeftRotation(node* a) {
        node* b = a->right;
        a->right = b->left;
        b->left = a;
        fixheight(b);
        fixheight(a);
        return b;
    }
    node* smallRightRotation(node* a) {
        node* b = a->left;
        a->left = b->right;
        b->right = a;
        fixheight(b);
        fixheight(a);
        return b;
    }
    void fixheight(node* a) {
        char hl = a->left ? a->left->balance : 0;
        char hr = a->right ? a->right->balance : 0;
        a->balance = hl - hr;
    }
    node* _insert(node* p, const T& key) {
        if (!p) return new node(key);
        if (key < p->data)
            p->left = _insert(p->left, key);
        else
            p->right = _insert(p->right, key);
        return balance(p);
    }
    node* balance(node* p) {
        fixheight(p);
        if (p->balance == -2) //перекос вправо
        {
            if (p->right->balance > 0)
                p->right = smallRightRotation(p->right);
            return smallLeftRotation(p);
        }
        if (p->balance == 2) //перекос влево
        {
            if (p->left->balance < 0)
                p->left = smallLeftRotation(p->left);
            return smallRightRotation(p);
        }
        return p; // балансировка не нужна
    }
    bool _search(node* p, const T& key) {
        if (!p) {
            return false;
        }
        if (p->data == key) {
            return true;
        }
        else if (key > p->data) {
            return _search(p->right, key);
        }
        else {
            return _search(p->left, key);
        }
    }
    node* _findmin(node* p) {
        if (p->left)
            return _findmin(p->left);
        else
            return p;
    }
    node* _remove(node* p, const T& key) {
        if (!p) {
            return nullptr;
        }
        if (p->data == key) {
            node* l = p->left;
            node* r = p->right;
            if (p == root)
                root = nullptr;
            delete p;
            p = nullptr;
            if (r) {
                node* minNode = _findmin(r);
                minNode->left = l;
                return r;
            }
            else if(l) {
                return l;
            }
        }
        else if (key < p->data) {
            p->left = _remove(p->left, key);
        }
        else {
            p->right = _remove(p->right, key);
        }
        if (p)
            return balance(p);
        else
            return nullptr;
    }
public:
    AvlTree() {
        root = nullptr;
    }
    void Insert(const T& key) {
        if(root)
            _insert(root, key);
        else {
            root = _insert(root, key);
        }
    }
    bool Search(const T& key) {
        return _search(this->root, key);
    }
    bool isEmpty() {
        return root == nullptr;
    }
    void Remove(const T& key) {
        _remove(root, key);
    }
};