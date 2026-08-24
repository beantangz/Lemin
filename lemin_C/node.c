#include "node.h"
#include "libft.h"

static char *copy_string(const char *text)
{
    char *copy = malloc(ft_strlen(text) + 1);
    if (copy != NULL)
        ft_strlcpy(copy, text, ft_strlen(text) + 1);
    return copy;
}

Node *node_create(const char *name)
{
    Node *node = ft_calloc(1, sizeof(*node));
    if (node == NULL)
        return NULL;
    node->name = copy_string(name);
    if (node->name == NULL) {
        free(node);
        return NULL;
    }
    return node;
}

void node_add_neighbor(Node *from, Node *to)
{
    if (from->neighbor_count == from->neighbor_capacity) {
        int new_capacity = from->neighbor_capacity == 0 ? 4 : from->neighbor_capacity * 2;
        Edge **new_neighbors = malloc((size_t)new_capacity * sizeof(*new_neighbors));
        if (new_neighbors == NULL)
            return;
        for (int i = 0; i < from->neighbor_count; i++)
            new_neighbors[i] = from->neighbors[i];
        free(from->neighbors);
        from->neighbors = new_neighbors;
        from->neighbor_capacity = new_capacity;
    }

    Edge *forward = ft_calloc(1, sizeof(*forward));
    Edge *backward = ft_calloc(1, sizeof(*backward));
    if (forward == NULL || backward == NULL) {
        free(forward);
        free(backward);
        return;
    }

    forward->from = from;
    forward->to = to;
    forward->capacity = 1;
    forward->rev = backward;
    backward->from = to;
    backward->to = from;
    backward->residual = 1;
    backward->rev = forward;

    from->neighbors[from->neighbor_count++] = forward;

    if (to->neighbor_count == to->neighbor_capacity) {
        int new_capacity = to->neighbor_capacity == 0 ? 4 : to->neighbor_capacity * 2;
        Edge **new_neighbors = malloc((size_t)new_capacity * sizeof(*new_neighbors));
        if (new_neighbors == NULL)
            return;
        for (int i = 0; i < to->neighbor_count; i++)
            new_neighbors[i] = to->neighbors[i];
        free(to->neighbors);
        to->neighbors = new_neighbors;
        to->neighbor_capacity = new_capacity;
    }
    to->neighbors[to->neighbor_count++] = backward;
}

void node_destroy(Node *node)
{
    if (node == NULL)
        return;
    for (int i = 0; i < node->neighbor_count; i++) {
        Edge *edge = node->neighbors[i];
        if (!edge->residual) {
            free(edge->rev);
            free(edge);
        }
    }
    free(node->neighbors);
    free(node->name);
    free(node);
}
