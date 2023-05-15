import networkx as nx
import random
import argparse

"USAGE: python graph_generator.py -n #nodes -t type(0, 1, 2) -w maximum_weight_of_edges"


def generate_connected_graph(n, type, max_weight):
    """GENERATE RANDOM GRAPH"""
    # Just some heuristics about sparse, normal and fully connected graph
    p = 1.0 if type == 3 else 0.6 if type == 2 else 0.2

    # Generate random erdos renyi graph
    G = nx.erdos_renyi_graph(n, p, seed=21520378, directed=False)

    # Ensure graph is connected
    while not nx.is_connected(G):
        # Create a random edge
        u = random.choice(range(0, n))
        v = random.choice(list(nx.non_neighbors(G, u)))

        # Add u,
        G.add_edge(u, v)

    print(G.number_of_nodes(), G.number_of_edges())

    """STORE GRAPH IN A FILE"""
    file_name = 'fully' if type == 3 else 'normal' if type == 2 else 'sparse'
    file_name = file_name + '_connected_graph.txt'

    with open('./test_cases/' + file_name, 'w') as f:
        f.write('{0} {1}\n'.format(G.number_of_nodes(), G.number_of_edges()))

        for edge in G.edges:
            f.write('{0} {1} {2}\n'.format(edge[0], edge[1], random.choice(range(0, max_weight))))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="program's description")
    parser.add_argument('-n', '--numVertices', type=int, help='#vertices of the graph')
    parser.add_argument('-t', '--type', type=int, help='type of graph (0:sparse, 1:normal, 2:fully)')
    parser.add_argument('-w', '--maxWeight', type=int, default=100, help='maximum weight of every edges in graph')

    try:
        args = parser.parse_args()
        generate_connected_graph(args.numVertices, args.type, args.maxWeight)
    except:
        print('Please offer parameters (n, m)!')