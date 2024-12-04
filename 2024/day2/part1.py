from itertools import pairwise

with open("input.txt") as f:
    lines = f.readlines()

    S = 0

    for l in lines:
        orig_nums = l.split(" ")

        for i in range(len(orig_nums)):
            bad = False
            nums = orig_nums.copy()
            del nums[i]
            incr = int(nums[0]) < int(nums[1])

            for p in pairwise(nums):
                p = list(map(int, p))
                if incr ^ (p[0] < p[1]):
                    bad = True
                    break
                dist = abs(p[0] - p[1])
                if dist > 3 or dist < 1:
                    bad = True
                    break

            if not bad:
                S += 1
                break

    print(S)

