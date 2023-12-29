#include <vector>
#include <set>
#include <string>
#include "IGraph.h"
#include "HashTable.h"

struct SetGraph : public IGraph {
 public:
  SetGraph(int size) : adjacencySet(size) {}
  SetGraph(const IGraph &graph);

  ~SetGraph() {}

  void AddEdge(int from, int to) override;
  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  std::vector<HashTable<int>> adjacencySet;
};