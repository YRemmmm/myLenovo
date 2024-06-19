#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to count characters in a file
int count_characters(FILE *file) {
    int count = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

// Function to count words in a file
int count_words(FILE *file) {
    int count = 0;
    char c;
    int in_word = 0;
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c) || c == ',') {
            if (in_word) {
                count++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }
    if (in_word) {
        count++;
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename> <option>\n", argv[0]);
        printf("Options:\n");
        printf("  -c  Count characters\n");
        printf("  -w  Count words\n");
        return 1;
    }

    char *filename = argv[1];
    char *option = argv[2];

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return 1;
    }

    if (strcmp(option, "-c") == 0) {
        int character_count = count_characters(file);
        printf("Character count: %d\n", character_count);
    } else if (strcmp(option, "-w") == 0) {
        int word_count = count_words(file);
        printf("Word count: %d\n", word_count);
    } else {
        printf("Invalid option\n");
        printf("Usage: %s <filename> <option>\n", argv[0]);
        printf("Options:\n");
        printf("  -c  Count characters\n");
        printf("  -w  Count words\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}
