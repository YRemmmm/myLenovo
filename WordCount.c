#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to count the number of characters in a given file.
int count_characters(FILE *file) {
    int count = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

// Function to count the number of words in a given file. Words are considered
// as sequences of non-whitespace characters separated by whitespace or commas.
int count_words(FILE *file) {
    int count = 0;
    char c;
    int in_word = 0; // Flag to indicate if we're currently inside a word
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c) || c == ',') { // If a delimiter is found
            if (in_word) {           // And we were in a word
                count++;              // Increment word count
                in_word = 0;          // Reset the in-word flag
            }
        } else {
            in_word = 1;             // Set the in-word flag
        }
    }
    // If the file ends with a word, increment the word count
    if (in_word) {
        count++;
    }
    return count;
}

int main(int argc, char *argv[]) {
    // Check for correct command-line argument usage
    if (argc != 3) {
        printf("Usage: %s <filename> <option>\n", argv[0]);
        printf("Options:\n");
        printf("  -c  Count characters\n");
        printf("  -w  Count words\n");
        return 1;
    }

    char *filename = argv[1]; // Get filename from arguments
    char *option = argv[2];   // Get operation option

    // Attempt to open the specified file in read mode
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file"); // Print error message if file fails to open
        return 1;
    }

    // Based on the chosen option, perform the respective counting operation
    if (strcmp(option, "-c") == 0) {
        int character_count = count_characters(file);
        printf("Character count: %d\n", character_count);
    } else if (strcmp(option, "-w") == 0) {
        int word_count = count_words(file);
        printf("Word count: %d\n", word_count);
    } else {
        // If the provided option is invalid, inform the user and exit
        printf("Invalid option\n");
        printf("Usage: %s <filename> <option>\n", argv[0]);
        printf("Options:\n");
        printf("  -c  Count characters\n");
        printf("  -w  Count words\n");
        fclose(file); // Close the file before exiting
        return 1;
    }

    // Close the file after processing
    fclose(file);
    return 0;
}
