#ifndef NODE_H
#define NODE_H

#include "edge.h"

struct Node {
    char *name;
    Edge **neighbors;
    int neighbor_count;
    int neighbor_capacity;
    int visited;
    Edge *parent_edge;
};

Node *node_create(const char *name);
void node_add_neighbor(Node *from, Node *to);
void node_destroy(Node *node);

#endif
