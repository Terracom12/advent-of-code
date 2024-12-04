from re import finditer

with open("input.txt") as f:
    mem = "".join(f.readlines())

enables = [(m.end(), True) for m in finditer("do\\(\\)", mem)]
enables += [(m.end(), False) for m in finditer("don't\\(\\)", mem)]
enables.sort(key=lambda v: -v[0])

res = 0
state = True
for found in finditer("mul\\((\\d+),(\\d+)\\)", mem):
    while enables and (last_enable := enables[-1]) and last_enable[0] < found.end():
        state = last_enable[1]
        enables.pop()

    if state:
        res += int(found.group(1)) * int(found.group(2))

print(res)
