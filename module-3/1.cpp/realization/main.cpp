#include <functional>
#include <iostream>
#include <queue>

#include "header_files/ArcGraph.h"
#include "header_files/IGraph.h"
#include "header_files/ListGraph.h"
#include "header_files/MatrixGraph.h"
#include "header_files/SetGraph.h"

void BFSInternal(const IGraph &graph, int vertex, std::vector<bool> &visited,
                 std::function<void(int)> &func) {
  std::queue<int> qu;
  qu.push(vertex);
  visited[vertex] = true;

  while (!qu.empty()) {
    int currentVertex = qu.front();
    qu.pop();

    func(currentVertex);

    for (int nextVertex : graph.GetNextVertices(currentVertex)) {
      if (!visited[nextVertex]) {
        visited[nextVertex] = true;
        qu.push(nextVertex);
      }
    }
  }
}

void BFS(const IGraph &graph, std::function<void(int)> func) {
  std::vector<bool> visited(graph.VerticesCount(), false);

  for (int i = 0; i < graph.VerticesCount(); i++) {
    if (!visited[i]) BFSInternal(graph, i, visited, func);
  }
}

void DFSInternal(const IGraph &graph, int vertex, std::vector<bool> &visited,
                 std::function<void(int)> &func) {
  visited[vertex] = true;
  func(vertex);

  for (int nextVertex : graph.GetNextVertices(vertex)) {
    if (!visited[nextVertex]) DFSInternal(graph, nextVertex, visited, func);
  }
}

void DFS(const IGraph &graph, std::function<void(int)> func) {
  std::vector<bool> visited(graph.VerticesCount(), false);

  for (int i = 0; i < graph.VerticesCount(); i++) {
    if (!visited[i]) DFSInternal(graph, i, visited, func);
  }
}

int main(int argc, const char *argv[]) {
  ListGraph listGraph(6);
  listGraph.AddEdge(0, 1);
  listGraph.AddEdge(0, 2);
  listGraph.AddEdge(2, 3);
  listGraph.AddEdge(0, 4);
  listGraph.AddEdge(0, 5);

  std::cout << "ListGraph" << std::endl;
  std::cout << "BFS: ";
  BFS(listGraph, [](int vertex) { std::cout << vertex << " "; });
  std::cout << std::endl;
  std::cout << "DFS: ";
  DFS(listGraph, [](int vertex) { std::cout << vertex << " "; });
  std::cout << std::endl << std::endl;

  std::cout << "ArcGraph" << std::endl;
  ArcGraph arcGraph(listGraph);
  std::cout << "BFS: ";
  BFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });
  std::cout << std::endl;
  std::cout << "DFS: ";
  DFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });
  std::cout << std::endl << std::endl;

  std::cout << "MatrixGraph" << std::endl;
  MatrixGraph matrixGraph(arcGraph);
  std::cout << "BFS: ";
  BFS(matrixGraph, [](int vertex) { std::cout << vertex << " "; });
  std::cout << std::endl;
  std::cout << "DFS: ";
  DFS(matrixGraph, [](int vertex) { std::cout << vertex << " "; });
  std::cout << std::endl << std::endl;

  std::cout << "SetGraph" << std::endl;
  SetGraph setGraph(matrixGraph);
  std::cout << "BFS: ";
  BFS(setGraph, [](int vertex) { std::cout << vertex << " "; });
  std::cout << std::endl;
  std::cout << "DFS: ";
  DFS(setGraph, [](int vertex) { std::cout << vertex << " "; });
  std::cout << std::endl;

  return 0;
}