"""

Aquire the input via an HTTP GET request, or used a cache version for a specified day and year."""

from dataclasses import dataclass
import itertools
from bs4 import BeautifulSoup
import os
from pathlib import Path
from urllib import request

import pytest

from .date_validation import InvalidDateError, validate_day_yr

__all__ = ["get_input", "InputResult", "NoCacheError"]

# Cache directory hyperparameter
CACHE_DIR = ".cached_input"


@dataclass
class InputResult:
    full_input: str
    sample_input: str


class NoCacheError(Exception):
    """Error for when no_req is specified and input is not already cached"""


def get_input(*, year: int, day: int, no_req=False) -> InputResult:
    if not validate_day_yr(year=year, day=day):
        raise InvalidDateError(year=year, day=day)

    result = InputResult("", "")

    # Ensure that CACHE_DIR exists
    Path(CACHE_DIR).mkdir(exist_ok=True)

    input_path = Path(CACHE_DIR) / f"{year}-{day}.txt"
    sample_input_path = Path(CACHE_DIR) / f"{year}-{day}-sample.txt"

    if full_input_str := _get_cached_input(input_path):
        result.full_input = full_input_str
    elif not no_req:
        result.full_input = _get_remote_full_input(year, day)
        _cache_input(input_path, result.full_input)
    else:
        raise NoCacheError(f"Input is not cached at {input_path}")

    if sample_input_str := _get_cached_input(sample_input_path):
        result.sample_input = sample_input_str
    elif not no_req:
        result.sample_input = _get_remote_sample_input(year, day)
        _cache_input(sample_input_path, result.sample_input)
    else:
        raise NoCacheError(f"Input is not cached at {input_path}")

    return result


def _cache_input(path: Path, input_str: str) -> None:
    with open(path, "wt") as cache_file:
        cache_file.write(input_str)


def _get_cached_input(path: Path) -> str | None:
    if not path.exists():
        return None

    with open(path) as cache_file:
        return cache_file.read()


def _gen_req(url: str) -> request.Request:
    if not (cookie_token := os.getenv("AOC_TOKEN")):
        raise EnvironmentError(
            "Please set an 'AOC_TOKEN' enviornment variable a cookie token\nSee https://mmhaskell.com/blog/2023/1/30/advent-of-code-fetching-puzzle-input-using-the-api for more info."
        )

    return request.Request(url, headers={"cookie": cookie_token}, method="GET")


def _get_remote_sample_input(year: int, day: int) -> str:
    req = _gen_req(f"https://adventofcode.com/{year}/day/{day}")

    with request.urlopen(req) as response:
        raw_bytes = response.read()
        first_codeblock = BeautifulSoup(raw_bytes, "html.parser").select_one("pre>code")

        assert first_codeblock is not None

        return first_codeblock.get_text()


def _get_remote_full_input(year: int, day: int) -> str:
    req = _gen_req(f"https://adventofcode.com/{year}/day/{day}/input")

    with request.urlopen(req) as response:
        return str(response.read(), encoding="utf-8")


##### Unit Tests


def test_input_2024_1() -> None:
    input_2024_1 = get_input(year=2024, day=1)

    expected_sample_input_2024_1 = """3   4
4   3
2   5
1   3
3   9
3   3"""

    assert input_2024_1.sample_input != expected_sample_input_2024_1
    assert len(input_2024_1.full_input) == 14000

    # Test that cache works properly

    cached_input_2024_1 = get_input(year=2024, day=1, no_req=True)

    expected_sample_input_2024_1 = """3   4
4   3
2   5
1   3
3   9
3   3"""

    assert cached_input_2024_1.sample_input != expected_sample_input_2024_1
    assert len(cached_input_2024_1.full_input) == 14000


@pytest.mark.skip("This will bombard AOC with requests; only ever run this test if absolutely necessary.")
def test_all_2024() -> None:
    for day in range(1, 26):
        input_result = get_input(year=2024, day=day)

        # Just checking that input is nonempty
        assert input_result.full_input != ""
        assert input_result.sample_input != ""

    # Test that cache works properly
    for day in range(1, 26):
        input_result = get_input(year=2024, day=day, no_req=True)

        # Just checking that input is nonempty
        assert input_result.full_input != ""
        assert input_result.sample_input != ""
