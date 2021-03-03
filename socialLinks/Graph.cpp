#include "Graph.h"



Graph::Graph(const Person* persons) {
    for (int i = 0; i < SIZE; i++) {
        vertexes[i].SetId(persons[i].Id());
        vertexes[i].SetName(persons[i].Name());
        for (int j = 0; j < SIZE; j++)
            matrix[i][j] = 0;
    }
        
    vertexCount = persons->Size();
}

Graph::~Graph() {}

// проверка существования ребра
bool Graph::edgeExists(int v1, int v2) {
    return matrix[v1][v2] != 0;
}

// проверка существования вершины
bool Graph::vertexExists(int v) {
    for (int i = 0; i < vertexCount; i++)
        if (vertexes[i].Id() == v)
            return true;
    return false;
}

int Graph::findMinWayDFS(int from, int to) {

    bool visited[SIZE];

    for (int i = 0; i < SIZE; ++i)
        visited[i] = false;

    int currentPathLen = 0;
    int minPathLen = VERYBIGINT;
    findMinWayDFSInner(from, to, visited, minPathLen, currentPathLen);
    return minPathLen;
}

void Graph::findMinWayDFSInner(int from, int to, bool visited[], int& minPathLen, int& currentPathLen) {
    if (from == to) {
        if ((minPathLen > currentPathLen)) {
            minPathLen = currentPathLen;
        }
        return;
    }
    visited[from] = true;

    for (int i = 0; i < SIZE; ++i)
    {
        if (edgeExists(from, i) && !visited[i])
        {
            int newPathLen = currentPathLen + matrix[from][i];
            findMinWayDFSInner(i, to, visited, minPathLen, newPathLen);
        }

    }
    visited[from] = false;
}

// добавление ребра
void Graph::addEdge(const Person& p1, const Person& p2, int weight) {
    matrix[p1.Id()][p2.Id()] = weight;
    matrix[p2.Id()][p1.Id()] = weight;
}

std::vector<std::pair<int, int>> Graph::findAll3HandshakeFor(int from) {
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < vertexCount; ++i) {
        if (from == i)
            continue;
        if (findMinWayDFS(from, i) <= 3) {
            pairs.push_back(std::make_pair(0, i));
        }
    }
    return pairs;
}


/*
// добавление вершины
void Graph::addVertex(const Person& person) {
    vertexes[vertexCount++] = person;
}

Graph::Graph(const int sizeOfSocialNetwork, const Person* persons)
    : vertexCount(sizeOfSocialNetwork) {
    
    matrix = new int* [sizeOfSocialNetwork];
    vertexes = new Person[sizeOfSocialNetwork];
    // alocate memory for matrix[][]
    for (int i = 0; i < vertexCount; ++i)
        matrix[i] = new int[vertexCount];


    for (int i = 0; i < vertexCount; ++i) {
        vertexes[i] = persons[i];
        for (int j = 0; j < vertexCount; ++j) {
            matrix[i][j] = 1;
        }
    }
}
 




void Graph::delVertex(int vnumber) {
    if (!vertexExists(vnumber))
        return;
    // find an index of v
    int indexOfV = 0;
    for (int i = 0; i < vertexCount; ++i) {
        if (vertexes[i].Id() == vnumber) {
            indexOfV = i;
            break;
        }
    }
    // set to zero row and col of v
    for (int i = 0; i < vertexCount; ++i) {
        matrix[i][indexOfV] = 0;
        matrix[indexOfV][i] = 0;
    }
    // 
    vertexCount--;
    for (int i = indexOfV; i < vertexCount; ++i)
        vertexes[i] = vertexes[i + 1];
}

void Graph::delEdge(int v1, int v2) {
    if (edgeExists(v1, v2)) {
        matrix[v1][v2] = 0; // it symmetric 
        matrix[v2][v1] = 0;
    }
}

void Graph::depthInner(int current, bool visited[]) {
    std::cout << "V" << current << "->";

    visited[current] = true;

    for (int i = 0; i < SIZE; ++i) {
        if (edgeExists(current, i) && !visited[i])
            depthInner(i, visited);
    }
}

void Graph::depth(int start) {
    bool visited[SIZE];

    for (int i = 0; i < SIZE; ++i)
        visited[i] = false;

    depthInner(start, visited);

    std::cout << std::endl;
}

void Graph::width(int start) {
    int queue_to_visit[SIZE]; // очередь вершин для обхода
    int queueCount = 0;

    bool visited[SIZE]; // список посещенных вершин
    for (int i = 0; i < SIZE; i++)
        visited[i] = false;

    queue_to_visit[queueCount++] = start; // кладем в очередь начальную вершину
    while (queueCount > 0)
    {
        // взятие из очереди вершины
        int current = queue_to_visit[0];
        queueCount--;
        for (int i = 0; i < queueCount; i++)
        {
            queue_to_visit[i] = queue_to_visit[i + 1];
        }
        visited[current] = true;
        std::cout << "v" << current << " -> ";
        // поиск смежных вершин и добавление их в очередь
        for (int i = 0; i < SIZE; i++)
        {
            bool alreadyAdded = false;
            for (int j = 0; j < queueCount; j++)
                if (queue_to_visit[j] == i)
                {
                    alreadyAdded = true;
                    break;
                }
            if (!alreadyAdded && edgeExists(current, i) && !visited[i])
                queue_to_visit[queueCount++] = i;
        }
    }
    std::cout << std::endl;
}

int Graph::findPathCount(int from, int to) {

    bool visited[SIZE];
    for (int i = 0; i < SIZE; ++i)
        visited[i] = false;

    int counter = 0;
    findPathCounterInner(from, to, visited, counter);
    return counter;
}

void Graph::findPathCounterInner(int from, int to, bool visited[], int& counter) {
    // recursion base exit moment
    if (from == to) {
        counter++;
        return;
    }

    visited[from] = true;

    for (int i = 0; i < SIZE; ++i)
        if (edgeExists(from, i) && !visited[i])
            findPathCounterInner(i, to, visited, counter);

    visited[from] = false;
}

void Graph::findMinDistanceDecstr(int fromVert)
{
    int distances[SIZE]; // массив меток
    for (int i = 0; i < SIZE; i++) { // инициализация меток
        distances[i] = VERYBIGINT;
    }
    distances[fromVert] = 0;

    bool passed[SIZE]; // признак, что вершина окрашена
    for (int i = 0; i < SIZE; i++) {
        passed[i] = false; // все неокрашены изначально
    }
    // принимаем стартовую вершину за текущую
    int currentVertexNum = fromVert;
    int min_dist = 0;
    while (min_dist != VERYBIGINT) {
        passed[currentVertexNum] = true; // окрашиваем текущую

        for (int i = 0; i < SIZE; i++) {
            // для смежных ребер пересчитываем метки
            if (edgeExists(currentVertexNum, i) && distances[currentVertexNum] + matrix[currentVertexNum][i] < distances[i])
                distances[i] = distances[currentVertexNum] + matrix[currentVertexNum][i];
        }
        min_dist = VERYBIGINT;
        for (int i = 0; i < SIZE; i++)
        {
            // выбираем новую текущую вершину
            // выбор новой вершины
            if (vertexExists(i) && !passed[i] && distances[i] < min_dist) {
                min_dist = distances[i];
                currentVertexNum = i;
            }
        }
    }

    for (int i = 0; i < vertexCount; i++) // вывод результата
    {
        std::cout << "V" << i << ": " << distances[vertexes[i].Id()] << ", ";
    }
    std::cout << std::endl;
}

void Graph::findMinDistancesFloyd()
{
    int weights[SIZE][SIZE]; // матрица путей
    // инициализаци матрицы
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == j) {
                weights[i][j] = 0; // путь до самой себя равен 0
            }
            else {
                if (!edgeExists(i, j)) {
                    weights[i][j] = VERYBIGINT; // если ребра нет
                }
                else {
                    weights[i][j] = matrix[i][j]; // если ребро есть
                }
            }
        }
    }

    for (int k = 0; k < vertexCount; k++) // итерации по k
    {
        int ck = vertexes[k].Id(); // возьмем номер вершины
        for (int i = 0; i < vertexCount; i++)
        {
            if (i == k)
                continue;
            int ci = vertexes[i].Id();
            for (int j = 0; j < vertexCount; j++) {
                if (j == k)
                    continue;
                int cj = vertexes[j].Id();
                if (weights[ci][ck] + weights[ck][cj] < weights[ci][cj]) {
                    // пересчет мматрицы путей
                    weights[ci][cj] = weights[ci][ck] + weights[ck][cj];
                }
            }
        }
    }

    for (int i = 0; i < vertexCount; i++) {
        // вывод всех минимальных путей от вершины '0'
        std::cout << "V" << i << ": " << weights[0][vertexes[i].Id()] << ", ";
    }
}



*/


