"""
Provides `aoc_run` function which handles all necessary tasks for obtaining input and testing for a given day

Interfaces with an implementation of AOCBase
"""

from typing import Any, Type
from .get_input import get_input
from termcolor import colored

__all__ = ["aoc_run", "AOCBase"]


class AOCBase:
    def process_input(self, raw_input: str) -> Any:
        return raw_input

    def part1(self, _in: Any) -> Any:
        raise NotImplementedError(f"not yet implemented for '{type(self).__name__}'")

    def part2(self, _in: Any) -> Any:
        raise NotImplementedError(f"not yet implemented for '{type(self).__name__}'")


def _print_res_table(header: str, fields: dict[str, str | None]) -> None:
    print(header, str("-") * len(header), sep="\n")

    for name, res in fields.items():
        if res is None:
            res_str = colored("INCOMPLETE", "red")
        else:
            res_str = colored(str(res), "green")

        print(f"{name}: {res_str}")


def aoc_run(year: int, day: int, ImplCls: Type[AOCBase]) -> None:
    input_result = get_input(year=year, day=day)

    impl = ImplCls()

    print(colored(f"Running Advent of Code implementation for Day {day} of {year}", "blue"))
    print(colored(f"Using implementation class '{ImplCls.__name__}'", "blue"))
    print(colored("Input", "blue"), colored("was", "green") if input_result.was_cached else colored("was not", "red"), colored("cached", "blue"))
    print()

    sample_res_pt1 = None
    full_res_pt1 = None
    sample_res_pt2 = None
    full_res_pt2 = None

    proced_sample_in = impl.process_input(input_result.sample_input)
    proced_full_in = impl.process_input(input_result.full_input)

    try:
        sample_res_pt1 = impl.part1(proced_sample_in)
        full_res_pt1 = impl.part1(proced_full_in)
    except Exception as e:
        print("Part 1 failed with exception:", colored(str(e), "red"))


    try:
        sample_res_pt2 = impl.part2(proced_sample_in)
        full_res_pt2 = impl.part2(proced_full_in)
    except Exception as e:
        print("Part 2 failed with exception:", colored(str(e), "red"))

    print()
    _print_res_table("Part 1", {"Sample": sample_res_pt1, "Full": full_res_pt1})
    print()
    _print_res_table("Part 2", {"Sample": sample_res_pt2, "Full": full_res_pt2})
