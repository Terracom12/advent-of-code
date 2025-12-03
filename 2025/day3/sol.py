from aoc_util import AOCBase, aoc_run

class Day3(AOCBase):
    def process_input(self, raw_input: str) -> list[str]:
        return [l for l in raw_input.split('\n') if l]

    def part1(self, lines: list[str]) -> int:
        res = 0

        for line in lines:
            prev_largest = 0
            best = 0
            for j in map(int, line):
                best = max(best, 10 * prev_largest + j)
                prev_largest = max(prev_largest, j)
            res += best

        return res

    def part2(self, lines: list[str]) -> int:
        # pretty sure there's a 2D dp solution but brute forcing it seems easy for now
        res = 0

        for line in lines:
            print("LINE", line)
            best = ""
            start = 0
            for e in range(12):
                if e == 11:
                    sub = line[start:]
                else:
                    sub = line[start:e-11]
                c = max(sub)
                start += sub.index(c) + 1
                best += c
            res += int(best)
        return res

if __name__ == "__main__":
    aoc_run(2025, 3, Day3)
