from dataclasses import dataclass
from functools import reduce
from itertools import batched, zip_longest
import itertools
import operator
from aoc_util import AOCBase, aoc_run
import numpy as np

@dataclass
class Input:
    nums: np.ndarray
    ops: list[str]
    raw_lines: list[str]

class Day6(AOCBase):
    def process_input(self, raw_input: str) -> Input:
        lines = list(filter(None, raw_input.split('\n')))

        return Input(
                np.transpose([list(map(int, line.split())) for line in lines[:-1]]),
                lines[-1].split(),
                lines
        )

    def part1(self, inp: Input) -> int:
        res = 0

        for ns,op in zip(inp.nums, inp.ops):
            if op == '+': opf = operator.add
            elif op == '*': opf = operator.mul
            else: assert False
            res += reduce(opf, ns)

        return res

    def part2(self, inp: Input) -> int:
        # Kinda recreating and parsing everything but whatever
        # don't feel like rewriting part 1 now

        res = 0

        lines = [[*l] for l in inp.raw_lines[:-1]]
        str_nums = np.transpose(lines)

        grp = iter(str_nums)
        for op in inp.ops:
            if op == '+': 
                r = 0
                opf = operator.add
            elif op == '*': 
                r = 1
                opf = operator.mul
            else: assert False

            for g in grp:
                if all(not e.strip() for e in g): break
                i = int("".join(g))
                r = opf(r, i)
            res += r

        return res

if __name__ == "__main__":
    aoc_run(2025, 6, Day6)
