#include <vector>

#include "IGraph.h"

struct ArcGraph : public IGraph {
 public:
  ArcGraph(int size) : edges(0) {}
  ArcGraph(const IGraph &graph);

  ~ArcGraph() {}

  void AddEdge(int from, int to) override;
  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  std::vector<std::pair<int, int>> edges;
};