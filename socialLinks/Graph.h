#pragma once
#include "Person.h"
#include <iostream>
#include <vector>
#include <utility>


#define SIZE 8
#define VERYBIGINT 1000000000 

class Graph {
public:
    Graph(const Person* persons);
    ~Graph();
    int findMinWayDFS(int from, int to);
    void addEdge(const Person& p1, const Person& p2, int weight);
    std::vector<std::pair<int, int>> findAll3HandshakeFor(int from);
    /*
    void addVertex(const Person& person);

    void delVertex(int vnumber);

    void delEdge(int v1, int v2);

    // depth-first search
    void depth(int start);

    // width-first search
    void width(int start);

    // алгоритм поиска количества всех возможных путей между двумя вершинами графа на основе графа матрицы смежности
    int findPathCount(int from, int to);

    // algo дейкстры
    void findMinDistanceDecstr(int fromVert);

    // algo floyd
    void findMinDistancesFloyd();

    // поиска минимального расстояния между двумя вершинами в графе
    
    */
private:
    
    bool edgeExists(int v1, int v2);
    
    bool vertexExists(int v);

    /*
    // recursion part of dfs
    void depthInner(int current, bool visited[]);
    void findPathCounterInner(int from, int to, bool visited[], int& counter);
    */
    void findMinWayDFSInner(int from, int to, bool visited[], int& minPathLen, int& currentPathLen);
     
    int matrix[SIZE][SIZE]; // матрица смежности
    Person vertexes[SIZE];  // хранилище вершин
    int vertexCount;        // количество добавленных вершин
};




