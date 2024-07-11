#pragma once

#ifndef MSF_HPP
#define MSF_HPP

#include <algorithm>
#include <cassert>
#include <numeric>
#include <queue>
#include <vector>

#include "graph.hpp"

// Implementierung einer klassischen `UnionFind`-Datenstruktur; die Klasse kann
// zur Kompilierzeit mit den Parametern `PathCompression` und `UnionByRank`
// konfiguriert werden.
template <bool PathCompression, bool UnionByRank>  //
class UnionFind {
 public:
  constexpr static bool path_compression = PathCompression;
  constexpr static bool union_by_rank = UnionByRank;

 private:
  // Die Klasse Parents speichert die Elternknoten der einzelnen Knoten.
  // Die Klasse hat einen Konstruktor, der die Anzahl der Knoten `n` erwartet
  // und dann die Knoten 0, 1, ..., n-1 als Singleton-Gruppen initialisiert
  // (d.h. jeder Knoten ist sein eigener Elternknoten).
  //
  // Die Methode `get_parent` gibt den Elternknoten eines Knoten `x` zurück und
  // erhöht dabei die Anzahl der Zugriffe auf die Elternknoten.
  //
  // Die Methode `set_parent` setzt den Elternknoten eines Knoten `x` auf einen
  // neuen Wert und erhöht dabei die Anzahl der Zugriffe auf die Elternknoten.
  class Parents {
    std::vector<Node> parent;
    uint64_t parent_accesses{0};

   public:
    Parents() = delete;
    Parents(Node n) : parent(n) { std::iota(parent.begin(), parent.end(), 0); }

    Node get_parent(Node x, bool count = true) {
      assert(static_cast<size_t>(x) < parent.size());
      parent_accesses += count;
      return parent[x];
    }

    void set_parent(Node x, Node p) {
      assert(static_cast<size_t>(x) < parent.size());
      assert(static_cast<size_t>(p) < parent.size());
      parent_accesses++;
      parent[x] = p;
    }

    uint64_t get_parent_accesses() const {  //
      return parent_accesses;
    }
  };
  Parents parents;
  std::vector<Count> rank;

  Count num_groups;

 public:
  UnionFind() = delete;
  UnionFind(Node n) : parents(n), rank(n, 0), num_groups(n) {}

  Node find(Node x) {
    const auto parent_x = parents.get_parent(x);
    if (parent_x == x) return x;

    Node representant_x = find(parent_x);

    if constexpr (PathCompression) {
      parents.set_parent(x, representant_x);
    }

    return representant_x;
  }

  void link(Node root_x, Node root_y) {
    if constexpr (UnionByRank) {
      if (rank[root_y] < rank[root_x])
        parents.set_parent(root_y, root_x);
      else {
        parents.set_parent(root_x, root_y);
        if (rank[root_x] == rank[root_y]) rank[root_y]++;
      }
    } else {
      parents.set_parent(root_x, root_y);
    }

    num_groups--;
  }

  void combine(Node x, Node y) {
    Node root_x = find(x);
    Node root_y = find(y);

    link(root_x, root_y);
  }

  Node get_parent(Node x) {  //
    return parents.get_parent(x, false);
  }

  Count number_of_groups() const {  //
    return num_groups;
  }

  uint64_t number_of_parent_accesses() const {
    return parents.get_parent_accesses();
  }
};

using UnionFindNoPCNoRank = UnionFind<false, false>;
using UnionFindPCOnly = UnionFind<true, false>;
using UnionFindRankOnly = UnionFind<false, true>;
using UnionFindPCAndRank = UnionFind<true, true>;

// Die Funktion `max_node` berechnet den größten Knoten-Index,
// der in den Kanten `edges` vorkommt.
Node max_node(std::vector<Edge> &edges) {
  assert(edges.size());

  // PERF: max_element of an vector with a custom compare function, that just
  // compares bigger of the nodes indicies
  auto m = *std::max_element(
      edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return std::max(a.from, a.to) < std::max(b.from, b.to);
      });

  return std::max(m.from, m.to);
}

struct KruskalResult {
  std::vector<Edge> msf_edges;

  Weight total_weight;
  bool is_spanning_tree;

  uint64_t parent_accesses;
};

template <typename UnionFind>
KruskalResult kruskal(std::vector<Edge> &edges) {
  std::vector<Edge> msf_edges;

  Node n = max_node(edges);
  UnionFind uf(n + 1);
  Weight total_weight = 0;

  // Step 1: Sort the edges vector in-place
  std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
    return a.weight < b.weight; // Note: Sorting in ascending order of weights
  });

  // Step 2: Iterate through the sorted vector of edges
  for (const Edge& edge : edges) {
    // Check if the nodes are in different sets
    if (uf.find(edge.from) != uf.find(edge.to)) {
      // Since they are in different sets, combine them
      uf.combine(edge.from, edge.to);
      // Add the edge to the MSF and update the total weight
      msf_edges.push_back(edge);
      total_weight += edge.weight;
    }
  }

  return KruskalResult{msf_edges, total_weight, uf.number_of_groups() == 1,
                       uf.number_of_parent_accesses()};
}

#endif  // MSF_HPP
