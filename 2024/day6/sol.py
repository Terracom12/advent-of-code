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
    orig_pos = m.guard.copy()

    def get_traveled_poses() -> list[tuple[int, int]]:
        result = []
        dir = np.mat([[0, -1]])

        ROT_90 = np.mat(
            [[0, 1],
            [-1, 0]]
        )

        seen: set[tuple[int, int]] = set()

        while m.in_bounds(*m.guard):
            if (*m.guard,) not in seen:
                seen.add((*m.guard,))
                result.append((*m.guard,))

            new_pos = m.guard.copy()

            new_pos[0] += dir[0, 0]
            new_pos[1] += dir[0, 1]

            if (*new_pos,) in m.obstacles:
                dir *= ROT_90
                continue

            m.guard = new_pos

        return result

    def is_looping(start: list[int]) -> bool:
        # Try obstacle at each traveled pos
        m.guard = start.copy()
        dir = np.mat([[0, -1]])


        ROT_90 = np.mat(
            [[0, 1],
            [-1, 0]]
        )

        old_trav: dict[tuple[int, int], set[tuple[int, int]]] = {}

        while m.in_bounds(*m.guard):
            if (*m.guard,) not in old_trav.keys():
                old_trav[(*m.guard,)] = {(*np.asarray(dir)[0],)}
            elif (*np.asarray(dir)[0],) in old_trav[(*m.guard,)]:
                return True
            else:
                old_trav[(*m.guard,)].add((*np.asarray(dir)[0],))


            new_pos = m.guard.copy()

            new_pos[0] += dir[0, 0]
            new_pos[1] += dir[0, 1]

            if (*new_pos,) in m.obstacles:
                dir *= ROT_90
                continue

            m.guard = new_pos

        return False

    poses = get_traveled_poses()

    result = 0

    for i,pos in enumerate(poses, start=1):
        m.obstacles.add(pos)
        print(f"{i} / {len(poses)}", end='\r')
        if is_looping(orig_pos):
            result += 1
        m.obstacles.remove(pos)


    return result

def main():
    with open("input.txt") as f:
        lines = f.readlines()

    m = Map(lines)
    m2 = Map(lines)

    print("Part 1:", part1(m))
    print("\nPart 2:", part2(m2))

if __name__ == "__main__":
    main()
