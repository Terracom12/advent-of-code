with open("input.txt") as f:
    lines = list(map(list, f.readlines()))

from dataclasses import dataclass
from enum import IntFlag


class Dir(IntFlag):
    none = 0

    up_left = 1
    up_right = 2
    down_left = 4
    down_right = 8

    def corr(self):
        if self == self.up_left:
            return self.down_left
        if self == self.up_right:
            return self.down_right
        if self == self.down_left:
            return self.up_left
        if self == self.down_right:
            return self.up_right

        return self.none


@dataclass
class Cell:
    def __init__(self):
        self.good_dir = {
            "S": Dir.none,
            "A": Dir.none,
            "M": Dir.none,
        }

    def __str__(self) -> str:
        return f"Cell {str(int(self.good_dir['S'])).rjust(2)} {str(int(self.good_dir['A'])).rjust(2)} {str(int(self.good_dir['M'])).rjust(2)}"

    def __repr__(self):
        return str(self)


dp = [[Cell() for _ in lines[0]] for _ in lines]


def in_range(r, c):
    if r < 0 or c < 0:
        return False
    if r >= len(dp) or c >= len(dp[0]):
        return False
    return True


for i, row in enumerate(dp):
    for j, _ in enumerate(row):
        if lines[i][j] != "S":
            continue

        dp[i][j].good_dir["S"] |= (
            Dir.up_left | Dir.up_right | Dir.down_left | Dir.down_right
        )


for i, row in enumerate(dp):
    for j, _ in enumerate(row):
        if lines[i][j] != "A":
            continue

        for ni, nj, dir in [
            (i + 1, j + 1, Dir.up_right),
            (i + 1, j - 1, Dir.up_left),
            (i - 1, j + 1, Dir.down_right),
            (i - 1, j - 1, Dir.down_left),
        ]:
            if not in_range(ni, nj):
                continue
            if dp[ni][nj].good_dir["S"] & dir:
                dp[i][j].good_dir["A"] |= dir

        if dp[i][j].good_dir["A"] == Dir.none:
            lines[i][j] = "."


for i, row in enumerate(dp):
    for j, _ in enumerate(row):
        if lines[i][j] != "M":
            continue

        for ni, nj, dir in [
            (i + 1, j + 1, Dir.up_right),
            (i + 1, j - 1, Dir.up_left),
            (i - 1, j + 1, Dir.down_right),
            (i - 1, j - 1, Dir.down_left),
        ]:
            if not in_range(ni, nj):
                continue
            if dp[ni][nj].good_dir["A"] & dir:
                dp[i][j].good_dir["M"] |= dir

        if dp[i][j].good_dir["M"] == Dir.none:
            lines[i][j] = "."

result = 0
for i, row in enumerate(dp):
    for j,cell in enumerate(row):
        if lines[i][j] != "M":
            continue

        r = result
        for ni, nj, dirs in [
            (i, j + 2, [Dir.up_right, Dir.up_left]),
            (i, j + 2, [Dir.down_right, Dir.down_left]),
            (i + 2, j, [Dir.up_left, Dir.down_left]),
            (i + 2, j, [Dir.up_right, Dir.down_right]),
        ]:
            if not in_range(ni, nj):
                continue

            if cell.good_dir["M"] & dirs[0] and dp[ni][nj].good_dir["M"] & dirs[1]:
                result += 1
        if r == result:
            lines[i][j] = "$"

print(result)
