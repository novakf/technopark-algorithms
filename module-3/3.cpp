/*
3. Города
Требуется отыскать самый выгодный маршрут между городами.
*/

#include <cassert>
#include <iostream>
#include <set>
#include <vector>

struct Route {
  explicit Route(int town, int time) : town_(town), time_(time) {}

  int town_, time_;
};

struct ListGraph {
 public:
  ListGraph(int size) : adjacencyLists(size) {}

  void AddEdge(int from, int to, int weight);
  int VerticesCount() const;

  std::vector<std::pair<int, int>> GetNextVertices(int vertex) const;
  std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const;

 private:
  std::vector<std::vector<std::pair<int, int>>> adjacencyLists;
};

void ListGraph::AddEdge(int from, int to, int weight) {
  assert(0 <= from && from < adjacencyLists.size());
  assert(0 <= to && to < adjacencyLists.size());

  adjacencyLists[from].push_back(std::make_pair(to, weight));
}

int ListGraph::VerticesCount() const {
  return static_cast<int>(adjacencyLists.size());
}

std::vector<std::pair<int, int>> ListGraph::GetNextVertices(int vertex) const {
  assert(0 <= vertex && vertex < adjacencyLists.size());

  return adjacencyLists[vertex];
}

std::vector<std::pair<int, int>> ListGraph::GetPrevVertices(int vertex) const {
  assert(0 <= vertex && vertex < adjacencyLists.size());

  std::vector<std::pair<int, int>> prevVertices;

  for (int from = 0; from < adjacencyLists.size(); from++) {
    for (std::pair<int, int> to : adjacencyLists[from]) {
      if (to.second == vertex) {
        prevVertices.push_back(std::make_pair(from, to.second));
      }
    }
  }

  return prevVertices;
}

class WeightLessComparator {
 public:
  bool operator()(std::pair<int, int> const &A,
                  std::pair<int, int> const &B) const {
    if (A.first == B.first) {
      return false;
    }
    if (A.second == B.second) return A.first < B.first;
    return A.second < B.second;
  }
};

int getShortestWay(int startPoint, int endPoint, ListGraph graph,
                   int townsCount, int roadsCount) {
  std::set<std::pair<int, int>, WeightLessComparator> routes;

  std::vector<unsigned int> shortestWayLength(townsCount, 2500000000);  // d[]
  std::vector<int> previousPoint(townsCount);                           // p[]

  shortestWayLength[startPoint] = 0;
  previousPoint[startPoint] = -1;

  routes.insert(std::make_pair(startPoint, 0));

  while (!routes.empty()) {
    std::pair<int, int> currentTown = *routes.begin();
    routes.erase(routes.begin());

    for (auto nextTown : graph.GetNextVertices(currentTown.first)) {
      int nextWayLength =
          shortestWayLength[currentTown.first] + nextTown.second;

      if (nextWayLength < shortestWayLength[nextTown.first]) {
        shortestWayLength[nextTown.first] = nextWayLength;
        
        routes.insert(
            std::make_pair(nextTown.first, shortestWayLength[nextTown.first]));
      }
    }

    if (currentTown.first == endPoint) break;
  }

  unsigned int target = shortestWayLength[endPoint];

  return target == 2500000000 ? 0 : target;
}

int main(int argc, const char *argv[]) {
  int townsCount;
  int roadsCount;

  std::cin >> townsCount;
  std::cin >> roadsCount;
  ListGraph listGraph(townsCount);

  int from, to, time;
  for (int i = 0; i < roadsCount; i++) {
    std::cin >> from >> to >> time;
    listGraph.AddEdge(from, to, time);
    listGraph.AddEdge(to, from, time);
  }

  int startPoint, endPoint;
  std::cin >> startPoint >> endPoint;

  std::cout << getShortestWay(startPoint, endPoint, listGraph, townsCount,
                              roadsCount);

  return 0;
}
