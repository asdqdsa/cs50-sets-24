#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string get_input_word (int player_num);
int get_char_score (char letter);
int get_word_score (string word);
string get_result (int score1, int score2);
int
main (void)
{
    string word_p1 = get_input_word (1);
    string word_p2 = get_input_word (2);
    int word1_score = get_word_score (word_p1);
    int word2_score = get_word_score (word_p2);
    string result = get_result (word1_score, word2_score);

    printf ("%s\n", result);
}

string
get_result (int score1, int score2)
{
    if (score1 > score2)
        {
            return "Player 1 wins!";
        }
    else if (score1 < score2)
        {
            return "Player 2 wins!";
        }
    return "Tie!";
}

int
get_char_score (char letter)
{
    const int score[26] = { 1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                            1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };
    const char letters[26]
        = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    for (int i = 0; i < 26; i++)
        {
            if (letters[i] == toupper (letter))
                {
                    return score[i];
                }
        }
    return 0;
}

int
get_word_score (string word)
{
    int total = 0;
    for (int i = 0, len = strlen (word); i < len; i++)
        {
            total += get_char_score (word[i]);
        }
    return total;
}
string
get_input_word (int player_num)
{
    string input;
    do
        {
            input = get_string ("Player %i: ", player_num);
        }
    while (strlen (input) < 1);
    return input;
}
