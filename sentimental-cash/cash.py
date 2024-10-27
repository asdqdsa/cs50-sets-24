def main() -> None:
    cash: float = get_user_input()
    output: int = hand_coins(cash)
    print(f"{output}")


def get_user_input() -> float:
    cash: float = -1

    while cash < 0:
        try:
            cash = float(input("Change: "))
            if cash < 0:
                print("Cash connot be negative!")

        except ValueError:
            print("Not a number!")
    return cash


def hand_coins(input: float) -> int:
    result: int = 0

    quarters: int = int(input / 0.25)
    coins: float = round(input % 0.25, 2)

    dimes: int = int(coins / 0.10)
    coins = round(coins % 0.10, 2)

    nickels: int = int(coins / 0.05)
    coins = round(coins % 0.05, 2)

    pennies = coins / 0.01

    result = int(quarters + dimes + nickels + pennies)
    return result


main()
