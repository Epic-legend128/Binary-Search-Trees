#include "BST.hpp"

// (Red-Black Tree)/(Self Balancing BST)
class RBT: public BST {
    private:
        /* Balance RB Tree after insertion
        @param root is root of the tree
        @param p is the node where the color distruption needs fixing */
        void fix_insert(node* root, node* p) {
            while (p->parent != nullptr && p->parent->isRed) {
                if (p->parent == p->parent->parent->left) {
                    node* y = p->parent->parent->right;
                    if (y != nullptr && y->isRed) {
                        p->parent->isRed = false;
                        y->isRed = false;
                        p->parent->parent->isRed = true;
                        p = p->parent->parent;
                    }
                    else {
                        if (p == p->parent->right) {
                            p = p->parent;
                            rotate_left(p);
                        }
                        p->parent->isRed = false;
                        p->parent->parent->isRed = true;
                        rotate_right(p->parent->parent);
                    }
                }
                else {
                    node* y = p->parent->parent->left;
                    if (y != nullptr && y->isRed) {
                        p->parent->isRed = false;
                        y->isRed = false;
                        p->parent->parent->isRed = true;
                        p = p->parent->parent;
                    }
                    else {
                        if (p == p->parent->left) {
                            p = p->parent;
                            rotate_right(p);
                        }
                        p->parent->isRed = false;
                        p->parent->parent->isRed = true;
                        rotate_left(p->parent->parent);
                    }
                }
            }
            this->root->isRed = false;
        }
        
        /* Insert node in RB Tree
        @param root root of the tree
        @param p node to be inserted */
        void insert(node* &root, int p) override {
            if (p > root->data) {
                if (root->right == nullptr) {
                    node* t = new node(p);
                    root->right = t;
                    t->parent = root;
                    t->isRed = true;
                    fix_insert(root, t);
                    return;
                }
                insert(root->right, p);
            }
            else {
                if (root->left == nullptr) {
                    node* t = new node(p);
                    root->left = t;
                    t->parent = root;
                    t->isRed = true;
                    fix_insert(root, t);
                    return;
                }
                insert(root->left, p);
            }
        }

        /* Rotate right 
        @param n node on which right rotation takes place */
        void rotate_right(node* n) {
            if (n->left == nullptr) return;

            if (n == root) root = n->left;
            else {
                if (n->parent->right == n) n->parent->right = n->left;
                else n->parent->left = n->left;
            }

            node* temp = n->left->right;
            if (temp != nullptr) n->left->right->parent = n;
            n->left->right = n;
            n->left->parent = n->parent;
            n->parent = n->left;
            n->left = temp;
        }

        /* Rotate left
        @param n node on which left rotation takes place */
        void rotate_left(node* n) {
            if (n->right == nullptr) return;

            if (n == root) root = n->right;
            else {
                if (n->parent->right == n) n->parent->right = n->right;
                else n->parent->left = n->right;
            }

            node* temp = n->right->left;
            if (temp != nullptr) n->right->left->parent = n;
            n->right->left = n;
            n->right->parent = n->parent;
            n->parent = n->right;
            n->right = temp;
        }
        
    public:
        RBT(int data) {
            this->root->data = data;
        }

        RBT() = default;

        /* Insert node in RB Tree
        @param p node to be inserted */
        void insert(int p) override {
            insert(this->root, p);
        }
};