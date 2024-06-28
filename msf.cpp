#include "msf.hpp"
#include "graph.hpp"
#include <fstream>
#include <random>

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

      if (n < max_n / 100) {
        auto res = kruskal<UnionFindNoPCNoRank>(edges);
        output << n << ',' << m << ',' << avg_deg << ",naive,"
               << res.parent_accesses << std::endl;
      }

      // Hier sollen weitere Varianten vermessen werden
    }
  }

  return 0;
}
