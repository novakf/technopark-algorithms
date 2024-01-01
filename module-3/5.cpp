/*
Задача 5. Приближенное решение метрической неориентированной задачи
коммивояжера. Для построения минимального остовного дерева используйте алгоритм
Крускала.
*/

#include <cassert>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

struct Route {
  explicit Route(int from, int to, int weight)
      : from_(from), to_(to), weight_(weight) {}

  int from_, to_, weight_;
};

struct ListGraph {
 public:
  ListGraph(int size) : routes(size) {}

  void AddEdge(int from, int to, int weight);
  int VerticesCount() const;

  std::vector<std::pair<int, int>> GetNextVertices(int vertex) const;
  std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const;

 private:
  std::vector<Route> routes;
};

void ListGraph::AddEdge(int from, int to, int weight) {
  assert(0 <= from && from < routes.size());
  assert(0 <= to && to < routes.size());

  routes.push_back(Route(from, to, weight));
}

int ListGraph::VerticesCount() const { return static_cast<int>(routes.size()); }

std::vector<std::pair<int, int>> ListGraph::GetNextVertices(int vertex) const {
  std::vector<Route> nextVertices;

  for (std::pair edge :  ) {
    if (edge.first == vertex) nextVertices.push_back(edge.second);
  }

  return nextVertices;
}

std::vector<std::pair<int, int>> ListGraph::GetPrevVertices(int vertex) const {
  assert(0 <= vertex && vertex < routes.size());

  std::vector<std::pair<int, int>> prevVertices;

  for (int from = 0; from < routes.size(); from++) {
    for (std::pair<int, int> to : routes[from]) {
      if (to.second == vertex) {
        prevVertices.push_back(std::make_pair(from, to.second));
      }
    }
  }

  return prevVertices;
}

// система непересекающихся множеств
class DSU {
 public:
  DSU(int count);

  int FindLeader(int v);
  void UnionSets(int v1, int v2);

 private:
  std::vector<int> parent;
  std::vector<int> rank;
};

DSU::DSU(int count) : parent(count), rank(count, 1) {
  for (int i = 0; i < count; i++) {
    parent[i] = i;
  }
}

int DSU::FindLeader(int v) {
  if (v == parent[v]) return v;
  int p = FindLeader(parent[v]);
  parent[v] = p;
  return p;
}

void DSU::UnionSets(int v1, int v2) {
  int p1 = FindLeader(v1);
  int p2 = FindLeader(v2);

  if (p1 == p2) return;

  if (rank[p1] < rank[p2]) {
    parent[p1] = p2;
    rank[p2] += rank[p1];
  } else {
    parent[p2] = p1;
    rank[p1] += rank[p2];
  }

  parent[p2] = p1;
}

int getSpanningTreeWeight(ListGraph graph) {
  DSU tree(graph.VerticesCount());
  std::vector<Route> routes;

  return 0;
}

int main(int argc, const char *argv[]) {
  int verticesCount;
  int edgesCount;

  std::cin >> verticesCount >> edgesCount;
  ListGraph listGraph(verticesCount);

  int from, to, weight;
  for (int i = 0; i < edgesCount; i++) {
    std::cin >> from >> to >> weight;
    listGraph.AddEdge(from - 1, to - 1, weight);
  }

  std::cout << getSpanningTreeWeight(listGraph);

  return 0;
}