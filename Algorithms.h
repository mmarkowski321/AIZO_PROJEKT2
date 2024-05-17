#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.h"
#include <vector>
#include <utility>

std::vector<Edge> primMSTList(GraphList& graph);
std::vector<Edge> primMSTMatrix(GraphMatrix& graph);
std::vector<Edge> kruskalMSTList(GraphList& graph);
std::vector<Edge> kruskalMSTMatrix(GraphMatrix& graph);

std::pair<std::vector<int>, std::vector<int>> dijkstraList(GraphList& graph, int src, int dest);
std::pair<std::vector<int>, std::vector<int>> dijkstraMatrix(GraphMatrix& graph, int src, int dest);
std::pair<std::vector<int>, std::vector<int>> bellmanFordList(GraphList& graph, int src, int dest);
std::pair<std::vector<int>, std::vector<int>> bellmanFordMatrix(GraphMatrix& graph, int src, int dest);

int fordFulkersonList(GraphList& graph, int src, int dest);
int fordFulkersonMatrix(GraphMatrix& graph, int src, int dest);

void displayMST(const std::vector<Edge>& mst);
void displayShortestPath(int src, int dest, const std::vector<int>& dist, const std::vector<int>& path);

#endif // ALGORITHMS_H
