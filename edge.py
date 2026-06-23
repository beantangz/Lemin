class Edge:
    def __init__(self, from_node, to_node, capacity=1):
        self.to = to_node
        self.from_node = from_node
        self.capacity = capacity
        self.rev = None
        self.used = False

    def __repr__(self):
         return f"{self.to.name}({self.capacity})"