#include <iostream>
#include "Graph.h"
#include "Algorithms.h"
#include "Utility.h"

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
// Display the graph in both list and matrix representations
void displayGraph(const GraphList& graphList, const GraphMatrix& graphMatrix) {
    std::cout << "Reprezentacja listowa:\n";
    for (int u = 0; u < graphList.V; ++u) {
        std::cout << u << ": ";
        for (const auto& [v, weight] : graphList.adjList[u]) {
            std::cout << "(" << v << ", " << weight << ") ";
        }
        std::cout << "\n";
    }
    std::cout << "\nReprezentacja macierzowa:\n";
    for (const auto& row : graphMatrix.matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

// Menu for user interaction
void menu() {
    GraphList graphList(0, 0);
    GraphMatrix graphMatrix(0, 0);
    bool graphGenerated = false;

    while (true) {
        std::cout << "Wybierz operacje:\n";
        std::cout << "1. Wczytaj dane z pliku\n";
        std::cout << "2. Wygeneruj graf losowo\n";
        std::cout << "3. Testuj algorytmy na grafie\n";
        std::cout << "4. Wyjscie\n";
        int operation;
        std::cin >> operation;
        if (operation == 4) break;

        if (operation == 1 || operation == 2) {
            std::cout << "Wybierz reprezentacje grafu:\n";
            std::cout << "1. Lista sasiedztwa\n";
            std::cout << "2. Macierz incydencji\n";
            int repr;
            std::cin >> repr;

            if (operation == 1) {
                std::string filename;
                std::cout << "Podaj nazwe pliku: ";
                std::cin >> filename;
                if (repr == 1) {
                    graphList = readGraphFromFileList(filename);
                    graphMatrix = convertListToMatrix(graphList);
                } else {
                    graphMatrix = readGraphFromFileMatrix(filename);
                    graphList = convertMatrixToList(graphMatrix);
                }
            } else {
                int V;
                double density;
                std::cout << "Podaj liczbe wierzcholkow: ";
                std::cin >> V;
                std::cout << "Podaj gestosc grafu (w %): ";
                std::cin >> density;
                density /= 100;
                if (repr == 1) {
                    graphList = generateRandomGraphList(V, density);
                    graphMatrix = convertListToMatrix(graphList);
                } else {
                    graphMatrix = generateRandomGraphMatrix(V, density);
                    graphList = convertMatrixToList(graphMatrix);
                }
            }
            graphGenerated = true;
            displayGraph(graphList, graphMatrix);
        } else if (operation == 3) {
            if (!graphGenerated) {
                std::cout << "Najpierw wczytaj lub wygeneruj graf.\n";
                continue;
            }

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
                if (repr == 1) {
                    if (algo == 1) {
                        double time = measureTime([&] { return primMSTList(graphList); });
                        auto result = primMSTList(graphList);
                        displayMST(result);
                        std::cout << "Czas wykonania: " << time << " sekund\n";
                    } else {
                        double time = measureTime([&] { return kruskalMSTList(graphList); });
                        auto result = kruskalMSTList(graphList);
                        displayMST(result);
                        std::cout << "Czas wykonania: " << time << " sekund\n";
                    }
                } else {
                    if (algo == 1) {
                        double time = measureTime([&] { return primMSTMatrix(graphMatrix); });
                        auto result = primMSTMatrix(graphMatrix);
                        displayMST(result);
                        std::cout << "Czas wykonania: " << time << " sekund\n";
                    } else {
                        double time = measureTime([&] { return kruskalMSTMatrix(graphMatrix); });
                        auto result = kruskalMSTMatrix(graphMatrix);
                        displayMST(result);
                        std::cout << "Czas wykonania: " << time << " sekund\n";
                    }
                }
            } else if (choice == 2) {
                std::cout << "Wybierz algorytm:\n";
                std::cout << "1. Algorytm Dijkstry\n";
                std::cout << "2. Algorytm Bellmana-Forda\n";
                int algo;
                std::cin >> algo;
                int src, dest;
                std::cout << "Podaj wierzcholek poczatkowy: ";
                std::cin >> src;
                std::cout << "Podaj wierzcholek koncowy: ";
                std::cin >> dest;
                std::cout << "Wybierz reprezentacje grafu:\n";
                std::cout << "1. Lista sasiedztwa\n";
                std::cout << "2. Macierz incydencji\n";
                int repr;
                std::cin >> repr;
                if (repr == 1) {
                    if (algo == 1) {
                        double time = measureTime([&] { return dijkstraList(graphList, src, dest); });
                        auto [dist, path] = dijkstraList(graphList, src, dest);
                        displayShortestPath(src, dest, dist, path);
                        std::cout << "Czas wykonania: " << time << " sekund\n";
                    } else {
                        double time = measureTime([&] { return bellmanFordList(graphList, src, dest); });
                        auto [dist, path] = bellmanFordList(graphList, src, dest);
                        displayShortestPath(src, dest, dist, path);
                        std::cout << "Czas wykonania: " << time << " sekund\n";
                    }
                } else {
                    if (algo == 1) {
                        double time = measureTime([&] { return dijkstraMatrix(graphMatrix, src, dest); });
                        auto [dist, path] = dijkstraMatrix(graphMatrix, src, dest);
                        displayShortestPath(src, dest, dist, path);
                        std::cout << "Czas wykonania: " << time << " sekund\n";
                    } else {
                        double time = measureTime([&] { return bellmanFordMatrix(graphMatrix, src, dest); });
                        auto [dist, path] = bellmanFordMatrix(graphMatrix, src, dest);
                        displayShortestPath(src, dest, dist, path);
                        std::cout << "Czas wykonania: " << time << " sekund\n";
                    }
                }
            } else if (choice == 3) {
                int src, dest;
                std::cout << "Podaj wierzcholek poczatkowy: ";
                std::cin >> src;
                std::cout << "Podaj wierzcholek koncowy: ";
                std::cin >> dest;
                std::cout << "Wybierz reprezentacje grafu:\n";
                std::cout << "1. Lista sasiedztwa\n";
                std::cout << "2. Macierz incydencji\n";
                int repr;
                std::cin >> repr;
                if (repr == 1) {
                    double time = measureTime([&] { return fordFulkersonList(graphList, src, dest); });
                    int maxFlow = fordFulkersonList(graphList, src, dest);
                    std::cout << "Maksymalny przeplyw: " << maxFlow << "\n";
                    std::cout << "Czas wykonania: " << time << " sekund\n";
                } else {
                    double time = measureTime([&] { return fordFulkersonMatrix(graphMatrix, src, dest); });
                    int maxFlow = fordFulkersonMatrix(graphMatrix, src, dest);
                    std::cout << "Maksymalny przeplyw: " << maxFlow << "\n";
                    std::cout << "Czas wykonania: " << time << " sekund\n";
                }
            }
        }
    }
}

int main() {
    menu();
    return 0;
}
