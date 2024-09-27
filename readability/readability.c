#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

string get_input_text(void);
int count_words(string);
int count_sentences(string);
int count_letters(string);
void get_rating(float index);

int main(void)
{
    string text = get_input_text();
    float words = (float)count_words(text);
    float sentences = (float)count_sentences(text);
    float letters = (float)count_letters(text);
    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    printf("%f \n", index);
    get_rating(index);
    return 0;
    // 12.5832 - 1.184 - 15.8
    // 22.47 - 0.21142857
    // 31.5741176 1.243697487
    // 31.5756 1.2432
}

void get_rating(float index)
{
    int round_index = round(index);
    if (round_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (round_index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
        printf("Grade %i\n", (int)round_index);
}
int count_letters(string input)
{
    int letter_count = 0;
    for (int i = 0, len = strlen(input); i < len; i++)
    {
        if (input[i] != ' ' && input[i] != '.' && input[i] != '?' && input[i] != '!' && input[i] != ',' &&
            input[i] != ';')
        {
            letter_count += 1;
        }
    }
    printf("%i letters count\n", letter_count);
    return letter_count;
}

int count_words(string input)
{
    int word_count = 1;
    for (int i = 0, len = strlen(input); i < len; i++)
    {
        if (input[i] == ' ' || input[i] == '\'')
        {
            word_count += 1;
        }
    }
    printf("%i  words count\n", word_count);
    return word_count;
}

int count_sentences(string input)
{
    int sentence_count = 0;
    for (int i = 0, len = strlen(input); i < len; i++)
    {
        if (input[i] == '!' || input[i] == '.' || input[i] == '?')
        {
            sentence_count += 1;
        }
    }
    printf("%i sentences count\n", sentence_count);
    return sentence_count;
}

string get_input_text(void)
{
    string str = "It was a bright cold day in April, and the clocks were striking "
                 "thirteen. Winston Smith, his chin nuzzled into his breast in an "
                 "effort to escape the vile wind, slipped quickly through the glass "
                 "doors of Victory Mansions, though not quickly enough to prevent a "
                 "swirl of gritty dust from entering along with him.";
    string input;
    do
    {
        input = get_string("Text: ");
    } while (strlen(input) < 1);
    return input;
    // return str;
}
