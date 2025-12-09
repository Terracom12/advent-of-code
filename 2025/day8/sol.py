from collections import Counter
from functools import reduce
import itertools
import operator
from aoc_util import AOCBase, aoc_run

class UnionFind:
    def __init__(self, n: int):
        self._parents = [i for i in range(n)]
        self._size = [1] * n

    def get_parent(self, n: int) -> int:
        p = self._parents[n]
        if p != n:
            p = self._parents[n] = self.get_parent(p)
        return self._parents[n]

    def union(self, a: int, b: int) -> int:
        ap = self.get_parent(a)
        bp = self.get_parent(b)

        asz = self._size[ap]
        bsz = self._size[bp]

        if ap == bp: 
            return asz

        if ap > bp:
            self._parents[bp] = ap
            self._size[ap] += bsz
        else:
            self._parents[ap] = bp;
            self._size[bp] += asz

        return asz + bsz

    def find(self, a: int, b: int) -> bool:
        return self.get_parent(a) == self.get_parent(b)

    def get_unions(self) -> Counter:
        for i in range(len(self._parents)):
            self._parents[i] = self.get_parent(i)
        return Counter(self._parents)

def dist(a: tuple[int,int,int], b: tuple[int,int,int]) -> int:
    return sum(abs(aa - bb) ** 2 for aa,bb in zip(a,b))

class Day8(AOCBase):
    def process_input(self, raw_input: str) -> list[tuple[int,int,int]]:
        lines = raw_input.split()
        return [(*map(int, l.split(',')),) for l in lines]

    def part1(self, inp) -> int:
        L = len(inp)

        uf = UnionFind(L)

        # (idx,idx)
        pairs = list(itertools.combinations(range(L), 2))
        pairs.sort(key=lambda it: dist(inp[it[0]],inp[it[1]]))

        NCONNECTIONS = 10 if len(inp) < 25 else 1000

        for ai,bi in pairs[:NCONNECTIONS]:
            uf.union(ai, bi)

        us = uf.get_unions()
        sizes_only = list(sorted(us.values()))

        return reduce(operator.mul, sizes_only[-3:])


    def part2(self, inp) -> int:
        L = len(inp)

        uf = UnionFind(L)

        # (idx,idx)
        pairs = list(itertools.combinations(range(L), 2))
        pairs.sort(key=lambda it: dist(inp[it[0]],inp[it[1]]))

        for ai,bi in pairs:
            usz = uf.union(ai, bi)

            if usz == L:
                print("got", inp[ai], inp[bi])
                return inp[ai][0] * inp[bi][0]

        return -1


if __name__ == "__main__":
    aoc_run(2025, 8, Day8)
