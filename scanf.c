#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_int (const char *prompt);

int main(void)
{
    int number = get_int ("Give a number: ");

    printf ("The number is %i\n", number);

    return EXIT_SUCCESS;
}

// My own safe implementation to get integer from user 
int get_int (const char *prompt)
{
    int number_of_invalid_prompts = 0;

    char input;

    int size;
    int index;

    char *buffer = NULL;
    char *newPointer = NULL;

    while (number_of_invalid_prompts < 10)
    {
        bool is_invalid = false;

        size = 1;
        index = 0;

        printf ("%s", prompt);

        // realloc is used instead of malloc or calloc
        // realloc(NULL, 1) is the same as malloc(1)
        newPointer = realloc(buffer, 1 * sizeof(char));

        if (newPointer == NULL)
        {
            // Memory reallocation failed
            printf ("Memory cannot be reallocated!\n");

            // Free old memory
            free(buffer);

            buffer = NULL;
            newPointer = NULL;

            return 0;
        }
        
        // // Reallocation succeeded
        buffer = newPointer;

        while ((input = fgetc (stdin)) != '\n' && size < 40)
        {
            // Save the inputted character
            buffer[index++] = input;
        
            size++;

            // Extend memory with one byte for the next input read
            newPointer = realloc(buffer, size * sizeof(char));

            if (newPointer == NULL)
            {
                // Memory reallocation failed
                printf ("Memory cannot be reallocated!\n");

                // Free old memory
                free(buffer);

                buffer = NULL;
                newPointer = NULL;

                return 0;
            }
            
            // // Reallocation succeeded
            buffer = newPointer;
        }

        // Close string buffer with nul
        buffer[size - 1] = '\0';

        // Check if string contains just digits, else the input is invalid
        for (int i = 0; i < size - 1; i++)
        {
            if (!isdigit(buffer[i]))
            {
                is_invalid = true;
                break;
            }
        }

        // If there is no any input or input is invalid try again
        if (is_invalid || buffer[0] == '\0')
        {
            printf ("Invalid input!\n");
            number_of_invalid_prompts++;
            
            // Reset character count

            continue;
        }

        // Convert string to number
        int number = atoi(buffer);

        // free the allocated memory
        free(buffer);
        buffer = NULL;

        return number;
    }

    printf ("Too much invalid input! Program stopped!\n");

    free(buffer);

    buffer = NULL;

    return 0;
}