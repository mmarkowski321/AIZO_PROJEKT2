#include "Algorithms.h"
#include <queue>
#include <algorithm>
#include <climits>
#include <iostream>
#include <stdexcept>

std::vector<Edge> primMSTList(GraphList& graph) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::vector<int> key(graph.V, INT_MAX);
    std::vector<int> parent(graph.V, -1);
    std::vector<bool> inMST(graph.V, false);
    int src = 0;
    pq.push({0, src});
    key[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;
        for (auto& [v, weight] : graph.adjList[u]) {
            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }
    std::vector<Edge> result;
    for (int i = 1; i < graph.V; ++i) {
        result.push_back({parent[i], i, key[i]});
    }
    return result;
}

std::vector<Edge> primMSTMatrix(GraphMatrix& graph) {
    std::vector<int> key(graph.V, INT_MAX);
    std::vector<int> parent(graph.V, -1);
    std::vector<bool> inMST(graph.V, false);
    key[0] = 0;
    for (int count = 0; count < graph.V - 1; ++count) {
        int min = INT_MAX, u;
        for (int v = 0; v < graph.V; ++v) {
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }
        inMST[u] = true;
        for (int v = 0; v < graph.V; ++v) {
            if (graph.matrix[u][v] && !inMST[v] && graph.matrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph.matrix[u][v];
            }
        }
    }
    std::vector<Edge> result;
    for (int i = 1; i < graph.V; ++i) {
        result.push_back({parent[i], i, key[i]});
    }
    return result;
}

std::vector<Edge> kruskalMSTList(GraphList& graph) {
    std::vector<Edge> edges;
    for (int u = 0; u < graph.V; ++u) {
        for (auto& [v, weight] : graph.adjList[u]) {
            if (u < v) {
                edges.push_back({u, v, weight});
            }
        }
    }
    std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });
    std::vector<int> parent(graph.V);
    for (int i = 0; i < graph.V; ++i) {
        parent[i] = i;
    }
    auto find = [&](int u) {
        while (u != parent[u]) {
            u = parent[u];
        }
        return u;
    };
    auto unite = [&](int u, int v) {
        parent[find(u)] = find(v);
    };
    std::vector<Edge> result;
    for (auto& edge : edges) {
        if (find(edge.src) != find(edge.dest)) {
            result.push_back(edge);
            unite(edge.src, edge.dest);
        }
    }
    return result;
}

std::vector<Edge> kruskalMSTMatrix(GraphMatrix& graph) {
    std::vector<Edge> edges;
    for (int u = 0; u < graph.V; ++u) {
        for (int v = u + 1; v < graph.V; ++v) {
            if (graph.matrix[u][v]) {
                edges.push_back({u, v, graph.matrix[u][v]});
            }
        }
    }
    std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });
    std::vector<int> parent(graph.V);
    for (int i = 0; i < graph.V; ++i) {
        parent[i] = i;
    }
    auto find = [&](int u) {
        while (u != parent[u]) {
            u = parent[u];
        }
        return u;
    };
    auto unite = [&](int u, int v) {
        parent[find(u)] = find(v);
    };
    std::vector<Edge> result;
    for (auto& edge : edges) {
        if (find(edge.src) != find(edge.dest)) {
            result.push_back(edge);
            unite(edge.src, edge.dest);
        }
    }
    return result;
}

std::pair<std::vector<int>, std::vector<int>> dijkstraList(GraphList& graph, int src, int dest) {
    std::vector<int> dist(graph.V, INT_MAX);
    std::vector<int> prev(graph.V, -1);
    dist[src] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (auto& [v, weight] : graph.adjList[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return {dist, prev};
}

std::pair<std::vector<int>, std::vector<int>> dijkstraMatrix(GraphMatrix& graph, int src, int dest) {
    std::vector<int> dist(graph.V, INT_MAX);
    std::vector<int> prev(graph.V, -1);
    std::vector<bool> visited(graph.V, false);
    dist[src] = 0;
    for (int i = 0; i < graph.V - 1; ++i) {
        int min = INT_MAX, u;
        for (int v = 0; v < graph.V; ++v) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }
        visited[u] = true;
        for (int v = 0; v < graph.V; ++v) {
            if (!visited[v] && graph.matrix[u][v] && dist[u] != INT_MAX && dist[u] + graph.matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph.matrix[u][v];
                prev[v] = u;
            }
        }
    }
    return {dist, prev};
}

std::pair<std::vector<int>, std::vector<int>> bellmanFordList(GraphList& graph, int src, int dest) {
    std::vector<int> dist(graph.V, INT_MAX);
    std::vector<int> prev(graph.V, -1);
    dist[src] = 0;
    for (int i = 0; i < graph.V - 1; ++i) {
        for (int u = 0; u < graph.V; ++u) {
            for (auto& [v, weight] : graph.adjList[u]) {
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                }
            }
        }
    }
    for (int u = 0; u < graph.V; ++u) {
        for (auto& [v, weight] : graph.adjList[u]) {
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                throw std::runtime_error("Graf zawiera cykl o ujemnej dlugosci");
            }
        }
    }
    return {dist, prev};
}

std::pair<std::vector<int>, std::vector<int>> bellmanFordMatrix(GraphMatrix& graph, int src, int dest) {
    std::vector<int> dist(graph.V, INT_MAX);
    std::vector<int> prev(graph.V, -1);
    dist[src] = 0;
    for (int i = 0; i < graph.V - 1; ++i) {
        for (int u = 0; u < graph.V; ++u) {
            for (int v = 0; v < graph.V; ++v) {
                if (graph.matrix[u][v] && dist[u] != INT_MAX && dist[u] + graph.matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph.matrix[u][v];
                    prev[v] = u;
                }
            }
        }
    }
    for (int u = 0; u < graph.V; ++u) {
        for (int v = 0; v < graph.V; ++v) {
            if (graph.matrix[u][v] && dist[u] != INT_MAX && dist[u] + graph.matrix[u][v] < dist[v]) {
                throw std::runtime_error("Graf zawiera cykl o ujemnej dlugosci");
            }
        }
    }
    return {dist, prev};
}

bool bfsList(const GraphList& graph, int s, int t, std::vector<int>& parent) {
    std::vector<bool> visited(graph.V, false);
    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& [v, weight] : graph.adjList[u]) {
            if (!visited[v] && weight > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == t) {
                    return true;
                }
            }
        }
    }
    return false;
}

int fordFulkersonList(GraphList& graph, int src, int dest) {
    GraphList residualGraph = graph;
    std::vector<int> parent(graph.V);
    int maxFlow = 0;
    while (bfsList(residualGraph, src, dest, parent)) {
        int pathFlow = INT_MAX;
        for (int v = dest; v != src; v = parent[v]) {
            int u = parent[v];
            for (auto& [adjV, weight] : residualGraph.adjList[u]) {
                if (adjV == v) {
                    pathFlow = std::min(pathFlow, weight);
                }
            }
        }
        for (int v = dest; v != src; v = parent[v]) {
            int u = parent[v];
            for (auto& [adjV, weight] : residualGraph.adjList[u]) {
                if (adjV == v) {
                    weight -= pathFlow;
                }
            }
            for (auto& [adjV, weight] : residualGraph.adjList[v]) {
                if (adjV == u) {
                    weight += pathFlow;
                }
            }
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

bool bfsMatrix(const GraphMatrix& graph, int s, int t, std::vector<int>& parent) {
    std::vector<bool> visited(graph.V, false);
    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < graph.V; ++v) {
            if (!visited[v] && graph.matrix[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == t) {
                    return true;
                }
            }
        }
    }
    return false;
}

int fordFulkersonMatrix(GraphMatrix& graph, int src, int dest) {
    GraphMatrix residualGraph = graph;
    std::vector<int> parent(graph.V);
    int maxFlow = 0;
    while (bfsMatrix(residualGraph, src, dest, parent)) {
        int pathFlow = INT_MAX;
        for (int v = dest; v != src; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, residualGraph.matrix[u][v]);
        }
        for (int v = dest; v != src; v = parent[v]) {
            int u = parent[v];
            residualGraph.matrix[u][v] -= pathFlow;
            residualGraph.matrix[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

void displayMST(const std::vector<Edge>& mst) {
    std::cout << "Minimalne drzewo rozpinajace:\n";
    for (const auto& edge : mst) {
        std::cout << edge.src << " - " << edge.dest << " (waga: " << edge.weight << ")\n";
    }
}

void displayShortestPath(int src, int dest, const std::vector<int>& dist, const std::vector<int>& path) {
    if (dist[dest] == INT_MAX) {
        std::cout << "Brak sciezki z " << src << " do " << dest << "\n";
    } else {
        std::cout << "Najkrotsza sciezka z " << src << " do " << dest << " (koszt: " << dist[dest] << "): ";
        std::vector<int> fullPath;
        for (int v = dest; v != -1; v = path[v]) {
            fullPath.push_back(v);
        }
        std::reverse(fullPath.begin(), fullPath.end());
        for (int v : fullPath) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
}
