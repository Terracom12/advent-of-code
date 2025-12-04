import itertools
from pprint import pprint
from aoc_util import AOCBase, aoc_run

NEIGH = [n for n in itertools.product((-1,0,1), (-1,0,1)) if n != (0,0)]
def in_range(rows: list[list[str]], i: int, j: int) -> bool:
    if i not in range(len(rows)):
        return False
    if j not in range(len(rows[0])):
        return False
    return True

class Day4(AOCBase):
    def process_input(self, raw_input: str) -> list[list[str]]:
        return [[*r] for r in raw_input.split()]

    def part1(self, rows: list[list[str]]) -> int:
        res = 0

        for i,r in enumerate(rows):
            for j,c in enumerate(r):
                if c != '@':
                    continue
                C = [rows[i+ni][j+nj] for ni,nj in NEIGH if in_range(rows,i+ni,j+nj)].count('@')
                if C < 4:
                    res += 1

        return res



    def part2(self, rows: list[list[str]]) -> int:
        # trying to brute force
        res = 0

        removed = -1

        while removed != 0:
            removed = 0
            for i,r in enumerate(rows):
                for j,c in enumerate(r):
                    if c != '@':
                        continue
                    C = [rows[i+ni][j+nj] for ni,nj in NEIGH if in_range(rows,i+ni,j+nj)].count('@')
                    if C < 4:
                        removed += 1
                        rows[i][j] = 'r'
            res += removed

        return res

if __name__ == "__main__":
    aoc_run(2025, 4, Day4)
