#include <iostream>
#include <random>
#include "BST.hpp"

#define print(a) for(int x: a) std::cout << x<<' ';


int main() {
    srand(time(0)); //this is just for the random numbers nothing to do with the trees
    const int LIMIT = 100; //the range of the values that the nodes can have is from 0 to 100
    const int ELEMENTS = 5;

    BST* bst = new BST(rand()%LIMIT);

    
    std::cout << "The elements of the tree printed in the order they were inserted:\n";
    std::cout << bst->get_root()->data<<"\n";

    std::vector<int> p;
    //now just populate the tree with the nodes
    for (int i = 0; i<ELEMENTS; i++) {
        p.push_back(rand()%LIMIT);
        
        bst->insert(p[i]); // insert

        std::cout << p[i] <<"\n";
    }
    std::cout << "\n";

    std::vector<int> arr;
    std::cout << "The elements of the tree printed using Inorder:\n";
    bst->inorder(arr);
    print(arr); //print the elements from left to right so from smallest to biggest(left, root, right)
    std::cout <<"\n";

    arr.clear();
    std::cout << "The elements of the tree printed using Preorder:\n";
    bst->preorder(arr); //first print the root then the recursively the left side and then recursively the right side(root, left, left)
    print(arr);
    std::cout <<"\n";

    arr.clear();
    std::cout << "The elements of the tree printed using Postorder:\n";
    bst->postorder(arr); //first print recursively the left side, then the right side and then the root(left, right, root)
    print(arr);
    std::cout <<"\n\n";
    
    std::cout << "Minimum height of the tree: " << bst->min_height()<<"\n";
    
    std::cout << "Maximum height of the tree: "<<bst->height()<<"\n";
    
    std::cout << "The greatest value in the tree: "<<bst->find_max()->data<<"\n";
    
    std::cout << "The smallest value in the tree: "<<bst->find_min()->data<<"\n";

    std::cout << "The root node has a value of "<<bst->get_root()->data<<"\n\n";

    
    int randomValue = p[rand()%ELEMENTS];
    node* temp = bst->find(randomValue);
    if (temp == nullptr) {
        std::cout << "Node not found\n\n";
    }
    else {
        std::cout << "The value "<< randomValue<<" when put as an argument in the search function will return a node with the value of "<< temp->data<<" "<<((temp->parent!=nullptr)?("and parent with a value of "+std::to_string(temp->parent->data)):" and it is the head node")<<"\n\n";
    }

    bst->del(randomValue);
    std::cout << "After deleting "<<randomValue<<" Inorder is:\n";
    arr.clear();
    bst->inorder(arr);
    print(arr);
    return 0;
}


