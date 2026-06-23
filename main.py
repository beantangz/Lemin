from graph import Graph
from parser import parse_file
from simulation import simulate
from simulation import compute_distribution

graph = Graph()

ants, start, end = parse_file("map.txt", graph)

paths = graph.all_paths(start, end)

print("Paths trouvés :")
for p in paths:
    print(p)

#loads = compute_distribution(paths, ants)

#print("loads =", loads)

print("\nSimulation :")
simulate(paths, ants)