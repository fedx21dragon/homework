#include <cstdio>
#include <memory>
#include <vector>

#include "graph.hpp"
#include "msf.hpp"
#include "testing.hpp"

#define run_test_all_ufs(func)         \
  run_test(func<UnionFindNoPCNoRank>); \
  run_test(func<UnionFindPCOnly>);     \
  run_test(func<UnionFindRankOnly>);   \
  run_test(func<UnionFindPCAndRank>);

template <typename UnionFind>
bool test_union_find_small_hardcoded() {
  UnionFind uf(4);

  fail_unless_eq(uf.find(0), Node(0));
  fail_unless_eq(uf.find(1), Node(1));
  fail_unless_eq(uf.find(2), Node(2));
  fail_unless_eq(uf.find(3), Node(3));

  uf.combine(0, 1);
  fail_unless_eq(uf.find(0), uf.find(1));
  fail_unless(uf.find(0) <= Node(1));
  fail_unless_eq(uf.find(2), Node(2));
  fail_unless_eq(uf.find(3), Node(3));

  uf.combine(2, 3);
  fail_unless_eq(uf.find(0), uf.find(1));
  fail_unless_eq(uf.find(2), uf.find(3));
  fail_if_eq(uf.find(0), uf.find(2));

  uf.combine(1, 3);
  fail_unless_eq(uf.find(0), uf.find(1));
  fail_unless_eq(uf.find(2), uf.find(3));
  fail_unless_eq(uf.find(0), uf.find(3));

  return true;
}

template <typename UnionFind>
bool test_union_find_pc_and_rank() {
  UnionFind uf(6);

  uf.combine(2, 1);
  uf.combine(1, 3);
  // INFO: No path compression directly after combine. Path is *being
  // compressed* in find, so program needs to run find() to compress paths

  uf.find(2);

  if (UnionFind::path_compression) {
    fail_unless_eq(uf.get_parent(2), uf.get_parent(1));
  }

  uf.combine(0, 4);
  uf.combine(3, 4);
  uf.combine(3, 5);

  if (UnionFind::union_by_rank) {
    fail_if_eq(uf.get_parent(4), Node(3));
    fail_if_eq(uf.get_parent(3), Node(5));
  }

  return true;
}

bool test_num_groups() {
  UnionFindPCAndRank uf(5);

  fail_unless_eq(uf.number_of_groups(), (unsigned int)5);

  uf.combine(0, 1);
  uf.combine(2, 3);

  fail_unless_eq(uf.number_of_groups(), (unsigned int)3);

  uf.combine(1, 2);
  uf.combine(0, 3);  // already combined, shouldn't change number_of_groups

  fail_if_eq(uf.number_of_groups(), (unsigned int)1);

  return true;
}

bool test_max_node() {
  std::vector<Edge> edges;

  edges.push_back({0, 1, 1});
  edges.push_back({0, 2, 1});
  edges.push_back({0, 3, 1});
  edges.push_back({0, 4, 1});
  edges.push_back({0, 5, 1});
  edges.push_back({7, 5, 1});
  edges.push_back({8, 5, 1});
  edges.push_back({9, 5, 1});
  edges.push_back({10, 5, 1});

  fail_unless_eq(max_node(edges), Node(10));

  edges.push_back({10, 500, 1});

  fail_unless_eq(max_node(edges), Node(500));

  edges.pop_back();
  edges.pop_back();

  fail_unless_eq(max_node(edges), Node(9));

  /*
   * std::vector<Edge> empty;
   * fail_unless_eq(max_node(empty), Node(-1));
   * */

  return true;
}

int main() {
  run_test(test_gilbert_graph);

  run_test_all_ufs(test_union_find_small_hardcoded);

  run_test_all_ufs(test_union_find_pc_and_rank);

  run_test(test_num_groups);

  run_test(test_max_node);

  return 0;
}
