#include <stdio.h>
#include <string.h>

// Function to compute the Longest Prefix Suffix (LPS) array
void computeLPSArray(char* pattern, int M, int* lps) {
    int length = 0;  // length of the previous longest prefix suffix
    lps[0] = 0;      // lps[0] is always 0

    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                // Consider the previous longest prefix
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search Algorithm
void KMPSearch(char* pattern, char* text) {
    int M = strlen(pattern);
    int N = strlen(text);

    int lps[M];

    // Preprocess the pattern to get lps array
    computeLPSArray(pattern, M, lps);

    int i = 0; // index for text[]
    int j = 0; // index for pattern[]
    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1]; // Continue searching for next possible match
        }

        // Mismatch after j matches
        else if (i < N && pattern[j] != text[i]) {
            // Do not match lps[0..lps[j-1]] characters, they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
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

    printf("\n--- Knuth-Morris-Pratt (KMP) String Matching ---\n");
    KMPSearch(pattern, text);

    return 0;
}