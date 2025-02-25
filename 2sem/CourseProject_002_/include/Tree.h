#ifndef TREE_HPP_
#define TREE_HPP_
#include "Vector.h"

struct Tree_Node_;
// Хранить в векторе
typedef struct Tree_Node_ {
    T value;
    // Потомки Nodes * child;
    // Родители struct Tree_Node_ * parent;
} Tree_Node;

Tree_Node * Node_create(T value_, Tree_Node * parent_);
void Node_destroy(Tree_Node *);

typedef struct {
    Tree_Node * root;
} Tree;

Tree * Tree_create(T rootValue);
void Tree_destroy(Tree *);

bool Tree_addNode(Tree *, T parent, T childValue);
bool Tree_deleteNode(Tree *, T nodeValue);
void Tree_print(Tree *);
size_t Tree_levelWithMaxNodes(Tree *);

#endif