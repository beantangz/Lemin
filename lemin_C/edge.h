#ifndef EDGE_H
#define EDGE_H

typedef struct Node Node;
typedef struct Edge Edge;

struct Edge {
    Node *from;
    Node *to;
    int capacity;
    int residual;
    Edge *rev;
};

#endif
