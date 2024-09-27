#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

bool validate_key(string key);
string get_encrypted_text(string text, string key);
bool check_char_uppercase(char letter);
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Only one argument is allowed.\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Incorrect key.\n");
        return 1;
    }

    bool is_key_correct = validate_key(argv[1]);
    if (!is_key_correct)
    {
        printf("Incorrect key2.\n");
        return 1;
    }

    string input = get_string("plaintext: ");
    printf("input %s\n", input);
    get_encrypted_text(input, argv[1]);
    return 0;
}

string get_encrypted_text(string input, string key)
{
    const char ALPHABET[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                               'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    // general approach to calc the size of an array
    // int size = sizeof(input) / sizeof(input[0]);
    // char output[size];
    char output[strlen(input) + 1];
    for (int j = 0; j < strlen(input); j++)
    {
        for (int i = 0; i < 26; i++)
        {
            bool is_char_upper = check_char_uppercase(input[j]);
            if (is_char_upper && isalpha(input[j]))
            {
                if (ALPHABET[i] == input[j])
                {
                    output[j] = toupper(key[i]);
                }
            }
            else if (!is_char_upper && isalpha(input[j]))
            {
                if (ALPHABET[i] == toupper(input[j]))
                {
                    output[j] = tolower(key[i]);
                }
            }
            else
            {
                output[j] = input[j];
            }
        }
    }
    output[strlen(input)] = '\0';
    printf("ciphertext: %s\n", output);
}

bool check_char_uppercase(char letter)
{
    if (letter == toupper(letter))
    {
        return true;
    }
    return false;
}

bool validate_key(string key)
{
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }

    for (int i = 0, len = strlen(key); i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (key[i] == key[j])
            {
                return false;
            }
        }
    }
    return true;
}