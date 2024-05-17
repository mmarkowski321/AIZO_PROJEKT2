#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

struct Edge {
    int src, dest, weight;
};

struct GraphList {
    int V, E;
    std::vector<std::vector<std::pair<int, int>>> adjList;

    GraphList(int V, int E);
    void addEdge(int src, int dest, int weight);
};

struct GraphMatrix {
    int V, E;
    std::vector<std::vector<int>> matrix;

    GraphMatrix(int V, int E);
    void addEdge(int src, int dest, int weight);
};

GraphList readGraphFromFileList(const std::string& filename);
GraphMatrix readGraphFromFileMatrix(const std::string& filename);

GraphList generateRandomGraphList(int V, double density);
GraphMatrix generateRandomGraphMatrix(int V, double density);

#endif // GRAPH_H
