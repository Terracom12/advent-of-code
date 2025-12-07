from dataclasses import dataclass
from enum import StrEnum
from aoc_util import AOCBase, aoc_run

class Space(StrEnum):
    Air = "."
    Enter = "S"
    Splitter = "^"

@dataclass
class Grid:
    spaces: list[list[Space]]
    start: tuple[int, int]

    @property
    def M(self) -> int:
        return len(self.spaces)
    @property
    def N(self) -> int:
        return len((self.spaces or [[]])[0])

class Day7(AOCBase):
    def process_input(self, raw_input: str) -> Grid:
        lines = raw_input.split()

        start = None

        for i,l in enumerate(lines):
            j =  l.find(Space.Enter)
            if j != -1:
                start = (i,j)
                break

        assert start is not None
        return Grid([[*map(Space, l)] for l in lines], start)

    def part1(self, inp: Grid) -> int:
        V = [[False] * inp.N for _ in range(inp.M)]

        def beam(i: int, j: int) -> int:
            if i not in range(inp.M) or j not in range(inp.N):
                return 0
            if V[i][j] is True:
                return 0
            V[i][j] = True

            if inp.spaces[i][j] is not Space.Splitter:
                return beam(i + 1, j)

            return 1 + beam(i, j - 1) + beam(i, j + 1)

        return beam(*inp.start)

    def part2(self, inp: Grid) -> int:
        V = [[-1] * inp.N for _ in range(inp.M)]
        BI = 0

        bi_map = {}

        def get_splits_tot(grp: int) -> int:
            v = bi_map[grp]
            if type(v) is int:
                return v

            bi_map[grp] = sum(get_splits_tot(g) for g in v)
            return bi_map[grp]

        def beam(i: int, j: int, grp: int = 0) -> int:
            if i not in range(inp.M):
                assert grp not in bi_map.keys()
                bi_map[grp] = 1
                return 1

            if j not in range(inp.N):
                bi_map[grp] = 0
                return 0

            if V[i][j] != -1:
                v = get_splits_tot(V[i][j])
                bi_map[grp] = v
                return v
            V[i][j] = grp

            if inp.spaces[i][j] is not Space.Splitter:
                return beam(i + 1, j, grp)

            nonlocal BI
            NI = BI
            BI += 2

            bi_map[grp] = (NI + 1, NI + 2)

            return beam(i, j - 1, NI + 1) + beam(i, j + 1, NI + 2)

        return beam(*inp.start)

if __name__ == "__main__":
    aoc_run(2025, 7, Day7)
