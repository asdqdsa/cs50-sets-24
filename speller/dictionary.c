// Implements a dictionary's functionality

// #include <cs50.h>
#include <ctype.h>
// #include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
} node;

// global pointer for check size function to return
int word_count;
// Prototype
bool search_linked_list(const char* word, node* head);

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
// Prime Number for Even Distribution in custom hash func
const unsigned int PRIME = 23;

// Hash table
node* table[N];

bool search_linked_list(const char* word, node* head)
{
    node* curr = head;

    while (curr != NULL)
    {
        if (strcasecmp(curr->word, word) == 0)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Returns true if word is in dictionary, else false
bool check(const char* word)
{
    // find word in hash Table.
    int hash_index = hash(word);
    bool is_word_in_dict = search_linked_list(word, table[hash_index]);
    return is_word_in_dict;
}

// Hashes word to a number
unsigned int hash(const char* word)
{
    unsigned int hash_index = 0;
    while (true)
    {
        // ASCII value
        int character = toupper(*word);
        if (character == '\0')
            break;

        // Calculating a simple hash summ utilizing Prime number
        hash_index = hash_index * PRIME + character;
        // Increment pointer to cycle through the letters
        word++;
    }
    // Reducing value to the size of hash table
    return hash_index % N;
}

// while (fread(&c, sizeof(char), 1, dictionary))

// Loads dictionary into memory, returning true if successful, else false
bool load(const char* dictionary)
{
    // Open dict file
    FILE* ptr_source = fopen(dictionary, "r");
    if (ptr_source == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    word_count = 0;

    char word[LENGTH + 1];

    // Read strings one at a time from a file
    while (fscanf(ptr_source, "%s", word) != EOF)
    {
        unsigned int hash_index;
        // Allocate memory for a node
        node* ptr_node = (node*)malloc(sizeof(node));
        if (ptr_node == NULL)
        {
            fclose(ptr_source);
            return false;
        }

        // Copy word to node.word
        strcpy(ptr_node->word, word);
        ptr_node->next = NULL;

        // Get hash value of the word
        hash_index = hash(word);

        // Inserting new node by switching it with the curr head
        ptr_node->next = table[hash_index];
        table[hash_index] = ptr_node;

        // Increment word count
        word_count++;
    }

    fclose(ptr_source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (unsigned int i = 0; i < N; i++)
    {
        node* curr = table[i];
        node* temp;
        while (curr != NULL)
        {
            temp = curr->next;
            free(curr);
            curr = temp;
        }
        if (curr == NULL && i == N - 1)
        {
            return true;
        }
    }
    return true;
}
