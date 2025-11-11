#include <stdio.h>
#include <string.h>
#include <limits.h> // For CHAR_MAX

#define NO_OF_CHARS 256 // Total number of possible characters (ASCII)

// Function to create the bad character heuristic table
void badCharHeuristic(char *pattern, int size, int badchar[NO_OF_CHARS]) {
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Fill the actual value of the last occurrence of a character
    for (i = 0; i < size; i++)
        badchar[(int)pattern[i]] = i;
}

// Boyer–Moore search function using Bad Character Heuristic
void search(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);

    int badchar[NO_OF_CHARS];

    // Preprocess the pattern
    badCharHeuristic(pattern, m, badchar);

    int s = 0; // shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j while characters of pattern and text are matching
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        // If the pattern is present at current shift
        if (j < 0) {
            printf("Pattern found at index %d\n", s);

            // Shift pattern so that next character in text aligns with the last occurrence of pattern[0]
            s += (s + m < n) ? m - badchar[(int)text[s + m]] : 1;
        } else {
            // Shift the pattern so that the bad character in text aligns with its last occurrence in pattern
            int shift = j - badchar[(int)text[s + j]];
            s += (shift > 1) ? shift : 1; // ensure at least one shift
        }
    }
}

int main() {
    char text[100], pattern[100];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // remove newline

    printf("Enter the pattern to search: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = 0; // remove newline

    printf("\n--- Boyer-Moore String Matching (Bad Character Rule) ---\n");
    search(text, pattern);

    return 0;
}