from node import Node
from collections import deque
from edge import Edge

class Graph:

    def __init__(self):
        self.nodes = {}


    
    def add_node(self, name):
        if name not in self.nodes:
            self.nodes[name] = Node(name)


    def add_link(self, a, b):
        self.add_node(a)
        self.add_node(b)
    
        self.nodes[a].add_neighbor(self.nodes[b])
        self.nodes[b].add_neighbor(self.nodes[a])


    def reset(self):

        for node in self.nodes.values():
            node.visited = False
            node.parent_edge = None

    
    def bfs(self, start_name, end_name):
        
        self.reset()
        q = deque()

        start = self.nodes[start_name]
        end = self.nodes[end_name]

        start.visited = True

        q.append(start)

        while q:
            curr = q.popleft()

            for edge in curr.neigh:

                if edge.capacity <= 0: #peut pas etre neg mais au cas ou
                    continue

                next_node = edge.to

                if next_node.visited:
                    continue

                next_node.visited = True
                next_node.parent_edge = edge
                q.append(next_node)

                if next_node == end:
                    return True

        return False
    



    def build_path(self, end_name):
        
        curr = self.nodes[end_name]
        path = deque()


        while curr.parent_edge:
            edge = curr.parent_edge
            path.appendleft(edge)
            curr = edge.from_node
            
        return list(path)
    


    def use_flow(self, path):

        for edge in path:
            edge.capacity -= 1
            edge.rev.capacity += 1


    
    def path_to_nodes(self, path):

        return [path[0].from_node.name] + [edge.to.name for edge in path]
    
    
    def extract_paths(self, start_name, end_name):

        start = self.nodes[start_name]
        end = self.nodes[end_name]

        paths = []

        while True:

            path = []
            curr = start

            visited_node = set()

            while curr != end:

                found = False

                visited_node.add(curr)

                for edge in curr.neigh:

                    # on suit uniquement le flux utilise
                    if edge.rev.capacity > 0:

                        nxt = edge.to
                        if nxt in visited_node:
                            continue

                        path.append(edge)
                        edge.rev.capacity -= 1  # on consomme ce chemin
                        curr = nxt
                        found = True
                        break #sort du for, revient a la boucle while curr != end

                if not found:
                   return paths  # plus de chemins possibles, arrete le while

            paths.append(self.path_to_nodes(path))



    
    def all_paths(self, start_name, end_name):

        while self.bfs(start_name, end_name):
            path = self.build_path(end_name)
            self.use_flow(path)

        return self.extract_paths(start_name, end_name)
