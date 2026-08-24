#include "graph.h"
#include "parser.h"
#include "simulation.h"
#include "libft.h"

int main(void)
{
    Graph graph;
    graph_init(&graph);
    int ants = 0;
    char *start = NULL;
    char *end = NULL;

    if (!parse_file(&graph, &ants, &start, &end)) {
        ft_putstr_fd("Erreur: carte invalide\n", 2);
        free(start);
        free(end);
        graph_destroy(&graph);
        return 1;
    }

    PathList paths = graph_all_paths(&graph, start, end, ants);
    ft_putstr_fd("Paths trouves :\n", 1);
    for (int i = 0; i < paths.count; i++) {
        path_print(&paths.items[i]);
        ft_putchar_fd('\n', 1);
    }

    ft_putstr_fd("\nSimulation :\n", 1);
    simulate(&paths, ants);

    path_list_destroy(&paths);
    free(start);
    free(end);
    graph_destroy(&graph);
    return 0;
}
