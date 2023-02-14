#ifndef TREE_H
#define TREE_H

//#include <cstdlib>
#include <iostream>
#include <fstream>

    struct node
        {
            std::string key; //value of node
            node* left; //left child
            node* right; //right child
            int count; //number of the same word
            int height; //the height of the node (for AVL tree)
        };
class Tree
{
    protected:

        node* root; //the root of tree

        node *CreateLeaf(std::string); // Create a leaf.
        void addLeafPriv(std::string, node*); // Add a leaf to the tree with  specific value.
        node* FindNodePriv(std::string, node*); // Find a leaf with specific value.

        void DeleteNodePriv(std::string, node*); // Delete a node.
        // Helper Functions For DeleteNodePriv.
        node* FindMin(node*); // Find the node with the smallest value.
        void DeleteRoot(); // Delete the root.
        void DeleteMatch(node*, node*, bool); // Delete a node except root.
        // bool: It says if a current node is a left(true) or right(false) child of his parent.

        // Tree traversals.
        void InOrderPriv(node*);
        void PreOrderPriv(node*);
        void PostOrderPriv(node*);

    public:
        Tree();

        //these functions call the same private function.
        //They are helpers for passing only the value of node for easier use from main.
        virtual void addLeaf(std::string);
        void FindNode(std::string);
        virtual void DeleteNode(std::string);

        // Tree traversals.
        virtual void InOrder();
        virtual void PreOrder();
        virtual void PostOrder();

        void WriteToFileTree(std::string*,int);


};
std::ostream& operator << (std::ostream&,node*);
#endif // TREE_H

