#include "BST.hpp"

// (Red-Black Tree)/(Self Balancing BST)
class RBT: public BST {
    private:
        /* Balance RB Tree after insertion
        @param root is root of the tree
        @param p node where the color distruption needs fixing */
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
        
        /* Places b into a's position
        @param a parent node
        @param b child node */
        void transplant(node* a, node* b) {
            if (a->parent == nullptr) this->root = b;
            else if (a == a->parent->left) a->parent->left = b;
            else a->parent->right = b;
            if (b != nullptr) b->parent = a->parent;
        }

        /* Balance RB Tree after deletion
        @param x node where the color distruption needs fixing */
        void fix_delete(node* x, node* xParent) {
            while (x != this->root && (x == nullptr || !x->isRed)) {
                if (xParent->left == x) {
                    node* w = xParent->right;
                    
                    //case 1 red sibling
                    if (w != nullptr && w->isRed) {
                        w->isRed = false;
                        xParent->isRed = true;
                        rotate_left(xParent);
                        w = xParent->right;
                    }

                    //case 2 sibling's children are black
                    if ((w->left == nullptr || !w->left->isRed) && (w->right == nullptr || !w->right->isRed)) {
                        w->isRed = true;
                        x = xParent;
                        xParent = xParent->parent;
                    }
                    else {
                        //case 3 sibling's left child is red, right child is black
                        if (w->right == nullptr || !w->right->isRed) {
                            if (w->left != nullptr) w->left->isRed = false;
                            w->isRed = true;
                            rotate_right(w);
                            w = xParent->right;
                        }

                        //case 4 sibling's right child is red
                        w->isRed = xParent->isRed;
                        xParent->isRed = false;
                        if (w->right != nullptr) w->right->isRed = false;
                        rotate_left(xParent);
                        x = this->root;
                    }
                }
                else { // symmetrical
                    node* w = xParent->left;
                    
                    if (w != nullptr && w->isRed) {
                        w->isRed = false;
                        xParent->isRed = true;
                        rotate_right(xParent);
                        w = xParent->left;
                    }

                    if ((w->left == nullptr || !w->left->isRed) && (w->right == nullptr || !w->right->isRed)) {
                        w->isRed = true;
                        x = xParent;
                        xParent = xParent->parent;
                    }
                    else {
                        if (w->left == nullptr || !w->left->isRed) {
                            if (w->right != nullptr) w->right->isRed = false;
                            w->isRed = true;
                            rotate_left(w);
                            w = xParent->left;
                        }

                        w->isRed = xParent->isRed;
                        xParent->isRed = false;
                        if (w->left != nullptr) w->left->isRed = false;
                        rotate_right(xParent);
                        x = this->root;
                    }
                }
            }
            if (x != nullptr) x->isRed = false;
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

        /* Delete node from RB Tree
        @param n node to be deleted */
        void del(node* n) {
            if (n == nullptr) return;
            node* x = new node();
            node* xParent = new node();
            bool mnIsRed = n->isRed;
            if (n->left == nullptr) {
                x = n->right;
                xParent = n;
                transplant(n, n->right);
            }
            else if (n->right == nullptr) {
                x = n->left;
                xParent = n;
                transplant(n, n->left);
            }
            else {
                node* mn = find_min(n->right);
                mnIsRed = mn->isRed;
                x = mn->right;
                if (mn->parent == n) {
                    xParent = mn;
                    if (x != nullptr) x->parent = mn;
                }
                else {
                    xParent = mn->parent;
                    transplant(mn, mn->right);
                    mn->right = n->right;
                    mn->right->parent = mn;
                }
                transplant(n, mn);
                mn->left = n->left;
                mn->left->parent = mn;
                mn->isRed = n->isRed;
                
                if (n->parent == nullptr) {
                    this->root = mn;
                    mn->isRed = false;
                    mnIsRed = true;
                }
            }

            if (!mnIsRed) {
                fix_delete(x, xParent);
            }
        }

        /* Delete node from RB Tree
        @param n value of node to be deleted */
        void del(int n) {
            node* x = find(n);
            if (x != nullptr) del(x);
        }
};






