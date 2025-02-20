#include "graph.h"


Graph::Graph() {
    for (int i{ 0 }; i < SIZE; i++)
    {
        for (int j{ 0 }; j < SIZE; j++)
        {
            matrix[i][j] = 0;
        }
    }
    
    vertexCount = 0;    
}

// добавление вершины
void Graph::addVertex(std::string vName)
{
    vertexName[vertexCount] = vName;
    vertexNumber[vertexCount] = vertexCount;    
    vertexCount++;
}

// добавление ребра
void Graph::addEdge(int vertex1, int vertex2, int weight)
{
    matrix[vertex1][vertex2] = weight;
    matrix[vertex2][vertex1] = weight;
}

// добавление ребра - перегрузка функции
void Graph::addEdge(std::string vName1, std::string vName2, int weight)
{
    int vertex1{ getNumberByName(vName1) };
    int vertex2{ getNumberByName(vName2) };
    addEdge(vertex1, vertex2, weight);
}

// получение номера по имени
int Graph::getNumberByName(std::string vName)
{
    for (int i{ 0 }; i < SIZE; i++)
    {
        if (vertexName[i] == vName)
        {
            return i;
        }
    }
    std::cout << "Имя не найдено...\n";
    return -1;
}

// получение имени по номеру
std::string Graph::getNameByNumber(int vNumber)
{
    return vertexName[vNumber];
}

// проверка существования ребра
bool Graph::edgeExists(int vertex1, int vertex2)
{
    // return matrix[v1][v2] != 0
    return matrix[vertex1][vertex2] > 0;
}

// проверка существования вершины по номеру
int Graph::vertexExists(int vNumber)
{
    for (int i{ 0 }; i < vertexCount; i++)
    {
        if (vertexNumber[i] == vNumber)
        {
            return i;
        }
    }

    return 0;
}

// перегрузка функции - проверка существования вершины по имени
int Graph::vertexExists(std::string vName)
{
    for (int i{ 0 }; i < vertexCount; i++)
    {
        if (vertexName[i] == vName)
        {
            return i;
        }
    }

    return 0;
}

// удаление вершины
void Graph::delVertex(int vnumber)
{
    // обнуляем столбец и строку матрицы
    for (int i{ 0 }; i < SIZE; i++)
    {
        matrix[i][vnumber] = 0;
        matrix[vnumber][i] = 0;
    }
    // удаляем вершину из списка вершин
    int foundIndex = -1;
    for (int i{ 0 }; i < vertexCount; i++)
    {
        if (vertexNumber[i] == vnumber)
        {
            foundIndex = i;
        }     
    }
    vertexCount--;
    for(int i = foundIndex; i < vertexCount; i++)
    {
        vertexNumber[i] = vertexNumber[i+1];
        vertexName[i] = vertexName[i + 1];
    }
}

// удаление ребра
void Graph::delEdge(int vertex1, int vertex2)
{
    matrix[vertex1][vertex2] = 0;
    matrix[vertex2][vertex1] = 0;
}

// обход графа в глубину - подготовка к рекурсивному обходу
void Graph::depth(int start)
{
    bool visited[SIZE];         // список посещенных вершин
    for (int i{ 0 }; i < SIZE; i++)
    {
        visited[i] = false;     // инициализируем как непосещенные
    }
       
    depthInner(start, visited); // запуск алгоритма 
    
    std::cout << std::endl;
}

// обход графа в глубину - рекурсивный обход
void Graph::depthInner(int current, bool visited[])
{
    std::cout << "v" << current << " -> "; // вывод текущей вершины
    visited[current]= true;                // помечаем как посещенную
    for (int i{ 0 }; i < SIZE; i++)
    {
        if (edgeExists(current, i) && !visited[i])
        {
            // если существует ребро и вершина не посещалась, 
            // то пройдем по нему в смежную вершину
            depthInner(i, visited);
        }            
    }
}

// обход графа в ширину
void Graph::width(int start)
{
   int queue_to_visit[SIZE];               // очередь вершин для обхода
   int queueCount = 0;

   bool visited[SIZE];                     // список посещенных вершин
   for (int i{ 0 }; i < SIZE; i++)
   {
       visited[i] = false;
   }       
   
   queue_to_visit[queueCount++] = start;   // кладем в очередь начальную вершину
   while(queueCount > 0)
   {
       // взятие из очереди вершины
       int current = queue_to_visit[0];
       queueCount--;
       for (int i{ 0 }; i < queueCount; i++)
       {
           queue_to_visit[i] = queue_to_visit[i+1];
       }
       visited[current] = true;
       std::cout << "v" << current << " -> ";
       // поиск смежных вершин и добавление их в очередь
       for (int i{ 0 }; i < SIZE; i++)
       {
           bool alreadyAdded = false;
           for (int j{ 0 }; j < queueCount; j++)
           {
               if (queue_to_visit[j] == i)
               {
                   alreadyAdded = true;
                   break;
               }
           }
              
           if (!alreadyAdded && edgeExists(current, i) && !visited[i])
           {
               queue_to_visit[queueCount++] = i;
           }               
       }
   }
   std::cout << std::endl;
}

// поиска количества всех возможных путей между двумя
// вершинами графа - подготовка к рекурсивному обходу
int Graph::pathCount(int from, int to)
{
    bool visited[SIZE]; // массив пройденных вершин
    for (int i{ 0 }; i < SIZE; i++)
    {
        visited[i] = false;
    }
       
    int count = 0; // результат
    pathCountInner(from, to, visited, count);
    return count;
}

// поиска количества всех возможных путей между двумя
// вершинами графа - рекурсивный обход в глубину
void Graph::pathCountInner(int current, int to, bool visited[], int& count)
{
    if(current == to) 
    {
       // если дошли до второй вершины, увеличиваем счётчик путей и выходим
       count++;
       return;
    }
    visited[current] = true; // отмечаем как посещенную
    for (int i{ 0 }; i < SIZE; i++)
    {
        if(edgeExists(current, i) && !visited[i])
        {
            pathCountInner(i, to, visited, count);  
        }
    }    
    // отмечаем, что путь уже не содержит эту вершину
    visited[current] = false;
}

// поиска минимального пути между двумя вершинами 
// взвешенного графа - подготовка к рекурсивному обходу
int Graph::findMinWayDFS(int from, int to)
{    
    bool visited[SIZE];     // массив пройденных вершин
    for (int i{ 0 }; i < SIZE; i++)
    {
        visited[i] = false;
    }
       
    int min = VERYBIGINT;   // начальное минимальное расстояние
    int currentDistance = 0;
    
    inner(from,to,visited,min,currentDistance);
    return min;
}

// поиска минимального пути между двумя вершинами 
// взвешенного графа - рекурсивный обход в глубину
void Graph::inner(int current,int to, bool visited[], int& min, int currentDistance)
{
    if(current == to) 
    {
       // если попали в целевую вершину, сравниваем текущий путь с минимальным
       if(min > currentDistance)
       {
           // если новое расстояние меньше, запоминаем
           min = currentDistance;
       }
       return;
    }
    visited[current] = true; // обозначем вершину посещенной
    for (int i{ 0 }; i < SIZE; i++)
    {
        if(edgeExists(current, i) && !visited[i])
        {
            // запускаем рекурсию для всех непосещенных смежных вершин
            int newDist = currentDistance + matrix[current][i];
            inner(i,to, visited, min, newDist);  
        }
    }    
    // отмечаем, что путь уже не содержит эту вершину
    visited[current] = false;            
}

// поиск кратчайшего расстояния от определенной вершины до
// всех других во взвешенном графе - алгоритм Дейкстра
void Graph::findMinDistanceDecstr(int fromVert)
{
    int distances[SIZE];                 // массив меток
    for (int i{ 0 }; i < SIZE; i++)      // инициализация меток
    {
        distances[i] = VERYBIGINT;
    }
    distances[fromVert] = 0;
    
    bool passed[SIZE];                   // признак, что вершина окрашена
    for (int i{ 0 }; i < SIZE; i++)
    {
        passed[i] = false;               // все неокрашены изначально
    }
    // принимаем стартовую вершину за текущую
    int currentVertexNum = fromVert;
    int min_dist = 0;
    while(min_dist != VERYBIGINT)
    {
        passed[currentVertexNum] = true; // окрашиваем текущую
        
        for (int i{ 0 }; i < SIZE; i++)
        {
            // для смежных ребер пересчитываем метки
            if (edgeExists(currentVertexNum, i)
                && distances[currentVertexNum] + matrix[currentVertexNum][i] < distances[i])
            {
                distances[i] = distances[currentVertexNum] + matrix[currentVertexNum][i];
            }                    
        }
        min_dist = VERYBIGINT;
        for (int i{ 0 }; i < SIZE; i++)
        {
            // выбираем новую текущую вершину
            if (vertexExists(i) && !passed[i] && distances[i] < min_dist)
            {
                min_dist = distances[i];
                currentVertexNum = i;
            }
        }
    }

    // вывод результата
    for (int i{ 0 }; i < vertexCount; i++) 
    {
        std::cout << "V" << i << ": " << distances[vertexNumber[i]] << ", ";
    }
    std::cout << std::endl;
}

// поиск кратчайшего расстояния между любой парой
// вершин во взвешенном графе - алгоритм Флойда
void Graph::findMinDistancesFloyd()
{
    int weights[SIZE][SIZE];                      // матрица путей
    // инициализаци матрицы
    for (int i{ 0 }; i < SIZE; i++)
    {
        for(int j =0; j <SIZE; j++)
        {
            if(i == j)
            {
                weights[i][j] = 0;                // путь до самой себя равен 0
            }
            else 
            {
                if(!edgeExists(i,j))
                {
                    weights[i][j] = VERYBIGINT;   // если ребра нет
                }
                else
                {
                    weights[i][j] = matrix[i][j]; // если ребро есть
                }
            }
        }
    }
    
    for (int k{ 0 }; k < vertexCount; k++)        // итерации по k
    {
        int ck = vertexNumber[k];                 // возьмем номер вершины
        for (int i{ 0 }; i < vertexCount; i++)
        {
            if (i == k)
            {
                continue;
            }
                
            int ci = vertexNumber[i]; 
            for (int j{ 0 }; j < vertexCount; j++)
            {
                if (j == k)
                {
                    continue;
                }
                    
                int cj = vertexNumber[j];
                if(weights[ci][ck] + weights[ck][cj] < weights[ci][cj])
                {
                    // пересчет мматрицы путей
                    weights[ci][cj] = weights[ci][ck] + weights[ck][cj];
                }
            }
        }
    }
    
    for (int i{ 0 }; i < SIZE; i++)
    {
        for (int j{ 0 }; j < SIZE; j++)
        {
            matrix[i][j] = weights[i][j];        
        }
    }

    for (int i{ 0 }; i < vertexCount; i++)
    {
        // вывод всех минимальных путей от вершины '0'
        std::cout << "V" << i << ": " << weights[0][vertexNumber[i]] << ", ";
    }
}

void Graph::printFriend(int friendshipLevel)
{
    for (int i{ 0 }; i < vertexCount; i++)
    {
        for (int j{ i + 1 }; j < vertexCount; j++)
        {
            if (matrix[i][j] <= friendshipLevel && matrix[i][j] > 0)
            {
                std::cout << vertexName[i] << " <- " << matrix[i][j] << " -> " << vertexName[j] << "\n";
            }            
        }
    }
}
