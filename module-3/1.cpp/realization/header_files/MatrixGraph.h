#include <vector>
#include <iostream>
#include "IGraph.h"

struct MatrixGraph : public IGraph {
 public:
  MatrixGraph(int size) : adjacencyMatrix(size, std::vector<int>(size, 0)) {
    for (int i = 0; i < size; i++) {
      for (int el : adjacencyMatrix[i]) {
        std::cout << el << " ";
      }
      std::cout << std::endl;
    }
  }
  MatrixGraph(const IGraph &graph);

  ~MatrixGraph() {}

  void AddEdge(int from, int to) override;
  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  std::vector<std::vector<int>> adjacencyMatrix;
};