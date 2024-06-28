#pragma once

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <random>
#include <tuple>
#include <vector>

#include "testing.hpp"

using Node = uint32_t;
using Count = Node;
using Weight = float;

struct Edge {
  Node from;
  Node to;
  Weight weight;
};

std::vector<Edge> generate_gilbert_graph(std::mt19937_64 &gen, Node n,
                                         double avg_degree) {
  const double p = avg_degree / (n - 1);
  std::vector<Edge> edges;

  std::geometric_distribution<ptrdiff_t> geom(p);
  ptrdiff_t cursor = -1;

  const ptrdiff_t max_edges =
      static_cast<ptrdiff_t>(n) * static_cast<ptrdiff_t>(n);

  std::uniform_real_distribution<float> weight(0.0, 1.0);

  while (true) {
    cursor += geom(gen) + 1;
    if (cursor >= max_edges)
      break;

    Node i = cursor / n;
    Node j = cursor % n;

    if (i >= j)
      continue;

    Weight w = weight(gen);
    edges.push_back({i, j, w});
  }

  return edges;
}

bool test_gilbert_graph() {
  std::mt19937_64 gen(42);

  constexpr Node n = 1000;
  constexpr double avg_degree = 10.0;

  auto edges = generate_gilbert_graph(gen, n, avg_degree);
  fail_unless(edges.size() > static_cast<size_t>(n * avg_degree / 4));
  fail_unless(edges.size() < static_cast<size_t>(n * avg_degree));

  const size_t m = edges.size();
  std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
    return std::tie(a.from, a.to) < std::tie(b.from, b.to);
  });
  edges.erase(std::unique(edges.begin(), edges.end(),
                          [](const Edge &a, const Edge &b) {
                            return std::tie(a.from, a.to) ==
                                   std::tie(b.from, b.to);
                          }),
              edges.end());

  fail_unless_eq(edges.size(), m);

  for (const auto &edge : edges) {
    fail_if_eq(edge.from, edge.to);
    fail_unless(edge.weight >= 0.0);
    fail_unless(edge.weight <= 1.0);
  }

  return true;
}

#endif // GRAPH_HPP
