#include "graph.hpp"
#include "msf.hpp"

#include "testing.hpp"

#define run_test_all_ufs(func)                                                 \
  run_test(func<UnionFindNoPCNoRank>);                                         \
  run_test(func<UnionFindPCOnly>);                                             \
  run_test(func<UnionFindRankOnly>);                                           \
  run_test(func<UnionFindPCAndRank>);

template <typename UnionFind> bool test_union_find_small_hardcoded() {
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

int main() {
  run_test(test_gilbert_graph);

  run_test_all_ufs(test_union_find_small_hardcoded);

  return 0;
}
