#include <cs50.h>
#include <stdio.h>

int
main (void)
{
    string name = get_string ("Your String?: ");

    int n = 0;
    while (name[n] != '\0')
        {
            n++;
        }

    int total_bytes = sizeof (name);

    printf ("%c\n ", ('b' - 'A'));
    return 1;
}