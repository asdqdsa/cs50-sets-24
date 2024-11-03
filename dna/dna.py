import csv
import sys
from typing import Dict, Iterator, TypeAlias, List

Row: TypeAlias = Dict[str, str]
Rows: TypeAlias = List[Row]


def main():
    # TODO: Check for command-line usage
    try:
        if len(sys.argv) != 3:
            raise ValueError("Usage: provide only two arguments!")

    except ValueError as error:
        print(error)
        sys.exit(1)

    else:
        db_file_arg: str = sys.argv[1]
        seq_file_arg: str = sys.argv[2]

    # TODO: Read database file into a variable
    rows: Rows = []
    with open(db_file_arg) as db_file:
        reader: Iterator[Row] = csv.DictReader(db_file)
        for row in reader:
            rows.append(row)
    print(rows)

    # TODO: Read DNA sequence file into a variable
    with open(seq_file_arg) as seq_file:
        f_line = seq_file.readline()
        # print(f_line)

    # TODO: Find longest match of each STR in DNA sequence
    str_s: list[str] = [key for key in rows[0] if key != "name"]
    print(str_s)

    str_dict: dict[str, int] = {}
    count: int = 0
    for a_str in str_s:
        count = longest_match(f_line, a_str)
        str_dict[a_str] = count
    print(str_dict)

    # TODO: Check database for matching profiles
    for person in rows:
        found_match: bool = False

        for a_str in str_s:
            count_db: str | None = person.get(a_str)
            count_seq: int | None = str_dict.get(a_str)

            if count_db == str(count_seq):
                found_match = True
            else:
                found_match = False
                break

        if found_match:
            print(person["name"])
            break
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
