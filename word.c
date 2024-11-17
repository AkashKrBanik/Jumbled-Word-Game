#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void shuffleWord(char *word, int length, char *jumbledWord) {
    int i, j;
    int used[length];

    for (i = 0; i < length; i++) {
        used[i] = 0;
    }

    for (i = 0; i < length; i++) {
        do {
            j = rand() % length;
        } while (used[j] == 1);

        jumbledWord[i] = word[j];
        used[j] = 1;
    }
    jumbledWord[length] = '\0';
}

void displayJumbledWord(char *jumbledWord) {
    printf("Jumbled word: ");
    for (int i = 0; jumbledWord[i] != '\0'; i++) {
        printf("%c ", jumbledWord[i]);
    }
    printf("\n");
}

int checkGuess(char *word, char *guess) {
    return strcmp(word, guess) == 0;
}

int selectUniqueWord(char *words[], char *hints[], int wordCount, int usedWords[], int *usedWordCount) {
    int index;
    do {
        index = rand() % wordCount;
    } while (usedWords[index] == 1);

    usedWords[index] = 1;
    (*usedWordCount)++;
    return index;
}

int main() {
    char *words[] = {
        "apple", "banana", "cherry", "grape", "mango", "orange", "kiwi", "papaya", "peach", "plum",
        "ocean", "mountain", "river", "valley", "desert", "forest", "island", "lake", "sea", "beach",
        "computer", "laptop", "keyboard", "mouse", "printer", "monitor", "processor", "router", "modem", "server",
        "biology", "physics", "chemistry", "algebra", "geometry", "calculus", "history", "geography", "literature", "philosophy",
        "soccer", "tennis", "cricket", "basketball", "hockey", "golf", "rugby", "badminton", "volleyball", "baseball"
    };
    char *hints[] = {
        "fruit", "fruit", "fruit", "fruit", "fruit", "fruit", "fruit", "fruit", "fruit", "fruit",
        "nature", "nature", "nature", "nature", "nature", "nature", "nature", "nature", "nature", "nature",
        "tech", "tech", "tech", "tech", "tech", "tech", "tech", "tech", "tech", "tech",
        "science", "science", "science", "math", "math", "math", "history", "history", "literature", "philosophy",
        "sport", "sport", "sport", "sport", "sport", "sport", "sport", "sport", "sport", "sport"
    };
    int wordCount = sizeof(words) / sizeof(words[0]);
    int usedWords[50] = {0};
    int usedWordCount = 0;

    srand(time(NULL));
    char guess[20];
    int score = 0;
    int correctGuesses = 0;

    printf("Welcome to the Jumbled Word Game!\n\n");

    while (usedWordCount < wordCount) {
        int wordIndex = selectUniqueWord(words, hints, wordCount, usedWords, &usedWordCount);
        char *selectedWord = words[wordIndex];
        char *hint = hints[wordIndex];
        int wordLength = strlen(selectedWord);

        char jumbledWord[20];
        shuffleWord(selectedWord, wordLength, jumbledWord);

        int attempts = 3;
        int guessedCorrectly = 0;

        while (attempts > 0) {
            displayJumbledWord(jumbledWord);
            printf("Enter your guess: ");
            scanf("%s", guess);

            if (checkGuess(selectedWord, guess)) {
                printf("Congratulations! You guessed the word correctly.\n");
                score += 10;
                correctGuesses++;
                printf("Your score: %d\n", score);
                guessedCorrectly = 1;
                break;
            } else {
                attempts--;
                if (attempts == 0) {
                    printf("Hint: %s (Surprise Last attempt)\n", hint);
                    printf("Enter your guess: ");
                    scanf("%s", guess);
                    if (checkGuess(selectedWord, guess)) {
                        printf("Congratulations! You guessed the word correctly with the hint.\n");
                        score += 5;
                        correctGuesses++;
                        printf("Your score: %d\n", score);
                        guessedCorrectly = 1;
                        break;
                    }
                } else {
                    printf("Incorrect guess. Try again! Attempts left: %d\n", attempts);
                }
            }
        }

        if (!guessedCorrectly) {
            printf("Sorry, you've used all attempts. The word was '%s'.\n", selectedWord);
            break;
        }

        if (correctGuesses >= 10) {
            if (correctGuesses % 3 == 0) {
                char choice;
                printf("You've guessed %d words correctly! Would you like to continue playing? (y/n): ", correctGuesses);
                scanf(" %c", &choice);

                if (choice == 'n' || choice == 'N') {
                    printf("Thank you for playing! Your final score: %d\n", score);
                    return 0;
                }
            }
        }
    }

    printf("Game over! Your final score: %d\n", score);
    return 0;
}
