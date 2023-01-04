#include <iostream>
#include <random>

struct node {
    int data;
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
};

int min_height(node* root) {
    if (root == nullptr) return 0;
    return 1 + std::min(min_height(root->left), min_height(root->right));
}

//this is like the max height, I just named it height because that is the normal height
int height(node* root) {
    if (root == nullptr) return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

//finds node with biggest value in a binary search tree
node* find_max(node* root) {
    if (root->right == nullptr) return root;
    return find_max(root->right);
}

//finds node with least value in a binary search tree
node* find_min(node* root) {
    if (root->left == nullptr) return root;
    return find_min(root->left);
}

//this function finds a specific node in a binary search tree
node* find_num(node* root, node* key) {
    if (root->data > key->data) return find_num(root->left, key);
    else if (root->data < key->data) return find_num(root->right, key);
    return root;
}

//Inorder(left, root, right)
void print(node* root) {
    if (root == nullptr) return;
    print(root->left);
    std::cout << root->data<< "\n";
    print(root->right);
}

//Preorder(root, right, left)
void print_Preorder(node* root) {
    if (root == nullptr) return;
    std::cout << root->data<< "\n";
    print_Preorder(root->right);
    print_Preorder(root->left);
}

//Postorder(left, right, root)
void print_Postorder(node* root) {
    if (root == nullptr) return;
    print_Postorder(root->left);
    print_Postorder(root->right);
    std::cout << root->data<< "\n";
}

//insert for binary search trees
void insert(node* &root, node* p) {
    if (p->data > root->data) {
        if (root->right == nullptr) {
            root->right = p;
            p->parent = root;
            return;
        }
        insert(root->right, p);
    }
    else {
        if (root->left == nullptr) {
            root->left = p;
            p->parent = root;
            return;
        }
        insert(root->left, p);
    }
}

//put as parameter any node of the binary search tree and this function will find the root of the tree, the node at the top of the tree
node* find_root(node* p) {
    if (p->parent==nullptr) return p;
    return find_root(p->parent);
}

int main() {
    srand(time(0)); //this is just for the random numbers nothing to do with the trees
    const int LIMIT = 100; //the range of the values that the nodes can have is from 0 to 100
    const int ELEMENTS = 5;

    node* head = new node(); //create the head node
    node* p[ELEMENTS]; //create the rest of the nodes
    
    std::cout << "The elements of the tree printed in the order they were inserted:\n";
    head->data = rand()%LIMIT; //assign a value for the head node by picking a random value up to a hundred
    std::cout << head->data<<"\n";
    
    //now just populate the tree with the nodes
    for (int i = 0; i<ELEMENTS; i++) {
        p[i] = new node(); //this is needed
        p[i]->data = rand()%LIMIT; //just pick a random value up to a hundred
        insert(head, p[i]); //insert the node in the tree
        std::cout << p[i]->data<<"\n";
    }
    std::cout << "\n";
    std::cout << "The elements of the tree printed using Inorder:\n";
    print(head); //print the elements from left to right so from smallest to biggest(right, root, left)
    std::cout <<"\n";
    std::cout << "The elements of the tree printed using Preorder:\n";
    print_Preorder(head); //first print the root then the recursively the right side and then recursively the left side(root, right, left)
    std::cout <<"\n";
    std::cout << "The elements of the tree printed using Postorder:\n";
    print_Postorder(head); //first print recursively the left side, then the right side and then the root(left, right, root)
    std::cout <<"\n";
    
    std::cout << "Minimum height of the tree: " << min_height(head)<<"\n";
    
    std::cout << "Maximum height of the tree: "<<height(head)<<"\n";
    
    std::cout << "The greatest value in the tree: "<<find_max(head)->data<<"\n";
    
    std::cout << "The smallest value in the tree: "<<find_min(head)->data<<"\n";

    std::cout << "The root node has a value of "<<find_root(p[rand()%ELEMENTS])->data<<"\n";
    
    node* randomValue = new node();
    randomValue->data = p[rand()%ELEMENTS]->data;
    node* temp = find_num(head, randomValue);
    std::cout << "The value "<< randomValue->data<<" when put as an argument in the search function will return a node with the value of "<< temp->data<<" "<<((temp->parent!=nullptr)?("and parent with a value of "+std::to_string(temp->parent->data)):" and it is the head node")<<"\n";
    return 0;
}
