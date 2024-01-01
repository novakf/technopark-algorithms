/*
3. Who let the Rick out?
Рик и Морти снова бороздят просторы вселенных, но решили ограничиться только
теми, номера которых меньше M. Они могут телепортироваться из вселенной с
номером z во вселенную (z+1) mod M за a бутылок лимонада или во вселенную (z2+1)
mod M за b бутылок лимонада. Рик и Морти хотят добраться из вселенной с номером
x во вселенную с номером y. Сколько бутылок лимонада отдаст Рик за такое
путешествие, если он хочет потратить их как можно меньше?
*/

#include <cassert>
#include <climits>
#include <iostream>
#include <set>
#include <vector>

struct ListGraph {
 public:
  ListGraph(int size) : adjacencyLists(size) {}

  void AddEdge(int from, int to, int weight);
  int VerticesCount() const;

  std::vector<std::pair<int, int>> GetNextVertices(int vertex) const;

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

class WeightLessComparator {
 public:
  bool operator()(std::pair<int, int> const &A,
                  std::pair<int, int> const &B) const {
    if (A.second == B.second) return A.first < B.first;
    return A.second < B.second;
  }
};

int getShortestWay(int startPoint, int endPoint, ListGraph graph,
                   int verticesCount) {
  std::set<std::pair<int, int>, WeightLessComparator> routes;

  std::vector<unsigned int> shortestWayLength(verticesCount, 100000000);  // d[]

  shortestWayLength[startPoint] = 0;

  routes.insert(std::make_pair(startPoint, 0));

  while (!routes.empty()) {
    std::pair<int, int> currentVertice = *routes.begin();
    routes.erase(routes.begin());

    for (auto nextVertice : graph.GetNextVertices(currentVertice.first)) {
      int nextWayLength =
          shortestWayLength[currentVertice.first] + nextVertice.second;

      if (nextWayLength < shortestWayLength[nextVertice.first]) {
        shortestWayLength[nextVertice.first] = nextWayLength;

        routes.insert(std::make_pair(nextVertice.first,
                                     shortestWayLength[nextVertice.first]));
      }
    }
  }

  unsigned int target = shortestWayLength[endPoint];

  return target == 100000000 ? 0 : target;
}

int main(int argc, const char *argv[]) {
  int a;  // вес ребра для первого типа пути
  int b;  // вес ребра для второго типа пути
  int M;  // число вершин
  int x;  // начальная вершина
  int y;  // конечная вершина

  std::cin >> a >> b >> M >> x >> y;
  ListGraph listGraph(M);

  for (int z = 0; z < M; z++) {
    listGraph.AddEdge(z, (z + 1) % M, a);
    listGraph.AddEdge(z, ((long long)z * z + 1) % M, b);
  }

  std::cout << getShortestWay(x, y, listGraph, M);

  return 0;
}
