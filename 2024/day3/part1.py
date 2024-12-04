from re import finditer

with open("input.txt") as f:
    mem = "".join(f.readlines())

res = 0
for found in finditer("mul\\((\\d+),(\\d+)\\)", mem):
    res += int(found.group(1)) * int(found.group(2))

print(res)
