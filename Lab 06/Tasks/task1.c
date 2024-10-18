#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAX_TEXT_LENGTH 1000

// Function to count words in a string
int count_words(const char *text) {
    int count = 0;
    char *token;
    char *text_copy = strdup(text);  // Duplicate text to avoid modifying the original
    token = strtok(text_copy, " \t\n");
    while (token != NULL) {
        count++;
        token = strtok(NULL, " \t\n");
    }
    free(text_copy);
    return count;
}

// Function to count sentences in a string
int count_sentences(const char *text) {
    int count = 0;
    for (const char *ptr = text; *ptr; ptr++) {
        if (*ptr == '.' || *ptr == '!' || *ptr == '?') {
            count++;
        }
    }
    return count;
}

// Function to count paragraphs in a string
int count_paragraphs(const char *text) {
    int count = 0;
    const char *ptr = text;
    while (*ptr) {
        if (*ptr == '\n') {
            count++;
            while (*ptr == '\n') ptr++;  // Skip multiple newlines
        } else {
            ptr++;
        }
    }
    return count + 1;  // Count the last paragraph
}

int main() {
    const char *text = "This is a sentence. This is another one! Here is a new paragraph.\n\nThis is a new line.";
    int word_count = 0, sentence_count = 0, paragraph_count = 0;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            word_count = count_words(text);
        }
        #pragma omp section
        {
            sentence_count = count_sentences(text);
        }
        #pragma omp section
        {
            paragraph_count = count_paragraphs(text);
        }
    }

    // Print the results
    printf("Text: \"%s\"\n", text);
    printf("Word Count: %d\n", word_count);
    printf("Sentence Count: %d\n", sentence_count);
    printf("Paragraph Count: %d\n", paragraph_count);

    return 0;
}
