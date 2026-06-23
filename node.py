from edge import Edge

class Node:
    def __init__(self,name):
        self.name = name
        self.parent_edge = None
        self.neigh = [] #liste d'egde (vers qui, avec capacity)
        self.visited = False

    def add_neighbor(self, node):
        forward = Edge(self, node, 1)
        backward = Edge(node, self, 0)

        forward.rev = backward
        backward.rev = forward

        self.neigh.append(forward)
        node.neigh.append(backward)
    
    def __repr__(self):  #affiche quand on fait print()
        return self.name

