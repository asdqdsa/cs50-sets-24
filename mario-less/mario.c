#include <cs50.h>
#include <stdio.h>

void buildPyramid (int n);

int
main (void)
{
    int rows;
    do
        {
            rows = get_int ("How many rows do you want me to build? ");
        }
    while (rows < 1);

    buildPyramid (rows);
    // return 0;
}

void
buildPyramid (int n)
{
    for (int i = 0; i < n; i++)
        {
            int spaceCount = n - i - 1;
            while (spaceCount >= 1)
                {
                    spaceCount -= 1;
                    printf (" ");
                }

            for (int j = 0; j < i + 1; j++)
                {
                    printf ("#");
                }

            printf ("\n");
        }
}
