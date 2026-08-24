#include "graph.h"
#include "libft.h"

#define MAX_TURNS 2147483647

static int same_name(const char *left, const char *right)
{
    return ft_strlen(left) == ft_strlen(right)
        && ft_strncmp(left, right, ft_strlen(left)) == 0;
}

static void print_text(const char *text)
{
    ft_putstr_fd((char *)text, 1);
}

void graph_init(Graph *graph)
{
    graph->nodes = NULL;
    graph->node_count = 0;
    graph->node_capacity = 0;
}

void graph_destroy(Graph *graph)
{
    for (int i = 0; i < graph->node_count; i++)
        node_destroy(graph->nodes[i]);
    free(graph->nodes);
}

Node *graph_find_node(const Graph *graph, const char *name)
{
    for (int i = 0; i < graph->node_count; i++)
        if (same_name(graph->nodes[i]->name, name))
            return graph->nodes[i];
    return NULL;
}

Node *graph_add_node(Graph *graph, const char *name)
{
    Node *existing = graph_find_node(graph, name);
    if (existing != NULL)
        return existing;

    if (graph->node_count == graph->node_capacity) {
        int new_capacity = graph->node_capacity == 0 ? 8 : graph->node_capacity * 2;
        Node **new_nodes = malloc((size_t)new_capacity * sizeof(*new_nodes));
        if (new_nodes == NULL)
            return NULL;
        for (int i = 0; i < graph->node_count; i++)
            new_nodes[i] = graph->nodes[i];
        free(graph->nodes);
        graph->nodes = new_nodes;
        graph->node_capacity = new_capacity;
    }

    Node *node = node_create(name);
    if (node == NULL)
        return NULL;
    graph->nodes[graph->node_count++] = node;
    return node;
}

void graph_add_link(Graph *graph, const char *from, const char *to)
{
    Node *a = graph_add_node(graph, from);
    Node *b = graph_add_node(graph, to);
    if (a != NULL && b != NULL) {
        node_add_neighbor(a, b);
        node_add_neighbor(b, a);
    }
}

int graph_bfs(Graph *graph, const char *start_name, const char *end_name)
{
    Node *start = graph_find_node(graph, start_name);
    Node *end = graph_find_node(graph, end_name);
    if (start == NULL || end == NULL)
        return 0;

    for (int i = 0; i < graph->node_count; i++) {
        graph->nodes[i]->visited = 0;
        graph->nodes[i]->parent_edge = NULL;
    }

    Node **queue = malloc((size_t)graph->node_count * sizeof(*queue));
    if (queue == NULL)
        return 0;
    int head = 0;
    int tail = 0;
    start->visited = 1;
    queue[tail++] = start;

    while (head < tail) {
        Node *current = queue[head++];
        for (int i = 0; i < current->neighbor_count; i++) {
            Edge *edge = current->neighbors[i];
            if (edge->capacity <= 0 || edge->to->visited)
                continue;
            edge->to->visited = 1;
            edge->to->parent_edge = edge;
            queue[tail++] = edge->to;
            if (edge->to == end) {
                free(queue);
                return 1;
            }
        }
    }
    free(queue);
    return 0;
}

Path graph_build_path(Graph *graph, const char *end_name)
{
    Path path = {0};
    Node *current = graph_find_node(graph, end_name);
    while (current != NULL && current->parent_edge != NULL) {
        path.length++;
        current = current->parent_edge->from;
    }
    if (path.length == 0)
        return path;

    path.nodes = malloc((size_t)(path.length + 1) * sizeof(*path.nodes));
    path.edges = malloc((size_t)path.length * sizeof(*path.edges));
    if (path.nodes == NULL || path.edges == NULL) {
        free(path.nodes);
        free(path.edges);
        path.nodes = NULL;
        path.edges = NULL;
        path.length = 0;
        return path;
    }
    current = graph_find_node(graph, end_name);
    path.nodes[path.length] = current;
    for (int i = path.length - 1; i >= 0; i--) {
        path.edges[i] = current->parent_edge;
        path.nodes[i] = current = current->parent_edge->from;
    }
    return path;
}

void graph_use_flow(const Path *path)
{
    for (int i = 0; i < path->length; i++) {
        Edge *edge = path->edges[i];
        edge->capacity--;
        edge->rev->capacity++;
    }
}

static void path_list_append(PathList *list, Path path)
{
    Path *items = malloc((size_t)(list->count + 1) * sizeof(*items));
    if (items == NULL) {
        path_destroy(&path);
        return;
    }
    for (int i = 0; i < list->count; i++)
        items[i] = list->items[i];
    free(list->items);
    list->items = items;
    list->items[list->count++] = path;
}

PathList graph_extract_paths(Graph *graph, const char *start_name, const char *end_name)
{
    PathList result = {0};
    Node *start = graph_find_node(graph, start_name);
    Node *end = graph_find_node(graph, end_name);
    if (start == NULL || end == NULL)
        return result;

    int edge_count = 0;
    for (int i = 0; i < graph->node_count; i++)
        for (int j = 0; j < graph->nodes[i]->neighbor_count; j++)
            if (!graph->nodes[i]->neighbors[j]->residual)
                edge_count++;

    Edge **flow_edges = malloc((size_t)edge_count * sizeof(*flow_edges));
    int *flow = ft_calloc((size_t)edge_count, sizeof(*flow));
    if (flow_edges == NULL || flow == NULL) {
        free(flow_edges);
        free(flow);
        return result;
    }
    int edge_index = 0;
    for (int i = 0; i < graph->node_count; i++)
        for (int j = 0; j < graph->nodes[i]->neighbor_count; j++) {
            Edge *edge = graph->nodes[i]->neighbors[j];
            if (!edge->residual) {
                flow_edges[edge_index] = edge;
                flow[edge_index++] = edge->rev->capacity;
            }
        }

    while (1) {
        Node **nodes = malloc((size_t)(graph->node_count + 1) * sizeof(*nodes));
        Edge **edges = malloc((size_t)graph->node_count * sizeof(*edges));
        int *seen = ft_calloc((size_t)graph->node_count, sizeof(*seen));
        if (nodes == NULL || edges == NULL || seen == NULL) {
            free(nodes);
            free(edges);
            free(seen);
            break;
        }
        int length = 0;
        Node *current = start;
        int found_path = 1;
        while (current != end) {
            int current_index = -1;
            for (int i = 0; i < graph->node_count; i++)
                if (graph->nodes[i] == current)
                    current_index = i;
            if (current_index >= 0)
                seen[current_index] = 1;
            Edge *chosen = NULL;
            int chosen_index = -1;
            for (int i = 0; i < edge_count; i++) {
                Edge *edge = flow_edges[i];
                int next_index = -1;
                for (int j = 0; j < graph->node_count; j++)
                    if (graph->nodes[j] == edge->to)
                        next_index = j;
                if (edge->from == current && flow[i] > 0 && next_index >= 0 && !seen[next_index]) {
                    chosen = edge;
                    chosen_index = i;
                    break;
                }
            }
            if (chosen == NULL) {
                found_path = 0;
                break;
            }
            if (length == 0)
                nodes[length++] = chosen->from;
            nodes[length++] = chosen->to;
            edges[length - 2] = chosen;
            flow[chosen_index]--;
            current = chosen->to;
        }
        free(seen);
        if (!found_path) {
            free(nodes);
            free(edges);
            break;
        }
        Path path = {nodes, edges, length - 1};
        path_list_append(&result, path);
    }
    free(flow_edges);
    free(flow);
    return result;
}

int graph_compute_turns(const PathList *paths, int ants)
{
    if (paths->count == 0)
        return MAX_TURNS;
    int turns = MAX_TURNS;
    for (int i = 0; i < paths->count; i++)
        if (paths->items[i].length < turns)
            turns = paths->items[i].length;
    while (1) {
        int capacity = 0;
        for (int i = 0; i < paths->count; i++) {
            int available = turns - paths->items[i].length + 1;
            if (available > 0)
                capacity += available;
        }
        if (capacity >= ants)
            return turns;
        turns++;
    }
}

static PathList path_list_copy(const PathList *source)
{
    PathList copy = {0};
    for (int i = 0; i < source->count; i++) {
        Path path = {
            malloc((size_t)(source->items[i].length + 1) * sizeof(Node *)),
            malloc((size_t)source->items[i].length * sizeof(Edge *)),
            source->items[i].length
        };
        if (path.nodes == NULL || path.edges == NULL) {
            free(path.nodes);
            free(path.edges);
            continue;
        }
        for (int j = 0; j <= path.length; j++)
            path.nodes[j] = source->items[i].nodes[j];
        for (int j = 0; j < path.length; j++)
            path.edges[j] = source->items[i].edges[j];
        path_list_append(&copy, path);
    }
    return copy;
}

PathList graph_all_paths(Graph *graph, const char *start_name, const char *end_name, int ants)
{
    PathList best = {0};
    int best_turns = MAX_TURNS;
    while (graph_bfs(graph, start_name, end_name)) {
        Path path = graph_build_path(graph, end_name);
        graph_use_flow(&path);
        path_destroy(&path);
        PathList current = graph_extract_paths(graph, start_name, end_name);
        int turns = graph_compute_turns(&current, ants);
        print_text("Solution actuelle : ");
        for (int i = 0; i < current.count; i++) {
            path_print(&current.items[i]);
            if (i + 1 < current.count)
                print_text(", ");
        }
        if (turns == MAX_TURNS)
            print_text("\nTours : infini\n");
        else
        {
            print_text("\nTours : ");
            ft_putnbr_fd(turns, 1);
            print_text("\n");
        }
        if (turns < best_turns) {
            path_list_destroy(&best);
            best = path_list_copy(&current);
            best_turns = turns;
        }
        path_list_destroy(&current);
    }
    return best;
}

void path_destroy(Path *path)
{
    free(path->nodes);
    free(path->edges);
    path->nodes = NULL;
    path->edges = NULL;
    path->length = 0;
}

void path_list_destroy(PathList *paths)
{
    for (int i = 0; i < paths->count; i++)
        path_destroy(&paths->items[i]);
    free(paths->items);
    paths->items = NULL;
    paths->count = 0;
}

void path_print(const Path *path)
{
    print_text("[");
    for (int i = 0; i <= path->length; i++) {
        print_text("'");
        print_text(path->nodes[i]->name);
        print_text("'");
        if (i < path->length)
            print_text(", ");
    }
    print_text("]");
}
