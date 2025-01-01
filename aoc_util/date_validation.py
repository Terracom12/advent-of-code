import pytest
from datetime import date

__all__ = ["InvalidDateError", "validate_day_yr"]


class InvalidDateError(Exception):
    """Exception for an invalid day for AOC"""

    def __init__(self, *args: object, year: int, day: int) -> None:
        super().__init__(*args)
        self._year = year
        self._day = day

    def __str__(self) -> str:
        return f"Invalid Advent of Code date: year = {self._year} | day = {self._day}"


def validate_day_yr(*, year: int, day: int) -> bool:
    """Check whether day and year are valid to submit for AOC"""

    if day > 25 or day < 1:
        return False

    if year < 2015 or year > date.today().year:
        return False

    return True


##### Unit Tests


def test_invalid_days() -> None:
    assert validate_day_yr(year=2024, day=0) is False
    assert validate_day_yr(year=2014, day=1) is False
    assert validate_day_yr(year=2015, day=26) is False
    assert validate_day_yr(year=date.today().year + 1, day=1) is False


def test_valid_days() -> None:
    assert validate_day_yr(year=2024, day=1) is True
    assert validate_day_yr(year=2024, day=25) is True
    assert validate_day_yr(year=2024, day=10) is True

    assert validate_day_yr(year=2015, day=2) is True
    assert validate_day_yr(year=2020, day=18) is True


def test_exception() -> None:
    with pytest.raises(InvalidDateError, match="Invalid Advent of Code date"):
        raise InvalidDateError(year=2000, day=5)
