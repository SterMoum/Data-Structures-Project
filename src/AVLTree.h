#ifndef AVLTREE_H
#define AVLTREE_H

#include "Tree.h"

class AVLTree : public Tree
{
    public:
        AVLTree();

        void addLeaf(std::string)override;
        void FindNode(std::string);
        void DeleteNode(std::string)override;

        node* min(node*); // Find the node with the smallest value.

        void WriteToFileAVL(std::string*,int);

        void InOrder()override;
        void PreOrder()override;
        void PostOrder()override;


    private:

        node* addLeafPrivAVL(std::string, node*); // Add a leaf to the tree with  specific value.
        // Helper Functions for addLeafPriv
        int Height(node*);
        int max(int, int);
        node* RightRotation(node* &);
        node* LeftRotation(node* &);
        node* doubleRightRotation(node* &);
        node* doubleLeftRotation(node* &);

        node* DeleteNodePrivAVL(std::string,node*);
};

#endif // AVLTREE_H
