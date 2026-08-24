#ifndef SIMULATION_H
#define SIMULATION_H

#include "graph.h"

int *compute_distribution(PathList *paths, int ants);
void simulate(PathList *paths, int ants);

#endif
