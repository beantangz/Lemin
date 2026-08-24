def compute_distribution(paths, ants):
    paths = sorted(paths, key=len)

    n = len(paths)

    def can(T): #pour un temps T, on regarde combien on fait passer de fourmis de start a end par chemins et on fait la somme pr savoir si tte les fourmis peuvent passer
        return sum(max(0, T - len(p)) for p in paths) >= ants

    # trouver T minimal : len(paths) + ants = cas ou chaque path est taille 1, on est sur que c'est le min
    T = min(len(paths) + ants, 10**9)
    while not can(T):
        T += 1
    #ici T est le temps minimal possible

    loads = []
    remaining = ants

    for p in paths:
        cap = max(0, T - len(p)) #cb un chemin peut en ammener a end en un temps T
        take = min(cap, remaining) #cb il en reste a prendre (au max cap)
        loads.append(take)
        remaining -= take

    return loads #list avec indice correspond a cb le chemin i de paths va en prendre

def simulate(paths, ants):

    paths = [list(p) for p in paths]
    loads = compute_distribution(paths, ants)

    flows = [[] for _ in paths]

    ant_id = 1
    finished = 0

    # compteur d’envoi par path
    sent = [0] * len(paths)

    while finished < ants:

        turn = []

        # 1. avancer les fourmis
        for i, path in enumerate(paths):
            new_flow = []

            for ant, pos in flows[i]:
                pos += 1

                turn.append(f"L{ant}-{path[pos]}")

                if pos == len(path) - 1:
                    finished += 1
                else:
                    new_flow.append((ant, pos))

            flows[i] = new_flow

        # 2. injecter selon distribution optimale
        for i, path in enumerate(paths):

            if sent[i] < loads[i] and ant_id <= ants and len(path) > 1:

                flows[i].append((ant_id, 1))
                turn.append(f"L{ant_id}-{path[1]}")

                ant_id += 1
                sent[i] += 1
        #print("flows =", flows)
        #print("sent =", sent)
        #print("finished =", finished)

        if turn:
            print(" ".join(turn))