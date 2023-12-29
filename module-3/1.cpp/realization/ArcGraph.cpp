#include "header_files/ArcGraph.h"

#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>


ArcGraph::ArcGraph(const IGraph &graph) : edges(graph.VerticesCount()) {
  for (int vertice = 0; vertice < graph.VerticesCount(); vertice++) {
    for (int nextVertice : graph.GetNextVertices(vertice)) {
      edges.push_back(std::make_pair(vertice, nextVertice));
    }
  }
}

void ArcGraph::AddEdge(int from, int to) {
  edges.push_back(std::make_pair(from, to));
}

int ArcGraph::VerticesCount() const {
  std::vector<int> vertices;

  for (std::pair edge : edges) {
    int firstFound = 0;
    int secondFound = 0;
    for (int vertice : vertices) {
      if (vertice == edge.first) firstFound = 1;
      if (vertice == edge.second) secondFound = 1;
    }
    if (firstFound == 0) vertices.push_back(edge.first);
    if (secondFound == 0) vertices.push_back(edge.second);
  }

  return static_cast<int>(vertices.size() - 1);
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
  std::vector<int> nextVertices;

  for (std::pair edge : edges) {
    if (edge.first == vertex) nextVertices.push_back(edge.second);
  }

  return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
  std::vector<int> prevVertices;

  for (std::pair edge : edges) {
    if (edge.second == vertex) prevVertices.push_back(edge.first);
  }

  return prevVertices;
}
