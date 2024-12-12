def part1(grid: list[list[int]]) -> int:
    scores = [[set() for _ in grid[0]] for _ in grid]

    def dfs(i: int, j: int, S, last = 10):
        if i < 0 or i >= len(grid):
            return
        if j < 0 or j >= len(grid[0]):
            return

        if grid[i][j] != last - 1:
            return

        scores[i][j].add(S)

        dfs(i - 1, j, S, last - 1)
        dfs(i + 1, j, S, last - 1)
        dfs(i, j - 1, S, last - 1)
        dfs(i, j + 1, S, last - 1)

    for i,row in enumerate(grid):
        for j,n in enumerate(row):
            if n == 9:
                dfs(i, j, (i, j))

    result = 0
    for i,row in enumerate(grid):
        for j,n in enumerate(row):
            if n == 0:
                result += len(scores[i][j])

    return result

def part2(grid: list[list[int]]) -> int:
    scores = [[0 for _ in grid[0]] for _ in grid]

    def dfs(i: int, j: int, last = 10):
        if i < 0 or i >= len(grid):
            return
        if j < 0 or j >= len(grid[0]):
            return

        if grid[i][j] != last - 1:
            return

        scores[i][j] += 1

        dfs(i - 1, j, last - 1)
        dfs(i + 1, j, last - 1)
        dfs(i, j - 1, last - 1)
        dfs(i, j + 1, last - 1)

    for i,row in enumerate(grid):
        for j,n in enumerate(row):
            if n == 9:
                dfs(i, j)

    result = 0
    for i,row in enumerate(grid):
        for j,n in enumerate(row):
            if n == 0:
                result += scores[i][j]

    return result

def main():
    with open("input.txt") as f:
        grid = [list(map(int, line[:-1])) for line in f.readlines()]

    print("Part 1:", part1(grid))
    print("Part 2:", part2(grid))

if __name__ == "__main__":
    main()
