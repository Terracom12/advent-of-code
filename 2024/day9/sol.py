import bisect

def part1(nums: list[int]) -> int:
    def to_id(i: int) -> int:
        return (i // 2)

    checksum = 0

    block_pos = 0
    left = 0
    right = len(nums) - 1

    while left <= right:
        # File block for left
        if left % 2 == 0:
            # Empty file block
            if nums[left] == 0:
                left += 1
                continue
            # Decrease sz of file block
            nums[left] -= 1
            checksum += block_pos * to_id(left)
            # print(to_id(left), end="")

        # Empty block for left -> file block from right
        elif left % 2 == 1:
            # Empty file block on right
            if nums[right] == 0:
                right -= 2
                continue
            # Finished EMPTY block on left
            if nums[left] == 0:
                left += 1
                continue

            # Decrease sz of file block AND empty block
            nums[right] -= 1
            nums[left] -= 1
            checksum += block_pos * to_id(right)
            # print(to_id(right), end="")

        # Next file block
        block_pos += 1

    return checksum

def part2(nums: list[int]) -> int:
    def to_id(i: int) -> int:
        return (i // 2)

    checksum = 0

    # (block pos, block sz)
    open_blocks: list[tuple[int, int]] = []

    # Obtain all open blocks
    block_pos = 0
    for file_sz,free_sz in zip(nums[::2], nums[1::2]):
        block_pos += file_sz

        if free_sz > 0:
            open_blocks.append((block_pos, free_sz))

        block_pos += free_sz

    block_pos += nums[-1]

    # Sort by incr. block pos
    open_blocks.sort(key=lambda t: t[0])
    # print(open_blocks)

    print_res = ["." for _ in range(block_pos)]

    # print(block_pos)
    for i,block_sz in zip(range(len(nums) - 1, -1, -1), nums[::-1]):
        id = to_id(i)

        if block_sz == 0:
            continue

        # FILE type block
        if i % 2 == 0:
            # Try to take empty block in front
            open_idx = 0
            while open_idx < len(open_blocks) and open_blocks[open_idx][1] < block_sz:
                open_idx += 1

            # Block not found
            if open_idx == len(open_blocks):
                while block_sz > 0:
                    block_pos -= 1
                    block_sz -= 1
                    # print_res[block_pos] = str(id)
                    checksum += id * block_pos
            else:
                new_pos, free_sz = open_blocks[open_idx]

                if free_sz > block_sz:
                    open_blocks[open_idx] = (new_pos + block_sz, free_sz - block_sz)
                else:
                    del open_blocks[open_idx]

                while block_sz > 0:
                    # print_res[new_pos] = str(id)
                    checksum += id * new_pos
                    new_pos += 1
                    block_sz -= 1
                    block_pos -= 1


        # EMPTY type block
        elif i % 2 == 1:
            block_pos -= block_sz

        # print("".join(print_res))
        # print(block_pos,open_blocks)

    return checksum

def main():
    with open("input.txt") as f:
        nums = [int(n) for n in f.readline()[:-1]]

        if len(nums) % 2 == 0:
            print("HERE")
            del nums[-1]

    print("Part 1:", part1(nums.copy()))
    print("Part 2:", part2(nums))

if __name__ == "__main__":
    main()
