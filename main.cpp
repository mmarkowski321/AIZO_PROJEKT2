#include <iostream>
#include "Graph.h"
#include "Algorithms.h"
#include "Utility.h"
#include <numeric>

// Konwersja macierzy incydencji na listę sąsiedztwa
GraphList convertMatrixToList(const GraphMatrix& graphMatrix) {
    GraphList graphList(graphMatrix.V, graphMatrix.E);
    for (int u = 0; u < graphMatrix.V; ++u) {
        for (int v = 0; v < graphMatrix.V; ++v) {
            if (graphMatrix.matrix[u][v] != 0) {
                graphList.addEdge(u, v, graphMatrix.matrix[u][v]);
            }
        }
    }
    return graphList;
}

// Function to convert a list representation to a matrix representation
GraphMatrix convertListToMatrix(const GraphList& graphList) {
    GraphMatrix graphMatrix(graphList.V, graphList.E);
    for (int u = 0; u < graphList.V; ++u) {
        for (const auto& [v, weight] : graphList.adjList[u]) {
            if (graphMatrix.matrix[u][v] == 0) { // Avoid double insertion for undirected graphs
                graphMatrix.addEdge(u, v, weight);
            }
        }
    }
    return graphMatrix;
}

// Funkcja do testowania serii grafów i wyciągania średniej arytmetycznej czasu wykonania
template <typename GraphType, typename GenerateFunc, typename AlgoFunc>
double testAlgorithm(GenerateFunc generate, AlgoFunc algorithm, int V, double density, int iterations = 5) {
    std::vector<double> times;
    for (int i = 0; i < iterations; ++i) {
        GraphType graph = generate(V, density);
        double time = measureTime(algorithm, graph);
        times.push_back(time);
    }
    return std::accumulate(times.begin(), times.end(), 0.0) / times.size();
}

// Menu for user interaction
void menu() {
    while (true) {
        std::cout << "Wybierz operacje:\n";
        std::cout << "1. Testuj algorytmy na grafie\n";
        std::cout << "2. Wyjscie\n";
        int operation;
        std::cin >> operation;
        if (operation == 2) break;

        if (operation == 1) {
            std::cout << "Podaj liczbe wierzcholkow: ";
            int V;
            std::cin >> V;
            std::cout << "Podaj gestosc grafu (w %): ";
            double density;
            std::cin >> density;
            density /= 100;

            std::cout << "Wybierz problem do rozwiazania:\n";
            std::cout << "1. Minimalne Drzewo Rozpinajace (MST)\n";
            std::cout << "2. Najkrotsza Sciezka\n";
            std::cout << "3. Maksymalny Przeplyw\n";
            int choice;
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "Wybierz algorytm:\n";
                std::cout << "1. Algorytm Prima\n";
                std::cout << "2. Algorytm Kruskala\n";
                int algo;
                std::cin >> algo;
                std::cout << "Wybierz reprezentacje grafu:\n";
                std::cout << "1. Lista sasiedztwa\n";
                std::cout << "2. Macierz incydencji\n";
                int repr;
                std::cin >> repr;
                double avgTime;
                if (repr == 1) {
                    if (algo == 1) {
                        avgTime = testAlgorithm<GraphList>(generateRandomGraphList, primMSTList, V, density);
                    } else {
                        avgTime = testAlgorithm<GraphList>(generateRandomGraphList, kruskalMSTList, V, density);
                    }
                } else {
                    if (algo == 1) {
                        avgTime = testAlgorithm<GraphMatrix>(generateRandomGraphMatrix, primMSTMatrix, V, density);
                    } else {
                        avgTime = testAlgorithm<GraphMatrix>(generateRandomGraphMatrix, kruskalMSTMatrix, V, density);
                    }
                }
                std::cout << "Sredni czas wykonania: " << avgTime << " sekund\n";
            } else if (choice == 2) {
                std::cout << "Wybierz algorytm:\n";
                std::cout << "1. Algorytm Dijkstry\n";
                std::cout << "2. Algorytm Bellmana-Forda\n";
                int algo;
                std::cin >> algo;
                std::cout << "Podaj wierzcholek poczatkowy: ";
                int src;
                std::cin >> src;
                std::cout << "Podaj wierzcholek koncowy: ";
                int dest;
                std::cin >> dest;
                std::cout << "Wybierz reprezentacje grafu:\n";
                std::cout << "1. Lista sasiedztwa\n";
                std::cout << "2. Macierz incydencji\n";
                int repr;
                std::cin >> repr;
                double avgTime;
                if (repr == 1) {
                    if (algo == 1) {
                        avgTime = testAlgorithm<GraphList>(
                                [src, dest](int V, double density) { return generateRandomGraphList(V, density); },
                                [src, dest](GraphList& graph) { return dijkstraList(graph, src, dest); },
                                V, density);
                    } else {
                        avgTime = testAlgorithm<GraphList>(
                                [src, dest](int V, double density) { return generateRandomGraphList(V, density); },
                                [src, dest](GraphList& graph) { return bellmanFordList(graph, src, dest); },
                                V, density);
                    }
                } else {
                    if (algo == 1) {
                        avgTime = testAlgorithm<GraphMatrix>(
                                [src, dest](int V, double density) { return generateRandomGraphMatrix(V, density); },
                                [src, dest](GraphMatrix& graph) { return dijkstraMatrix(graph, src, dest); },
                                V, density);
                    } else {
                        avgTime = testAlgorithm<GraphMatrix>(
                                [src, dest](int V, double density) { return generateRandomGraphMatrix(V, density); },
                                [src, dest](GraphMatrix& graph) { return bellmanFordMatrix(graph, src, dest); },
                                V, density);
                    }
                }
                std::cout << "Sredni czas wykonania: " << avgTime << " sekund\n";
            } else if (choice == 3) {
                std::cout << "Podaj wierzcholek poczatkowy: ";
                int src;
                std::cin >> src;
                std::cout << "Podaj wierzcholek koncowy: ";
                int dest;
                std::cin >> dest;
                std::cout << "Wybierz reprezentacje grafu:\n";
                std::cout << "1. Lista sasiedztwa\n";
                std::cout << "2. Macierz incydencji\n";
                int repr;
                std::cin >> repr;
                double avgTime;
                if (repr == 1) {
                    avgTime = testAlgorithm<GraphList>(
                            [src, dest](int V, double density) { return generateRandomGraphList(V, density); },
                            [src, dest](GraphList& graph) { return fordFulkersonList(graph, src, dest); },
                            V, density);
                } else {
                    avgTime = testAlgorithm<GraphMatrix>(
                            [src, dest](int V, double density) { return generateRandomGraphMatrix(V, density); },
                            [src, dest](GraphMatrix& graph) { return fordFulkersonMatrix(graph, src, dest); },
                            V, density);
                }
                std::cout << "Sredni czas wykonania: " << avgTime << " sekund\n";
            }
        }
    }
}

int main() {
    menu();
    return 0;
}
