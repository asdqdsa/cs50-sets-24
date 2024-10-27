def main() -> None:
    count: int = 0

    # while count < 1 or count > 8:
    while not (0 < count < 9):
        try:
            count = int(input("How many rows do you want me to build? "))
            if count < 1 or count > 8:
                print("Please provide a positive integer between 1 and 8.")
        except ValueError:
            print("Not a number!")

    build_pyramid(count)


def build_pyramid(n: int) -> None:
    for i in range(n):
        print(" " * (n - i - 1), end="")
        print("#" * (i + 1))


main()
