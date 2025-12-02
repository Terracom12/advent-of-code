from dataclasses import dataclass
from typing import Literal
from aoc_util import AOCBase, aoc_run

@dataclass
class Rot:
    dir: str
    amt: int

class Day1(AOCBase):
    def process_input(self, raw_input: str) -> list[Rot]:
        return [Rot(rot[0], int(rot[1:])) for rot in raw_input.split('\n') if rot]

    def part1(self, rots: list[Rot]) -> int:
        pos = 50
        res = 0

        for r in rots:
            dir = None

            if r.dir == 'L':
                dir = -1
            else:
                dir = 1

            pos += r.amt * dir
            pos %= 100

            if pos == 0:
                res += 1

        return res

    def part2(self, rots: list[Rot]) -> int:
        p = (len(rots) < 100)

        pos = 50
        res = 0
        lastpos = pos

        for r in rots:
            dir = None

            if r.dir == 'L':
                dir = -1
            else:
                dir = 1

            pos += r.amt * dir
            pos %= 100

            if p: print(r, "r=", res, "@", pos)
            if r.dir == 'L' and pos > lastpos and lastpos:
                res += 1
            elif r.dir == 'R' and pos < lastpos:
                res += 1

            if pos == 0 and lastpos != 0 and r.dir != 'R':
                res += 1

            res += r.amt // 100
            if p: print("->", res, "@", pos)
            lastpos = pos

        return res

if __name__ == "__main__":
    aoc_run(2025, 1, Day1)
