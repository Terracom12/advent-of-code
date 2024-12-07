from dataclasses import dataclass

@dataclass
class Equations:
    data: dict[int, list[int]]

def eval_eqn(opnds: list[int], ops: list[str]) -> int:
    res = opnds[0]

    for n,op in zip(opnds[1:], ops):
        if op == "+":
            res += n
        elif op == "*":
            res *= n
        elif op == "||":
            res = int(str(res) + str(n))

    return res

def check_all_eqns(res: int, opnds: list[int], possible_obs: list[str]) -> bool:
    if len(opnds) == 1:
        return opnds[0] == res

    lhs = opnds.pop(0)
    rhs = opnds[0]


    for op in possible_obs:
        new_opnd = eval_eqn([lhs, rhs], [op])
        opnds[0] = new_opnd

        if check_all_eqns(res, opnds, possible_obs):
            return True

    opnds[0] = rhs
    opnds.insert(0, lhs)

    return False

def part1(eqs: Equations) -> int:
    total_calib_res = 0

    for desired_res,operands in eqs.data.items():
        if check_all_eqns(desired_res, operands, ["+", "*"]):
            total_calib_res += desired_res

    return total_calib_res

def part2(eqs: Equations) -> int:
    total_calib_res = 0

    for desired_res,operands in eqs.data.items():
        if check_all_eqns(desired_res, operands, ["+", "*", "||"]):
            total_calib_res += desired_res

    return total_calib_res

def main():
    eqs = Equations({})

    with open("input.txt") as f:
        lines = f.readlines()

    for line in lines:
        test_val, rem = line.split(": ")
        eqs.data[int(test_val)] = list(map(int, rem.split(" ")))


    print("Part 1:", part1(eqs))
    print("Part 2:", part2(eqs))

if __name__ == "__main__":
    main()
