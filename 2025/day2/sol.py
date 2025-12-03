from aoc_util import AOCBase, aoc_run

class Day2(AOCBase):
    def process_input(self, raw_input: str) -> list[range]:
        return [range(*map(int, rg.split('-'))) for rg in raw_input.split(',')]

    def part1(self, rgs: list[range]) -> int:
        # Sizes of ranges are low so let's just brute force
        res = 0

        for r in rgs:
            # make inclusive
            for i in range(r.start, r.stop + 1):
                s = str(i)
                l = len(s)
                if l % 2 != 0: 
                    continue

                if s[:l//2] == s[l//2:]:
                    res += i

        return res

    def part2(self, rgs: list[range]) -> int:
        # brute force again
        res = 0

        for r in rgs:
            # make inclusive
            for i in range(r.start, r.stop + 1):
                s = str(i)
                l = len(s)
                for rept in range(1, l // 2 + 1):
                    if l % rept != 0: 
                        continue


                    if all(s[:rept] == s[sl:sl+rept] for sl in range(rept, l, rept)):
                        res += i
                        break

        return res

if __name__ == "__main__":
    aoc_run(2025, 2, Day2)
