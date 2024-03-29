/*
2. Количество различных путей
Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших
путей между какими-то вершинами. Найдите количество различных кратчайших путей
между заданными вершинами.
*/

#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>

struct ListGraph {
 public:
  ListGraph(int size) : adjacencyLists(size) {}

  void AddEdge(int from, int to);
  int VerticesCount() const;

  std::vector<int> GetNextVertices(int vertex) const;
  std::vector<int> GetPrevVertices(int vertex) const;

 private:
  std::vector<std::vector<int>> adjacencyLists;
};

void ListGraph::AddEdge(int from, int to) {
  assert(0 <= from && from < adjacencyLists.size());
  assert(0 <= to && to < adjacencyLists.size());

  adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
  return static_cast<int>(adjacencyLists.size());
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
  assert(0 <= vertex && vertex < adjacencyLists.size());

  return adjacencyLists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
  assert(0 <= vertex && vertex < adjacencyLists.size());

  std::vector<int> prevVertices;

  for (int from = 0; from < adjacencyLists.size(); from++) {
    for (int to : adjacencyLists[from]) {
      if (to == vertex) {
        prevVertices.push_back(from);
      }
    }
  }

  return prevVertices;
}



int getShortestWaysCount(int startPoint, int endPoint, ListGraph graph,
                         int verticesCount, int edgesCount) {
  std::vector<int> shortestWayLength(verticesCount, edgesCount);  // d[]
  std::vector<int> shortestWaysCounter(verticesCount, 0);         // k[]

  shortestWayLength[startPoint] = 0;
  shortestWaysCounter[startPoint] = 1;

  std::queue<int> qu;
  qu.push(startPoint);

  while (!qu.empty()) {
    int currentVertex = qu.front();
    qu.pop();

    for (int nextVertex : graph.GetNextVertices(currentVertex)) {
      if (shortestWayLength[currentVertex] + 1 <
          shortestWayLength[nextVertex]) {
        shortestWayLength[nextVertex] = shortestWayLength[currentVertex] + 1;
        shortestWaysCounter[nextVertex] = shortestWaysCounter[currentVertex];
        qu.push(nextVertex);
      } else if (shortestWayLength[currentVertex] + 1 ==
                 shortestWayLength[nextVertex]) {
        shortestWaysCounter[nextVertex] += shortestWaysCounter[currentVertex];
      }
    }
  }

  return shortestWaysCounter[endPoint];
}

int main(int argc, const char *argv[]) {
  int v;  // кол-во вершин
  int n;  // кол-во ребер

  std::cin >> v;
  std::cin >> n;
  ListGraph listGraph(v);

  int from, to;
  for (int i = 0; i < n; i++) {
    std::cin >> from >> to;
    listGraph.AddEdge(from, to);
    listGraph.AddEdge(to, from);
  }

  int startPoint, endPoint;
  std::cin >> startPoint >> endPoint;

  std::cout << getShortestWaysCount(startPoint, endPoint, listGraph, v, n);

  return 0;
}
