

from collections import Counter


with open("input.txt") as f:
    lines = f.readlines()

    li = list(map(lambda l: int(l[:l.find(" ")]), lines))
    c = Counter(map(lambda l: int(l[l.find(" "):]), lines))

    print(sum(map(lambda t: t * c[t], li)))

