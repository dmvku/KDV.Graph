#pragma once
#include <string>
#include <iostream>

#define SIZE 25
#define VERYBIGINT 1000000000 // очень большое число

class Graph {

public:
    Graph();
    // добавление вершины
    void addVertex(std::string vName);
    // добавление ребра
    void addEdge(int vertex1, int vertex2, int weight);
    // добавление ребра - перегрузка функции
    void addEdge(std::string vName1, std::string vName2, int weight = 1);

    
    int getNumberByName(std::string vName);

    
    std::string getNameByNumber(int vNumber);

    // Для проверки, существует ли ребро, нужно посмотреть значение элемента
    // матрицы смежности с индексами номеров вершин (если есть ребро, он отличен от 0).
    bool edgeExists(int vertex1, int vertex2);

    // Для проверки, существует ли вершина, нужно проверить,
    // есть ли ее имя или номер в массиве vertexes.
    int vertexExists(int vNumber);
    int vertexExists(std::string vName);

    // удаление вершины
    void delVertex(int vNumber);

    // удаление ребра
    void delEdge(int vertex1, int vertex2);

    // обход графа в глубину - подготовка к рекурсивному обходу
    void depth(int vNumber);
    // обход графа в глубину - рекурсивный обход
    void depthInner(int current, bool visited[]);
    
    // обход графа в ширину
    void width(int vNumber);

    // поиска количества всех возможных путей между двумя
    // вершинами графа - подготовка к рекурсивному обходу
    int pathCount(int from, int to);
    // поиска количества всех возможных путей между двумя
    // вершинами графа - рекурсивный обход
    void pathCountInner(int current, int to, bool visited[], int& count);

    // поиска минимального пути между двумя вершинами 
    // взвешенного графа - подготовка к рекурсивному обходу
    int findMinWayDFS(int v1, int v2);

    // поиска минимального пути между двумя вершинами 
    // взвешенного графа - рекурсивный обход        
    void inner(int current, int to, bool visited[], int& min, int currentDistance);

    // поиск кратчайшего расстояния от определенной вершины до
    // всех других во взвешенном графе - алгоритм Дейкстра
    void findMinDistanceDecstr(int fromVert);

    // поиск кратчайшего расстояния между любой парой
    // вершин во взвешенном графе - алгоритм Флойда
    void findMinDistancesFloyd();

    // печать таблицы взаимоотношений
    void printFriend(int friendshipLevel);

private:
    int matrix[SIZE][SIZE]; // матрица смежности

    int vertexNumber[SIZE]{};
    std::string vertexName[SIZE]{}; // хранилище вершин
    int vertexCount{}; // количество добавленных вершин 
};
