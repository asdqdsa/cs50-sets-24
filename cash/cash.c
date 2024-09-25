#include <cs50.h>
#include <stdio.h>

void handCoins (int change);

int
main (void)
{
    int change;
    do
        {
            change = get_int ("What is your change? ");
        }
    while (change < 0);

    handCoins (change);
    return 0;
}

void
handCoins (int change)
{
    int result = 0;

    int quarters = change / 25;
    int coins = change % 25;

    int dimes = coins / 10;
    coins = coins % 10;

    int nickels = coins / 5;
    coins = coins % 5;

    int pennies = coins / 1;

    result = quarters + dimes + nickels + pennies;

    printf ("%i\n", result);
}
