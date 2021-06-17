#pragma once
#include "ITree.h"
#include <algorithm>
template <typename T>
class SplayTree : public ITree<T> {
public:
    struct node {
        struct node* left;
        struct node* right;
        struct node* parent;
        T data;
        node(const T& key) { data = key; left = nullptr; right = nullptr; parent = nullptr; }
    };

private:
    node* root;
    
    /*
    дописать сплей
    */
    void _Transplant(node* localParent, node* localChild) {
        if (localParent->parent == nullptr)
            root = localChild;
        else if (localParent == localParent->parent->left)
            localParent->parent->left = localChild;
        else if (localParent == localParent->parent->right)
            localParent->parent->right = localChild;

        if (localChild != nullptr)
            localChild->parent = localParent->parent;
    }

    void _LeftRotate(node* localRoot) {
        node* right = localRoot->right;

        localRoot->right = right->left;
        if (right->left != nullptr)
            right->left->parent = localRoot;

        _Transplant(localRoot, right);

        right->left = localRoot;
        right->left->parent = right;
    }

    void _RightRotate(node* localRoot) {
        node* left = localRoot->left;

        localRoot->left = left->right;
        if (left->right != nullptr)
            left->right->parent = localRoot;

        _Transplant(localRoot, left);

        left->right = localRoot;
        left->right->parent = left;
    }

    void _Splay(node* pivotElement) {
        while (pivotElement != root && pivotElement->parent) {
            if (pivotElement->parent == root || !pivotElement->parent->parent) {

                if (pivotElement == pivotElement->parent->left) {
                    _RightRotate(pivotElement->parent);
                }
                else if (pivotElement == pivotElement->parent->right) {
                    _LeftRotate(pivotElement->parent);
                }
            }
            else {
                // Zig-Zig step.
                if (pivotElement == pivotElement->parent->left &&
                    pivotElement->parent == pivotElement->parent->parent->left) {

                    _RightRotate(pivotElement->parent->parent);
                    _RightRotate(pivotElement->parent);

                }
                else if (pivotElement == pivotElement->parent->right &&
                    pivotElement->parent == pivotElement->parent->parent->right) {

                    _LeftRotate(pivotElement->parent->parent);
                    _LeftRotate(pivotElement->parent);
                }
                // Zig-Zag step.
                else if (pivotElement == pivotElement->parent->right &&
                    pivotElement->parent == pivotElement->parent->parent->left) {

                    _LeftRotate(pivotElement->parent);
                    _RightRotate(pivotElement->parent);

                }
                else if (pivotElement == pivotElement->parent->left &&
                    pivotElement->parent == pivotElement->parent->parent->right) {

                    _RightRotate(pivotElement->parent);
                    _LeftRotate(pivotElement->parent);
                }
            }
        }
    }

    void split(node* p, const T& key, node** treeL, node** treeR) {
        if (!p) {
            *treeL = nullptr;
            *treeR = nullptr;
            return;
        }
        p = _search(p, key);
        if (p->data == key) {
            if (p->left)
                p->left->parent = nullptr;
            if (p->right)
                p->right->parent = nullptr;
            *treeL = p->left;
            *treeR = p->right;
        }
        else if(p->data < key) {
            if(p->right)
                p->right->parent = nullptr;
            p->parent = nullptr;
            *treeL = p;
            *treeR = p->right;
            (*treeL)->right = nullptr;
        }
        else {
            if (p->left)
                p->left->parent = nullptr;
            p->parent = nullptr;
            *treeL = p->left;
            *treeR = p;
            (*treeR)->left = nullptr;
        }
    }

    void insert(node* p, const T& k)
    {
        node* l = nullptr;
        node* r = nullptr;
        split(p, k, &l, &r);
        root = new node(k);
        root->left = l;
        root->right = r;
        if(l)
            root->left->parent = root;
        if(r)
            root->right->parent = root;
    }

    node* merge(node* lTree, node* rTree) {
        if (!lTree && !rTree)
            return nullptr;
        if (!lTree)
            return rTree;
        if (!rTree)
            return lTree;
        rTree = _search(rTree, lTree->data);
        rTree->left = lTree;
        lTree->parent = rTree;
        return rTree;
    }

    node* remove(node* p, const T& key) {
        node* k = _search(p, key);
        if (!k || k->data != key) {
            return p;
        }
        node* r = k->right;
        node* l = k->left;
        delete k;
        if(l)
            l->parent = nullptr;
        if(r)
            r->parent = nullptr;
        return merge(l, r);
    }

    node* _search(node* p, const T& key) {
        if (!p) {
            return nullptr;
        }
        if (p->data == key) {
            _Splay(p);
            return p;
        }
        if (p->right && key > p->data) {
            return _search(p->right, key);
        }
        if(p->left && key < p->data){
            return _search(p->left, key);
        }
        _Splay(p);
        return p;
    }
public:
    SplayTree() { root = nullptr; }

    void Insert(const T& key) {
        insert(root, key);
    }
    bool Search(const T& key) {
        root = _search(root, key);
        return root && root->data == key;
    }
    bool IsEmpty() {
        return root == nullptr;
    }
    void Remove(const T& key) {
        root = remove(root, key);
    }
    ~SplayTree() { }
};