with open("input.txt") as f:
    lines = f.readlines()

from dataclasses import dataclass
from enum import IntFlag


class Dir(IntFlag):
    none = 0
    left = 1
    right = 2
    up = 4
    down = 8

    up_left = 16
    up_right = 32
    down_left = 64
    down_right = 128

    def inv(self):
        if self == self.left:
            return self.right
        if self == self.right:
            return self.left
        if self == self.up:
            return self.down
        if self == self.down:
            return self.up

        if self == self.up_left:
            return self.down_right
        if self == self.up_right:
            return self.down_left
        if self == self.up_right:
            return self.down_left
        if self == self.down_left:
            return self.up_right

        return self.none


@dataclass
class Cell:
    def __init__(self):
        self.good_dir = {
            "X": Dir.none,
            "M": Dir.none,
            "A": Dir.none,
        }

    def __str__(self) -> str:
        return f"Cell {list(map(int, self.good_dir.values()))}"

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
        if lines[i][j] != "X":
            continue

        dp[i][j].good_dir["X"] |= (
            Dir.left | Dir.right | Dir.up | Dir.down | Dir.up_left | Dir.up_right | Dir.down_left | Dir.down_right
        )


for i, row in enumerate(dp):
    for j, _ in enumerate(row):
        if lines[i][j] != "M":
            continue

        for ni, nj, dir in [
            (i + 1, j, Dir.up),
            (i - 1, j, Dir.down),
            (i, j + 1, Dir.right),
            (i, j - 1, Dir.left),
            (i + 1, j + 1, Dir.up_right),
            (i + 1, j - 1, Dir.up_left),
            (i - 1, j + 1, Dir.down_right),
            (i - 1, j - 1, Dir.down_left),
        ]:
            if not in_range(ni, nj):
                continue
            if dp[ni][nj].good_dir["X"] & dir:
                dp[i][j].good_dir["M"] |= dir


for i, row in enumerate(dp):
    for j, _ in enumerate(row):
        if lines[i][j] != "A":
            continue

        for ni, nj, dir in [
            (i + 1, j, Dir.up),
            (i - 1, j, Dir.down),
            (i, j + 1, Dir.right),
            (i, j - 1, Dir.left),
            (i + 1, j + 1, Dir.up_right),
            (i + 1, j - 1, Dir.up_left),
            (i - 1, j + 1, Dir.down_right),
            (i - 1, j - 1, Dir.down_left),
        ]:
            if not in_range(ni, nj):
                continue
            if dp[ni][nj].good_dir["M"] & dir:
                dp[i][j].good_dir["A"] |= dir


result = 0

for i, row in enumerate(dp):
    for j, _ in enumerate(row):
        if lines[i][j] != "S":
            continue

        for ni, nj, dir in [
            (i + 1, j, Dir.up),
            (i - 1, j, Dir.down),
            (i, j + 1, Dir.right),
            (i, j - 1, Dir.left),
            (i + 1, j + 1, Dir.up_right),
            (i + 1, j - 1, Dir.up_left),
            (i - 1, j + 1, Dir.down_right),
            (i - 1, j - 1, Dir.down_left),
        ]:
            if not in_range(ni, nj):
                continue
            if dp[ni][nj].good_dir["A"] & dir:
                result += 1

print(result)
