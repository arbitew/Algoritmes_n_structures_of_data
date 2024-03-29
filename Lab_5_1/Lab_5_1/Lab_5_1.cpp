#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;

// Структура для представления ребра в графе
struct Edge {
    int src, dest, weight;
};

// Структура для представления графа
struct Graph {
    int V, E;
    vector<Edge> edges;
};

// Структура для представления подмножества для алгоритма Краскала
struct Subset {
    int parent, rank;
};

// Создание графа с заданными характеристиками
Graph createGraph(int V, int minAdj, int maxAdj) {
    Graph graph;
    graph.V = V;
    graph.E = 0;

    // Инициализация случайным seed для разнообразия генерации
    srand(time(nullptr));

    for (int i = 0; i < V; ++i) {
        Edge edge;
        edge.src = i;
        int numAdj = rand() % (maxAdj - minAdj + 1) + minAdj;
        for (int j = 0; j < numAdj; ++j) {
            edge.dest = rand() % V;
            // Убеждаемся, что ребро не указывает на ту же вершину
            while (edge.dest == i) {
                edge.dest = rand() % V;
            }
            edge.weight = rand() % 20 + 1;
            graph.edges.push_back(edge);
            ++graph.E;
        }
    }

    return graph;
}

// Находит корень множества, которому принадлежит элемент 'i'
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// Объединяет два множества в одно
void Union(vector<Subset>& subsets, int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Алгоритм Краскала для построения минимального остовного дерева
vector<Edge> KruskalMST(const Graph& graph) {
    vector<Edge> result;

    // Сортируем все рёбра по весу
    vector<Edge> sortedEdges = graph.edges;
    sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
        });

    vector<Subset> subsets(graph.V);
    for (int v = 0; v < graph.V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int e = 0;
    int i = 0;

    // Строим остовное дерево с помощью алгоритма Краскала
    while (e < graph.V - 1 && i < graph.E) {
        Edge next_edge = sortedEdges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result.push_back(next_edge);
            Union(subsets, x, y);
            ++e;
        }
    }

    return result;
}

// Вывод графа в виде матрицы смежности
void printAdjMatrix(const Graph& graph) {
    vector<vector<int>> adjMatrix(graph.V, vector<int>(graph.V, 0));

    for (const auto& edge : graph.edges) {
        adjMatrix[edge.src][edge.dest] = edge.weight;
        adjMatrix[edge.dest][edge.src] = edge.weight;
    }

    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < graph.V; ++i) {
        for (int j = 0; j < graph.V; ++j) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Задаем параметры графа
    vector<int> numVertices = { 10, 20, 50, 100 };
    vector<int> minAdjVertices = { 3, 4, 10, 20 };
    int maxAdjVertices = 50; // Максимальное количество смежных вершин

    // Проводим тесты для каждого набора вершин
    for (int i = 0; i < numVertices.size(); ++i) {
        cout << "Graph with " << numVertices[i] << " vertices:" << endl;

        // Проводим серию тестов
        for (int test = 1; test <= 5; ++test) {
            Graph graph = createGraph(numVertices[i], minAdjVertices[i], maxAdjVertices);
            
            //printAdjMatrix(graph);
            auto start = chrono::steady_clock::now();
            vector<Edge> MST = KruskalMST(graph);
            /*for (Edge i : MST) {
                std::cout << i.src << " " << i.dest << endl;
            }*/
            auto end = chrono::steady_clock::now();

            // Вычисляем время выполнения в миллисекундах
            auto diff = end - start;
            cout << "Test " << test << ": " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
        }

        cout << endl;
    }

    return 0;
}
