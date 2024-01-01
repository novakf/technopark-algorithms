/*
2. Проверка пути на гамильтоновость
Нужно проверить, является ли путь в неориентированном графе гамильтоновым.
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

bool isHamiltonian(const ListGraph &graph, std::vector<int> trip) {
  std::vector<bool> visited(graph.VerticesCount(), false);

  for (int i = 0; i < trip.size(); i++) {
    bool pointExists = false;

    for (int vertice : graph.GetNextVertices(trip[i])) {
      if (vertice == trip[(i + 1) % trip.size()]) pointExists = true;
    }

    if (visited[i] == false && pointExists == true)
      visited[i] = true;
    else
      return false;
  }

  for (int vertice : graph.GetNextVertices(trip.size() - 1)) {
    if (vertice == trip[0]) return true;
  }

  return false;
}

int main(int argc, const char *argv[]) {
  int v;  // кол-во вершин
  int n;  // кол-во ребер
  int k;  // количество вершин в пути

  std::cin >> v;
  std::cin >> n;
  std::cin >> k;
  ListGraph listGraph(v);

  int from, to;
  for (int i = 0; i < n; i++) {
    std::cin >> from >> to;
    listGraph.AddEdge(from, to);
    listGraph.AddEdge(to, from);
  }

  std::vector<int> tripVertices(k);

  for (int i = 0; i < k; i++) {
    std::cin >> tripVertices[i];
  }

  std::cout << isHamiltonian(listGraph, tripVertices);

  return 0;
}
