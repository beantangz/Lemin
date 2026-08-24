#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"

typedef struct {
    Node **nodes;
    int node_count;
    int node_capacity;
} Graph;

typedef struct {
    Node **nodes;
    Edge **edges;
    int length;
} Path;

typedef struct {
    Path *items;
    int count;
} PathList;

void graph_init(Graph *graph);
void graph_destroy(Graph *graph);
Node *graph_find_node(const Graph *graph, const char *name);
Node *graph_add_node(Graph *graph, const char *name);
void graph_add_link(Graph *graph, const char *from, const char *to);
int graph_bfs(Graph *graph, const char *start_name, const char *end_name);
Path graph_build_path(Graph *graph, const char *end_name);
void graph_use_flow(const Path *path);
PathList graph_extract_paths(Graph *graph, const char *start_name, const char *end_name);
int graph_compute_turns(const PathList *paths, int ants);
PathList graph_all_paths(Graph *graph, const char *start_name, const char *end_name, int ants);
void path_destroy(Path *path);
void path_list_destroy(PathList *paths);
void path_print(const Path *path);

#endif
