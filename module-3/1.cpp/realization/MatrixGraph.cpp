#include "header_files/MatrixGraph.h"

#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

MatrixGraph::MatrixGraph(const IGraph &graph)
    : adjacencyMatrix(graph.VerticesCount(),
                      std::vector<int>(graph.VerticesCount(), 0)) {
  for (int from = 0; from < graph.VerticesCount(); from++) {
    for (int to : graph.GetNextVertices(from)) {
      adjacencyMatrix[from][to] = 1;
    }
  }
}

void MatrixGraph::AddEdge(int from, int to) {
  assert(0 <= from && from < adjacencyMatrix.size());
  assert(0 <= to && to < adjacencyMatrix.size());

  adjacencyMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
  return static_cast<int>(adjacencyMatrix.size());
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
  assert(0 <= vertex && vertex < adjacencyMatrix.size());
  std::vector<int> nextVertices;
  
  for (int to = 0; to < adjacencyMatrix.size(); to++) {
    if (adjacencyMatrix[vertex][to] != 0) nextVertices.push_back(to);
  }

  return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
  assert(0 <= vertex && vertex < adjacencyMatrix.size());
  std::vector<int> prevVertices;

  for (int from = 0; from < adjacencyMatrix.size(); from++) {
    if (adjacencyMatrix[from][vertex] != 0) prevVertices.push_back(from);
  }

  return prevVertices;
}
