#include <iostream>
#include <vector>
using namespace std;

class Graph // Класс, представляющий граф
{
public:
    int V; // Количество вершин
    vector<vector<int>> adj; // Список смежности

    Graph(int V) // Конструктор класса для инициализации графа с заданным количеством вершин
    {
        this->V = V; // Инициализация числа вершин
        adj.resize(V); // Инициализация списка смежности с размером V
    }

    void addEdge(int u, int v) // Метод для добавления ребра между вершинами u и v в граф
    {
        adj[u].push_back(v); // Добавление ребра между вершинами u и v
    }

    bool isCyclicUtil(int v, int visited[], int recStack[]) // функция для проверки наличия циклов в графе
    {
        visited[v] = 1; // Помечаем вершину как посещенную
        recStack[v] = 1; // Помечаем вершину как находящуюся в стеке

        for (int neighbor : adj[v])
        {
            if (visited[neighbor] == 0) // Если соседняя вершина не была посещена
            {
                if (isCyclicUtil(neighbor, visited, recStack)) // Если нашли цикл, возвращаем true
                {
                    return true;
                }
            }
            else if (recStack[neighbor] == 1) // Если соседняя вершина находится в стеке нашли цикл
            {
                return true;
            }
        }
        recStack[v] = 0; // Извлечение вершины из стека
        return false; // Нет цикла
    }

    bool isCyclic() // Метод для определения, содержит ли граф циклы
    {
        int* visited = new int[V]; // Массив для отслеживания посещенных вершин
        int* recStack = new int[V]; // Массив для отслеживания вершин в стеке

        for (int i = 0; i < V; i++)
        {
            visited[i] = 0; // Инициализация как не посещенные
            recStack[i] = 0; // Инициализация как не в стеке
        }

        for (int i = 0; i < V; i++)
        {
            if (visited[i] == 0 && isCyclicUtil(i, visited, recStack)) // Если нашли цикл в графе, возвращаем true
            {
                delete[] visited;
                delete[] recStack;
                return true;
            }
        }

        delete[] visited;
        delete[] recStack;
        return false; // Нет цикла в графе
    }

    bool isConnected() // Метод для проверки связности графа
    {
        for (int i = 0; i < V; i++)
        {
            int* visited = new int[V]; // Массив для отслеживания посещенных вершин
            for (int j = 0; j < V; j++)
            {
                visited[j] = 0; // Инициализация как не посещенные
            }
            dfs(i, visited); // Вызов функции поиска в глубину (DFS)
            delete[] visited; // Освобождение памяти
        }
        return true; // Граф связный
    }

    void dfs(int v, int visited[]) // Рекурсивная функция для обхода графа в глубину
    {
        visited[v] = 1; // Помечаем вершину как посещенную
        for (int neighbor : adj[v])
        {
            if (visited[neighbor] == 0) // Если соседняя вершина не была посещена
            {
                dfs(neighbor, visited); // Рекурсивно идем дальше
            }
        }
    }
};

int main()
{
    setlocale(0, "");


    Graph g(6);

    // Добавляем рёбра
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(1, 6);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(4, 1); //для проверки на цикличность


    // Проверяем, является ли граф связным и ацикличным
    bool isCyclic = g.isCyclic();
    bool isStronglyConnected = g.isConnected();

    if (isCyclic)
    {
        cout << "Граф является цикличным" << endl;
    }
    else
    {
        cout << "Граф не является цикличным" << endl;
    }

    if (isStronglyConnected)
    {
        cout << "Граф является связным" << endl << endl;
    }
    else
    {
        cout << "Граф не является связным" << endl;
    }

    return 0;
}
