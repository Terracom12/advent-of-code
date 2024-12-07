from collections import defaultdict
from dataclasses import dataclass

with open("input.txt") as f:
    rule_lines = []
    prod_lines = []

    while l := f.readline():
        if l == '\n':
            break
        rule_lines.append(l)

    while l := f.readline():
        prod_lines.append(l)


rules = defaultdict(list)

for r in rule_lines:
    lhs, rhs = r.split('|')
    rules[int(rhs)] += [int(lhs)]

result = 0

@dataclass
class Num:
    n: int
    def __lt__(self, rhs):
        return self.n in rules[rhs.n]


for pl in prod_lines:
    nums = list(map(Num, map(int, pl.split(','))))

    snums = sorted(nums)

    if snums != nums:
        result += snums[len(nums) // 2].n


print(result)
