from aoc_util import AOCBase, aoc_run
from collections import deque

class Day12(AOCBase):
    def process_input(self, raw_input: str) -> list[list[str]]:
        grid = [[*line] for line in raw_input.split("\n")]

        grid = grid[:-1]

        return grid

    def part1(self, grid: list[list[str]]) -> int:
        visited = [[False] * len(grid[0]) for _ in grid]

        def dfs(i: int, j: int, plot: str) -> tuple[int, int]:
            """
            Returns:
                (area, perimeter)
            """

            # Out of bounds or wrong plot type
            #  -> add 1 more perimeter
            if i not in range(len(grid)) or j not in range(len(grid[0])):
                return (0, 1)

            if grid[i][j] != plot:
                return (0, 1)

            # Visited already of same plot -> skip
            if visited[i][j]:
                return (0, 0)

            visited[i][j] = True

            # Correct plot type -> add 1 to area
            res = (1, 0)

            for di,dj in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                new = dfs(i + di, j + dj, plot)
                res = (res[0] + new[0], res[1] + new[1])

            return res

        result = 0

        for i,row in enumerate(grid):
            for j,plot in enumerate(row):
                if visited[i][j]:
                    continue

                area, perimeter = dfs(i, j, plot)

                result += area * perimeter

        return result

    def part2(self, grid: list[list[str]]) -> int:
        visited = [[False] * len(grid[0]) for _ in grid]
        # i, j, dir_i, dir_j
        edge_cache: set[tuple[int, int, int, int]] = set()

        to_visit: deque[tuple[int, int, tuple[int, int]]] = deque()

        def bfs_helper() -> tuple[bool, int, int]:
            """
            Returns:
                (should_continue, area, num_edges))
            """

            if len(to_visit) == 0:
                edge_cache.clear()
                return (False, 0, 0)

            i, j, last = to_visit.pop()

            # Out of bounds or wrong plot type
            #  -> add 1 more perimeter
            if i not in range(len(grid)) or j not in range(len(grid[0])) or grid[i][j] != plot:
                di,dj = i - last[0], j - last[1]

                assert last[0] != -1 and last[1] != -1

                edge_cache.add((i, j, di, dj))

                # Opposite directions (if left/right try up and down, and vice versa)
                if di == 0 and ((i - 1, j, di, dj) in edge_cache or (i + 1, j, di, dj) in edge_cache):
                    return (True, 0, 0)
                if dj == 0 and ((i, j - 1, di, dj) in edge_cache or (i, j + 1, di, dj) in edge_cache):
                    return (True, 0, 0)

                # Not part of another edge, add 1 to num edges
                return (True, 0, 1)

            # Visited already of same plot -> skip
            if visited[i][j]:
                return (True, 0, 0)

            visited[i][j] = True

            # Correct plot type -> add 1 to area

            for di,dj in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                to_visit.appendleft((i + di, j + dj, (i, j)))

            return (True, 1, 0)

        result = 0

        for i,row in enumerate(grid):
            for j,plot in enumerate(row):
                if visited[i][j]:
                    continue

                tot_area = 0
                tot_edges = 0
                to_visit.appendleft((i, j, (-1, -1)))
                while (ret := bfs_helper()) and ret[0] is True:
                    _, area, num_edges = ret
                    tot_area += area
                    tot_edges += num_edges

                result += tot_edges * tot_area
                # print(f"For '{plot}' @ {i}, {j} -- {area=} {num_edges=}", edge_cache)
                # print(list(filter(lambda t: t[0] == -1, edge_cache)))

        return result

if __name__ == "__main__":
    aoc_run(2024, 12, Day12)
