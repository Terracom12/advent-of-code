from functools import cache


def part1(stones: list[int], t: int) -> int:
    @cache
    def dp(s: int, t: int) -> int:
        if t == 0:
            return 1

        if s == 0:
            return dp(1, t - 1)
        elif (digits := str(s)) and len(digits) % 2 == 0:
            front = int(digits[:len(digits)//2])
            back = int(digits[len(digits)//2:])
            return dp(front, t - 1) + dp(back, t - 1)
        else:
            return dp(s * 2024, t - 1)

    res = 0

    for s in stones:
        res += dp(s, t)

    return res


def main():
    with open("input.txt") as f:
        line = f.readline().split(' ')
        stones = list(map(int, line))

    print("Part 1:", part1(stones, 25))
    print("Part 2:", part1(stones, 75))

if __name__ == "__main__":
    main()
