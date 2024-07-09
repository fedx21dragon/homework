#include "msf.hpp"

#include <fstream>
#include <random>

#include "graph.hpp"

int main() {
  constexpr Node min_n = 1 << 5;
  constexpr Node max_n = 1 << 21;
  constexpr uint64_t repeats = 5;

  std::ofstream output;
  output.open("kruskal.csv");
  output << "n,m,avg_deg,unionfind,accesses\n";

  const double avg_deg = 5;
  std::mt19937_64 gen(123456);

  for (uint64_t rep = 0; rep < repeats; ++rep) {
    for (Node n = min_n; n <= max_n; n *= 2) {
      auto edges = generate_gilbert_graph(gen, n, avg_deg);
      const auto m = edges.size();
      KruskalResult res;

      if (n < max_n / 100) {
        res = kruskal<UnionFindNoPCNoRank>(edges);
        output << n << ',' << m << ',' << avg_deg << ",naive,"
               << res.parent_accesses << std::endl;
      }

      res = kruskal<UnionFindPCOnly>(edges);
      output << n << ',' << m << ',' << avg_deg << ",pc," << res.parent_accesses
             << std::endl;
      res = kruskal<UnionFindRankOnly>(edges);
      output << n << ',' << m << ',' << avg_deg << ",rank,"
             << res.parent_accesses << std::endl;
      res = kruskal<UnionFindPCAndRank>(edges);
      output << n << ',' << m << ',' << avg_deg << ",pc+rank,"
             << res.parent_accesses << std::endl;

      // Hier sollen weitere Varianten vermessen werden
    }
  }

  output.close();

  return 0;
}
