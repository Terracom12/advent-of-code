import numpy as np

class Map:
    ROWS: int
    COLS: int
    obstacles: set[tuple[int, int]]
    guard: list[int]

    def __init__(self, lines: list[str]):
        self.ROWS = len(lines)
        self.COLS = len(lines[0])
        self.obstacles = set()

        for y,line in enumerate(lines):
            for x,c in enumerate(line):
                if c == "#":
                    self.obstacles.add((x, y))
                elif c == "^":
                    self.guard = [x, y]

    def in_bounds(self, x: int, y: int):
        return 0 <= x < self.COLS and 0 <= y < self.ROWS

def part1(m: Map) -> int:
    dir = np.mat([[0, -1]])

    ROT_90 = np.mat(
        [[0, 1],
         [-1, 0]]
    )

    seen: set[tuple[int, int]] = set()
    result = 0

    while m.in_bounds(*m.guard):
        if (*m.guard,) not in seen:
            result += 1
            seen.add((*m.guard,))

        new_pos = m.guard.copy()

        new_pos[0] += dir[0, 0]
        new_pos[1] += dir[0, 1]

        if (*new_pos,) in m.obstacles:
            dir *= ROT_90
            continue

        m.guard = new_pos

    return result

def part2(m: Map):
    dir = np.mat([[0, -1]])

    ROT_90 = np.mat(
        [[0, 1],
         [-1, 0]]
    )

    prev_dirs: dict[tuple[int, int], np.matrix] = {}
    result = 0

    while m.in_bounds(*m.guard):
        if (*m.guard,) not in prev_dirs:
            prev_dirs[(*m.guard,)] = dir

        new_pos = m.guard.copy()

        new_pos[0] += dir[0, 0]
        new_pos[1] += dir[0, 1]

        if (*new_pos,) in m.obstacles:
            dir *= ROT_90
            continue
        
        if (*m.guard,) in prev_dirs:
            if prev_dirs[(*m.guard,)] == dir * ROT_90 and m.in_bounds(*new_pos):
                result += 1

        m.guard = new_pos

    return result

def main():
    with open("input.txt") as f:
        lines = f.readlines()

    m = Map(lines)

    print("Part 1:", part1(m))

if __name__ == "__main__":
    main()
