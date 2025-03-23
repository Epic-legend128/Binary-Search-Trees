#include <vector>
#include <algorithm>

struct node {
    int data;
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;

    node(int d) {
        data = d;
    }

    node() = default;
};

class BST {
    private:
        node* root = new node();

        /* Returns minimum height of the tree
        @param root root of the BST */
        int min_height(node* root) {
            if (root == nullptr) return 0;
            return 1 + std::min(min_height(root->left), min_height(root->right));
        }

        /* Returns height of the tree
        @param root root of the tree */
        int height(node* root) {
            if (root == nullptr) return 0;
            return 1 + std::max(height(root->left), height(root->right));
        }

        /* Returns maximum valued node
        @param root root of the tree */
        node* find_max(node* root) {
            if (root->right == nullptr) return root;
            return find_max(root->right);
        }

        /* Returns minimum valued node
        @param root root of the tree */
        node* find_min(node* root) {
            if (root->left == nullptr) return root;
            return find_min(root->left);
        }

        /* Searches and returns a node, returns nullptr if node doesn't exist
        @param root root of the tree 
        @param key value that you are searching for */
        node* find(node* root, int key) {
            if (root == nullptr) return nullptr;
            if (root->data > key) return find(root->left, key);
            else if (root->data < key) return find(root->right, key);
            return root;
        }

        /* Inorder representation(left, root, right)
        @param root root of the tree
        @param arr vector which holds the inorder representation */
        void inorder(node* root, std::vector<int>& arr) {
            if (root == nullptr) return;
            inorder(root->left, arr);
            arr.push_back(root->data);
            inorder(root->right, arr);
        }

        /* Preorder representation(root, left, right)
        @param root root of the tree
        @param arr vector which holds the preorder representation */
        void preorder(node* root, std::vector<int>& arr) {
            if (root == nullptr) return;
            arr.push_back(root->data);
            preorder(root->left, arr);
            preorder(root->right, arr);
        }

        /* Postorder representation(left, right, root)
        @param root root of the tree
        @param arr vector which holds the postorder representation */
        void postorder(node* root, std::vector<int>& arr) {
            if (root == nullptr) return;
            postorder(root->left, arr);
            postorder(root->right, arr);
            arr.push_back(root->data);
        }

        /* Insert node in BST
        @param root root of the tree
        @param p node to be inserted */
        void insert(node* &root, int p) {
            if (p > root->data) {
                if (root->right == nullptr) {
                    node* t = new node(p);
                    root->right = t;
                    t->parent = root;
                    return;
                }
                insert(root->right, p);
            }
            else {
                if (root->left == nullptr) {
                    node* t = new node(p);
                    root->left = t;
                    t->parent = root;
                    return;
                }
                insert(root->left, p);
            }
        }
    public:
        BST(int data) {
            this->root->data = data;
        }

        BST() = default;

        /* Returns minimum height of the tree */
        int min_height() {
            return min_height(this->root);
        }

        /* Returns height of the tree */
        int height() {
            return height(this->root);
        }

        /* Returns maximum valued node */
        node* find_max() {
            return find_max(this->root);
        }

        /* Returns minimum valued node */
        node* find_min() {
            return find_min(this->root);
        }

        /* Searches and returns a node, returns nullptr if node doesn't exist
        @param key value that you are searching for */
        node* find(int key) {
            return find(this->root, key);
        }

        /* Inorder representation(left, root, right)
        @param arr vector which holds the inorder representation */
        void inorder(std::vector<int>& arr) {
            inorder(this->root, arr);
        }

        /* Preorder representation(root, left, right)
        @param arr vector which holds the preorder representation */
        void preorder(std::vector<int>& arr) {
            preorder(this->root, arr);
        }

        /* Postorder representation(left, right, root)
        @param arr vector which holds the postorder representation */
        void postorder(std::vector<int>& arr) {
            postorder(this->root, arr);
        }

        /* Insert node in BST
        @param p node to be inserted */
        void insert(int p) {
            insert(this->root, p);
        }

        /* Returns root of the tree */
        node* get_root() {
            return this->root;
        }

        /* Delete node from the BST
        @param n node to be deleted */
        void del(node* n) {
            if (n == nullptr) return;

            if (n->left == nullptr && n->right == nullptr) {
                if (n->parent == nullptr) {
                    root = nullptr;
                    return;
                }
                else {
                    if (n->parent->left != nullptr && n->parent->left == n) {
                        n->parent->left = nullptr;
                    }
                    else if (n->parent->right != nullptr && n->parent->right == n) {
                        n->parent->right = nullptr;
                    }
                }
            }
            else if (n->left == nullptr) {
                n->right->parent = n->parent;
                if (n->parent != nullptr) {
                    if (n->parent->left != nullptr && n->parent->left == n) n->parent->left = n->right;
                    else if (n->parent->right != nullptr && n->parent->right == n) n->parent->right = n->right;
                }
                else {
                    root = n->right;
                }
            }
            else if (n->right == nullptr) {
                n->left->parent = n->parent;
                if (n->parent != nullptr) {
                    if (n->parent->left != nullptr && n->parent->left == n) n->parent->left = n->left;
                    else if (n->parent->right != nullptr && n->parent->right == n) n->parent->right = n->left;
                }
                else {
                    root = n->left;
                }
            }
            else {
                node* replace = find_max(n->left);
                if (replace->parent != n) {
                    replace->parent->right = replace->left;
                    replace->left = n->left;
                    n->left->parent = replace;
                }

                replace->right = n->right;
                replace->parent = n->parent;

                n->right->parent = replace;

                if (n->parent == nullptr) {
                    root = replace;
                }
                else {
                    if (n->parent->right == n) n->parent->right = replace;
                    else n->parent->left = replace;
                }

                if (n->parent == nullptr) root = replace;
            }

            if (n->parent != nullptr) delete n;
        }
    
        /* Delete node from the BST
        @param n value of node to be deleted */
        void del(int n) {
            del(find(n));
        }

};