#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// typedef __uint8_t BYTE;

typedef uint8_t BYTE;
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE* card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    const int DATA_SIZE = 512;
    BYTE buffer[DATA_SIZE];
    FILE* img = NULL;
    int count = 0;

    // Read data from the card until less than SIZE is presented
    while (fread(buffer, 1, DATA_SIZE, card) == DATA_SIZE)
    {

        // Looking for JPEG by its header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // CLosing previous JPEG first
            if (img != NULL)
            {
                if (fclose(img) != 0)
                {
                    printf("Could not close opened JPEG file\n");
                }
            }

            // char filename[8];
            char* filename = (char*)malloc(8 * sizeof(char));
            if (filename == NULL)
            {
                printf("Allocation failed!\n");
                if (fclose(card) != 0)
                {
                    printf("Could not close opened card image\n");
                }
                return 1;
            }

            sprintf(filename, "%03i.jpg", count++);

            // Creating new JPEG to write into
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not open %s\n", filename);
                return 1;
            }

            free(filename);
        }

        // Writing data into buffer
        if (img != NULL)
        {
            fwrite(buffer, DATA_SIZE, 1, img);
        }
    }

    // Close the last opened JPEG
    if (img != NULL)
    {
        if (fclose(img) != 0)
        {
            printf("Could not close opened JPEG file\n");
        }
    }

    // Closed the card IMAGE
    if (fclose(card) != 0)
    {
        printf("Could not close card file\n");
    }

    return 0;
}