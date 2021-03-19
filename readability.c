#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_chars();
int count_sentences();
int count_words();

int main(void)
{
    // Request text from user
    string text = get_string("Text: ");

    // Count the number of chars in string
    int chars = count_chars(text);

    // Check each character for a space (counts word)
    int words = count_words(text);

    // Check each character for period (counts sentences)
    int sentences = count_sentences(text);

    // Average letters per 100 words
    float L = chars * 100.0 / words;


    // Average sentences per 100 words
    float S = sentences * 100.0 / words;

    // Calculate Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Round up/down the index to nearest int
    index = round(index);

    // Print under 1 grade or over 16 grade, if applies
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}

int count_chars(string word)
{
    int chars = 0;

    // Count all alphabetic characters
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (word[i] >= 65 && word[i] <= 90)
        {
            chars += 1;
        }
        else if (word[i] >= 97 && word[i] <= 122)
        {
            chars += 1;
        }
    }

    return chars;
}

int count_sentences(string word)
{
    int sentences = 0;

    // If characters '.', '!' or '?' are identified, count as end of a sentence
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (word[i] == 46 || word[i] == 33 || word [i] == 63)
        {
            sentences += 1;
        }
    }

    return sentences;
}

int count_words(string word)
{
    // Since there are always n + 1 words, where n = spaces, we add 1 to the variable when calling it initially
    int words = 1;

    // Any spaces are counted as words
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (word[i] == 32)
        {
            words += 1;
        }
    }

    return words;
}