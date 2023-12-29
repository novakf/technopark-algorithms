#include "header_files/SetGraph.h"

#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

SetGraph::SetGraph(const IGraph &graph) : adjacencySet(graph.VerticesCount()) {
  for (int i = 0; i < graph.VerticesCount(); i++) {
    for (int nextVertice : graph.GetNextVertices(i))
      adjacencySet[i].Add(nextVertice);
  }
}

void SetGraph::AddEdge(int from, int to) {
  assert(0 <= from && from < adjacencySet.size());
  assert(0 <= to && to < adjacencySet.size());
  adjacencySet[from].Add(to);
}

int SetGraph::VerticesCount() const {
  return static_cast<int>(adjacencySet.size());
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
  assert(0 <= vertex && vertex < adjacencySet.size());
  std::vector<int> nextVertices;

  for (int i = 0; i < adjacencySet.size(); i++) {
    if (adjacencySet[vertex].Has(i)) nextVertices.push_back(i);
  }

  return nextVertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
  assert(0 <= vertex && vertex < adjacencySet.size());
  std::vector<int> prevVertices;

  for (int from = 0; from < adjacencySet.size(); from++) {
    for (int i = 0; i < adjacencySet.size(); i++) {
      if (adjacencySet[from].Has(i)) {
        prevVertices.push_back(from);
      }
    }
  }
  return prevVertices;
}
