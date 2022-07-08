import os


class Node:
    def __init__(self, val=0, neighbors=None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []


def CreateGraphClone(adjList: list):
    # here input is graph, graph->adjacency list->graph and we need to create the graph i think
    # the label of node is same as the index , it is 1-indexed
    nodes = {}  # create a hasmap for the nodes
    for i in range(len(adjList)):
        nodes[i] = Node(i, adjList[i])
    return nodes[1]
