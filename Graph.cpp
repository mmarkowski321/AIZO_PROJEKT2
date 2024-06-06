#include "Graph.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>

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

// Funkcja do wczytywania grafu z pliku w formacie listy sąsiedztwa
GraphList readGraphFromFileList(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Nie można otworzyć pliku: " << filename << std::endl;
        exit(1);
    }
    int V;
    file >> V;
    GraphList graph(V, 0);
    int src, dest, weight;
    while (file >> src >> dest >> weight) {
        graph.addEdge(src, dest, weight);
    }
    return graph;
}





GraphMatrix readGraphFromFileMatrix(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Nie można otworzyć pliku: " << filename << std::endl;
        exit(1);
    }
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
