/*
1. Количество компонент связности
Посчитать кол-во компонент связности в неориентированном графе.
*/

#include <cassert>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

struct ListGraph {
 public:
  ListGraph(int size) : adjacencyLists(size) {}

  void AddEdge(int from, int to);
  int VerticesCount() const;

  std::vector<int> GetNextVertices(int vertex) const;

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

void DFSInternal(const ListGraph &graph, int vertex,
                 std::vector<bool> &visited) {
  visited[vertex] = true;

  for (int nextVertex : graph.GetNextVertices(vertex)) {
    if (!visited[nextVertex]) DFSInternal(graph, nextVertex, visited);
  }
}

int getGraphComponentsCount(const ListGraph &graph) {
  std::vector<bool> visited(graph.VerticesCount(), false);

  int componentsCount = 0;

  for (int i = 0; i < graph.VerticesCount(); i++) {
    if (!visited[i]) {
      componentsCount++;
      DFSInternal(graph, i, visited);
    }
  }

  return componentsCount;
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

  std::cout << getGraphComponentsCount(listGraph);

  return 0;
}
