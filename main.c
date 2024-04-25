#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "generic_vector.h"

typedef enum win { LOSS, WIN } GameResult;

void clear_keyboard_buffer();
void setUpGame(GENERIC_VECTOR arr[], int totals[]);
void play(GENERIC_VECTOR pWords, int letters, int guesses, int debugging, int len);
GENERIC_VECTOR* partition(GENERIC_VECTOR words, char guess, int letters, int len);
void generatePermutations(char letter, int maxLen, int remaining, char** arr, int start, int stop);
char** permute(char letter, int len);
Boolean matches_pattern(char* left, char* right, int len, char letter);

int main(int argc, char* argv[]) {
	int i;
	int size;
	int totals[30] = {0};
	GENERIC_VECTOR arr[30];
    FILE* fp;
    char ch;
    char playAgain = 'y';
    for (i = 0; i < 30; i++) {
		arr[i] = generic_vector_init_default(my_string_init_copy, my_string_destroy);
		if (arr[i] == NULL) {
			printf("CAMI IT FAILED\n");
			exit(1);
		}
	}

	fp= fopen("dictionary.txt", "r");
	ch = fgetc(fp);
	while(ch != EOF) {
		ungetc(ch, fp);
		MY_STRING hString = my_string_init_default();
		if (hString == NULL) {
			printf("my_string_init_default failed\n");
			exit(1);
		}
		my_string_extraction(hString, fp);
		size = my_string_get_size(hString);
		if (size > 0 && size <= 30) {
			totals[size - 1]++;
			if (generic_vector_push_back(arr[size - 1], hString) == FAILURE) {
				printf("CAMI WHY DID VECTOR PUSH BACK FAIL\n");
				exit(1);
			}
		}

		my_string_destroy(&hString);
		ch = fgetc(fp);
	}

	fclose(fp);

    while (playAgain == 'y') {
        setUpGame(arr, totals);
        playAgain = 0;
        while (playAgain != 'y' && playAgain != 'n') {
            printf("Would you like to play again (y/n): ");
            scanf("%c", &playAgain);
            clear_keyboard_buffer();
        }
    }


	for (i = 0; i < 30; i++) {
		generic_vector_destroy(arr + i);
	}

	return 0;
}

void setUpGame(GENERIC_VECTOR arr[], int totals[]) {
	int numberOfLetters = 0;
	int guessNum = 0;
	char runningTotal = 0;
    int noc = 0;

    printf("Please input a how many letters: ");
    while (noc == 0 || numberOfLetters <= 1 || numberOfLetters >= 30 || totals[numberOfLetters - 1] <= 0) {
        noc = scanf("%d", &numberOfLetters);
        clear_keyboard_buffer();
        if (noc == 0 || numberOfLetters <= 1 || numberOfLetters >= 30 || totals[numberOfLetters - 1] <= 0) {
            printf("Incorrect amount, Please input a how many letters: ");
        }
    }

	printf("How many guesses: ");
    while(noc == 0 || guessNum <= 0) {
        noc = scanf("%d", &guessNum);
        clear_keyboard_buffer();
        if (noc == 0 || guessNum <= 0) {
            printf("Incorrect amount, Please choose a positive number of guesses: ");
        }
    }

	printf("Would you like a running total of words remaining? (y/n): ");
    while (noc == 0 || (runningTotal != 'y' && runningTotal != 'n')) {
        noc = scanf("%c", &runningTotal);
        clear_keyboard_buffer();
        if (noc == 0 || (runningTotal != 'y' && runningTotal != 'n')) {
            printf("Please input (y/n):");
        }
    }

	GENERIC_VECTOR hVector = generic_vector_init_copy(arr[numberOfLetters - 1]);
	if (hVector == NULL) {
		printf("hVector is null when copy\n");
		exit(1);
	}

    play(hVector, numberOfLetters, guessNum, runningTotal == 'y', totals[numberOfLetters - 1]);
}

void play(GENERIC_VECTOR words, int letters, int guesses, int debugging, int len) {
	int i;
	char correctWord[letters + 1];
	int endGame = 0;
    int totalFamilies = 1 << letters;
    char guess;
    int firstGuess = 1;
    int guessedLetters[26] = { 0 };
    for (i = 0; i < letters; i++) {
        correctWord[i] = '_';
    }

    correctWord[letters] = '\0';

    while (!endGame) {
        guess = 0;
        GameResult gameResult;
        GENERIC_VECTOR* families = NULL;
        GENERIC_VECTOR* longest = NULL;
        if (debugging) {
            printf("Total words: %d\n", generic_vector_get_size(words));
        }

        while (!isalpha(guess) || (guess >= 'a' && guess <= 'z' && guessedLetters[guess - 'a'])) {
            if (!firstGuess) {
                printf("Guesses so far: ");
                for (i = 0; i < 26; i++) {
                    if (guessedLetters[i]) {
                        printf("%c ", i + 'a');
                    }
                }

                printf("\n");
            }

            printf("What is your guess: ");
            scanf("%c", &guess);
            clear_keyboard_buffer();
            if (!isalpha(guess)) {
                printf("Please input a letter as a guess: ");
            } else {
                guess = tolower(guess);
                if (guessedLetters[guess - 'a']) {
                    printf("You have already guessed that\n");
                }
            }
        }

        firstGuess = 0;
        guessedLetters[guess - 'a'] = 1;

        if (generic_vector_get_size(words) > 1) {
            families = partition(words, guess, letters, len);
            longest = families;
            int longestLen = generic_vector_get_size(*families);
            for (i = 0; i < totalFamilies; i++) {
                int currentLen = generic_vector_get_size(families[i]);
                if (currentLen > longestLen) {
                    longest = families + i;
                    longestLen = currentLen;
                }
            }

            generic_vector_destroy(&words);
            words = generic_vector_init_copy(*longest);
            len = longestLen;
        }

        int placeLetter = 0;
        for (i = 0; i < letters; i++) {
            if (*my_string_at(*generic_vector_at(words, 0), i) == guess) {
                correctWord[i] = guess;
                placeLetter = 1;
            }
        }

		if (placeLetter) {
			printf("Correct!\n");
		} else {
			guesses--;
			printf("Incorrect. You have %d lives remaining\n", guesses);
		}

		printf("Word: %s\n", correctWord);

		if (guesses <= 0) {
			gameResult = LOSS;
			endGame = 1;
		}

		if (!endGame) {
			int hasDashes = 0;
			for (i = 0; i < letters; i++) {
				if (correctWord[i] == '_') {
					hasDashes = 1;
				}
			}

			if (!hasDashes) {
				endGame = 1;
				gameResult = WIN;
			}
		}

        if (families != NULL) {
            for (i = 0; i < totalFamilies; i++) {
                generic_vector_destroy(families + i);
            }

            free(families);
        }

		if (endGame) {
			if (gameResult == LOSS) {
				printf("You lost\n");
                printf("The word was %s\n", my_string_c_str(*generic_vector_at(words, 0)));
			} else {
				printf("You won\n");
			}

			break;
		}
	}

    generic_vector_destroy(&words);
}

GENERIC_VECTOR* partition(GENERIC_VECTOR words, char guess, int letters, int len) {
	int i;
	int j;
    int totalPermutations = 1 << letters;
    char** permutations = permute(guess, letters);
	Status res;
	GENERIC_VECTOR* result = (GENERIC_VECTOR*)malloc(totalPermutations * sizeof(GENERIC_VECTOR));
	if (result == NULL) {
		printf("result did not malloc");
		exit(1);
	}

	for (i = 0; i < totalPermutations; i++) {
		result[i] = generic_vector_init_default(my_string_init_copy, my_string_destroy);
		if (result[i] == NULL) {
			printf("failed to partition words");
			exit(1);
		}
	}

	for (i = 0; i < len; i++) {
		MY_STRING word = *generic_vector_at(words, i);
		for (j = 0; j < totalPermutations; j++) {
			if (matches_pattern(my_string_c_str(word), permutations[j], letters, guess) == TRUE) {
				res = generic_vector_push_back(result[j], word);
				if (res == FAILURE) {
					printf("Failed to partition words\n");
					exit(1);
				}
			}
		}
	}

    for (i = 0; i < totalPermutations; i++) {
        free(permutations[i]);
    }

    free(permutations);

	return result;
}

void generatePermutations(char letter, int maxLen, int remaining, char** arr, int start, int stop) {
    if (remaining == 0) {
        return;
    }

    int mid = (start + stop) / 2;
    for (int i = start; i < mid; i++) {
        arr[i][maxLen - remaining] = '_';
    }

    for (int i = mid; i < stop; i++) {
        arr[i][maxLen - remaining] = letter;
    }

    generatePermutations(letter, maxLen, remaining - 1, arr, start, mid);
    generatePermutations(letter, maxLen, remaining - 1, arr, mid, stop);
}

char** permute(char letter, int len) {
    int totalPermutations = 1 << len;
    char** result = malloc(sizeof(char*) * totalPermutations);
    for (int i = 0; i < totalPermutations; i++) {
        result[i] = malloc(sizeof(char) * (len + 1));
    }

    generatePermutations(letter, len, len, result, 0, totalPermutations);
    return result;
}

Boolean matches_pattern(char* left, char* right, int len, char letter) {
    int i;
    int matches = 1;
    for (i = 0; i < len; i++) {
        if (right[i] == letter) {
            if (left[i] != letter) {
                matches = 0;
            }
        } else {
            if (left[i] == letter) {
                matches = 0;
            }
        }
    }

    return matches == 1 ? TRUE : FALSE;
}

void clear_keyboard_buffer() {
	char ch;
	do {
		scanf("%c", &ch);
	} while (ch != '\n');
}
