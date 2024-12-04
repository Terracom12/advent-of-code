with open("input.txt") as f:
    lines = f.readlines()

    l1 = sorted(list(map(lambda l: int(l[:l.find(" ")]), lines)))
    l2 = sorted(list(map(lambda l: int(l[l.find(" "):]), lines)))

    print(sum(map(lambda t: abs(t[0] - t[1]), zip(l1, l2))))

