class Edge:
    def __init__(self, from_node, to_node, capacity=1, residual = False):
        self.to = to_node
        self.from_node = from_node
        self.capacity = capacity
        self.rev = None
        self.residual = residual

    def __repr__(self):
         return f"{self.to.name}({self.capacity})"