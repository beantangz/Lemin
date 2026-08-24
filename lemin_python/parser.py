from graph import Graph

def parse_file(filename, graph):
    ants = 0
    start_room = None
    end_room = None

    next_is_start = False
    next_is_end = False

    with open(filename, "r") as f:
        for line in f:
            line = line.strip()

            if not line:
                continue

            if line.startswith("#") and not line.startswith("##"):
                continue

            if ants == 0:
                ants = int(line)
                continue

            if line == "##start":
                next_is_start = True
                continue

            if line == "##end":
                next_is_end = True
                continue

            if " " in line:
                parts = line.split()

                name = parts[0]

                graph.add_node(name)

                if next_is_start:
                    start_room = name
                    next_is_start = False

                elif next_is_end:
                    end_room = name
                    next_is_end = False

                continue

            if "-" in line:
                a, b = line.split("-")
                graph.add_link(a, b)

    return ants, start_room, end_room