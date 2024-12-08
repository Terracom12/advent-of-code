from collections import defaultdict

def in_range(x: int, y: int, li2d: list[str]) -> bool:
    if x < 0 or x >= len(li2d[0]):
        return False
    if y < 0 or y >= len(li2d):
        return False

    return True

def part1(grid: list[str]) -> int:
    annodes = set()
    antennae = defaultdict(list)

    for y,row in enumerate(grid):
        for x,c in enumerate(row):
            if not c.isalnum():
                continue

            for xp,yp in antennae[c]:
                dx,dy = x - xp, y - yp

                if in_range(xp - dx, yp - dy, grid):
                    annodes.add((xp - dx, yp - dy))
                if in_range(x + dx, y + dy, grid):
                    annodes.add((x + dx, y + dy))

            antennae[c].append((x, y))


    return len(annodes)

def part2(grid: list[str]) -> int:
    annodes = set()
    antennae = defaultdict(list)

    for y,row in enumerate(grid):
        for x,c in enumerate(row):
            if not c.isalnum():
                continue

            for xp,yp in antennae[c]:
                dx,dy = x - xp, y - yp

                while in_range(xp, yp, grid):
                    annodes.add((xp, yp))
                    xp -= dx
                    yp -= dy
                nx,ny = x,y
                while in_range(nx, ny, grid):
                    annodes.add((nx, ny))
                    nx += dx
                    ny += dy

            antennae[c].append((x, y))


    return len(annodes)

def main():
    with open("input.txt") as f:
        lines = [line[:-1] for line in f.readlines()]


    print("Part 1:", part1(lines))
    print("Part 2:", part2(lines))

if __name__ == "__main__":
    main()
