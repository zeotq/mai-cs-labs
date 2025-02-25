#include "../include/Tree.h"

// Node
Tree_Node * Node_create(T value_, Tree_Node * parent_) {
    // Node creation
}
void Node_destroy(Tree_Node *) {
    // Delete Node and Node-Childs
}

// Tree
Tree * Tree_create(T rootValue) {
    // Memory for Tree struct
    // Create root from rootValue
}
void Tree_destroy(Tree *) {
    // Delete Node
    // Delete Tree
}
bool Tree_addNode(Tree *, T parent, T childValue) {
    
}

bool Tree_deleteNode(Tree *, T nodeValue);
void Tree_print(Tree *);
size_t Tree_levelWithMaxNodes(Tree *);
