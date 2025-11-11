#include <stdio.h>
#include <string.h>
#include <math.h>

#define d 256 // number of characters in input alphabet (ASCII)
#define q 101 // a prime number used for modulus to reduce hash collisions

void rabinKarp(char text[], char pattern[]) {
    int M = strlen(pattern);
    int N = strlen(text);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text
    int h = 1;

    // The value of h = pow(d, M-1) % q
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate hash value of pattern and first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over the text
    for (i = 0; i <= N - M; i++) {
        // Check the hash values
        if (p == t) {
            // If hash matches, then check character by character
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == M)
                printf("Pattern found at index %d\n", i);
        }

        // Calculate hash value for next window
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;

            // We might get negative t, convert it to positive
            if (t < 0)
                t = (t + q);
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

    printf("\n--- Rabin-Karp String Matching ---\n");
    rabinKarp(text, pattern);

    return 0;
}