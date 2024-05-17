#include "Graph.h"
#include <fstream>
#include <cstdlib>

GraphList::GraphList(int V, int E) : V(V), E(E) {
    adjList.resize(V);
}

void GraphList::addEdge(int src, int dest, int weight) {
    adjList[src].push_back({dest, weight});
    adjList[dest].push_back({src, weight}); // dla nieskierowanego grafu
}

GraphMatrix::GraphMatrix(int V, int E) : V(V), E(E) {
    matrix.resize(V, std::vector<int>(V, 0));
}

void GraphMatrix::addEdge(int src, int dest, int weight) {
    matrix[src][dest] = weight;
    matrix[dest][src] = weight; // dla nieskierowanego grafu
}

GraphList readGraphFromFileList(const std::string& filename) {
    std::ifstream file(filename);
    int V, E;
    file >> V >> E;
    GraphList graph(V, E);
    int src, dest, weight;
    while (file >> src >> dest >> weight) {
        graph.addEdge(src, dest, weight);
    }
    return graph;
}

GraphMatrix readGraphFromFileMatrix(const std::string& filename) {
    std::ifstream file(filename);
    int V, E;
    file >> V >> E;
    GraphMatrix graph(V, E);
    int src, dest, weight;
    while (file >> src >> dest >> weight) {
        graph.addEdge(src, dest, weight);
    }
    return graph;
}

GraphList generateRandomGraphList(int V, double density) {
    int E = density * V * (V - 1) / 2;
    GraphList graph(V, E);
    for (int i = 0; i < V - 1; ++i) {
        int weight = rand() % 100 + 1;
        graph.addEdge(i, i + 1, weight);
    }
    for (int i = V - 1; i < E; ++i) {
        int src = rand() % V;
        int dest = rand() % V;
        if (src != dest) {
            int weight = rand() % 100 + 1;
            graph.addEdge(src, dest, weight);
        }
    }
    return graph;
}

GraphMatrix generateRandomGraphMatrix(int V, double density) {
    int E = density * V * (V - 1) / 2;
    GraphMatrix graph(V, E);
    for (int i = 0; i < V - 1; ++i) {
        int weight = rand() % 100 + 1;
        graph.addEdge(i, i + 1, weight);
    }
    for (int i = V - 1; i < E; ++i) {
        int src = rand() % V;
        int dest = rand() % V;
        if (src != dest) {
            int weight = rand() % 100 + 1;
            graph.addEdge(src, dest, weight);
        }
    }
    return graph;
}
