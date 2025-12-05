from dataclasses import dataclass
from aoc_util import AOCBase, aoc_run

@dataclass
class IngDB:
    fresh_rngs: list[range]
    avail: list[int]

class Day5(AOCBase):
    def process_input(self, raw_input: str) -> IngDB:
        rngs_str,avail_str = raw_input.split('\n\n')
        
        return IngDB([range(int(r.split('-')[0]), int(r.split('-')[1])+1) for r in rngs_str.split()],
                     [int(a) for a in avail_str.split()])


    def part1(self, inp: IngDB) -> int:
        res = 0
        for a in inp.avail:
            for r in inp.fresh_rngs:
                if a in r:
                    res += 1
                    break
        return res

    def part2(self, inp: IngDB) -> int:
        res = 0
        inp.fresh_rngs.sort(key=lambda r: r.start)

        last_end = 0
        for r in inp.fresh_rngs:
            if last_end > r.stop:
                continue

            st = max(last_end, r.start)
            res += (r.stop - st)
            last_end = r.stop

        return res

if __name__ == "__main__":
    aoc_run(2025, 5, Day5)
