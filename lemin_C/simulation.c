#include "simulation.h"
#include "libft.h"

static void sort_paths(PathList *paths)
{
    for (int i = 0; i < paths->count; i++)
        for (int j = i + 1; j < paths->count; j++)
            if (paths->items[j].length < paths->items[i].length) {
                Path temporary = paths->items[i];
                paths->items[i] = paths->items[j];
                paths->items[j] = temporary;
            }
}

int *compute_distribution(PathList *paths, int ants)
{
    sort_paths(paths);
    int turns = paths->count + ants;

    while (1) {
        int capacity = 0;
        for (int i = 0; i < paths->count; i++) {
            int available = turns - paths->items[i].length - 1;
            if (available > 0)
                capacity += available;
        }
        if (capacity >= ants)
            break;
        turns++;
    }

    int *loads = ft_calloc((size_t)paths->count, sizeof(*loads));
    if (loads == NULL)
        return NULL;
    int remaining = ants;
    for (int i = 0; i < paths->count; i++) {
        int capacity = turns - paths->items[i].length - 1;
        if (capacity < 0)
            capacity = 0;
        loads[i] = capacity < remaining ? capacity : remaining;
        remaining -= loads[i];
    }
    return loads;
}

typedef struct {
    int ant;
    int position;
} AntFlow;

typedef struct {
    AntFlow *items;
    int count;
    int capacity;
} FlowList;

static void flow_append(FlowList *flow, AntFlow ant)
{
    if (flow->count == flow->capacity) {
        int new_capacity = flow->capacity == 0 ? 4 : flow->capacity * 2;
        AntFlow *items = malloc((size_t)new_capacity * sizeof(*items));
        if (items == NULL)
            return;
        for (int i = 0; i < flow->count; i++)
            items[i] = flow->items[i];
        free(flow->items);
        flow->items = items;
        flow->capacity = new_capacity;
    }
    flow->items[flow->count++] = ant;
}

void simulate(PathList *paths, int ants)
{
    int *loads = compute_distribution(paths, ants);
    if (loads == NULL || paths->count == 0)
        return;

    FlowList *flows = ft_calloc((size_t)paths->count, sizeof(*flows));
    int *sent = ft_calloc((size_t)paths->count, sizeof(*sent));
    if (flows == NULL || sent == NULL) {
        free(flows);
        free(sent);
        free(loads);
        return;
    }

    int ant_id = 1;
    int finished = 0;
    while (finished < ants) {
        int printed = 0;
        for (int i = 0; i < paths->count; i++) {
            FlowList next = {0};
            for (int j = 0; j < flows[i].count; j++) {
                AntFlow ant = flows[i].items[j];
                ant.position++;
                if (printed)
                    ft_putchar_fd(' ', 1);
                ft_putstr_fd("L", 1);
                ft_putnbr_fd(ant.ant, 1);
                ft_putchar_fd('-', 1);
                ft_putstr_fd(paths->items[i].nodes[ant.position]->name, 1);
                printed = 1;
                if (ant.position == paths->items[i].length)
                    finished++;
                else
                    flow_append(&next, ant);
            }
            free(flows[i].items);
            flows[i] = next;
        }

        for (int i = 0; i < paths->count; i++) {
            if (sent[i] < loads[i] && ant_id <= ants && paths->items[i].length > 0) {
                AntFlow ant = {ant_id++, 1};
                flow_append(&flows[i], ant);
                if (printed)
                    ft_putchar_fd(' ', 1);
                ft_putstr_fd("L", 1);
                ft_putnbr_fd(ant.ant, 1);
                ft_putchar_fd('-', 1);
                ft_putstr_fd(paths->items[i].nodes[1]->name, 1);
                printed = 1;
                sent[i]++;
                if (paths->items[i].length == 1) {
                    flows[i].count--;
                    finished++;
                }
            }
        }
        if (printed)
            ft_putchar_fd('\n', 1);
    }

    for (int i = 0; i < paths->count; i++)
        free(flows[i].items);
    free(flows);
    free(sent);
    free(loads);
}
