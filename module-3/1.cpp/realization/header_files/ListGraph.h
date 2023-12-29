#include <vector>

#include "IGraph.h"

struct ListGraph : public IGraph {
 public:
  ListGraph(int size) : adjacencyLists(size) {}
  ListGraph(const IGraph &graph);

  ~ListGraph() {}

  void AddEdge(int from, int to) override;
  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  std::vector<std::vector<int>> adjacencyLists;
};