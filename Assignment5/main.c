#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int multiplication();

int main() {
    srand(time(NULL));
    printf("Welcome to the Multiplication Game!\n");
    printf("You have 6 seconds for each question.\n");
    while (1) {
        if (!multiplication())
            break;
    }
    printf("\nThanks for playing!\n");
    return 0;
}

int multiplication() {
    int r1 = rand() % 10;
    int r2 = rand() % 10;
    int answer = r1 * r2;
    int user_answer = 0;
    time_t start = time(NULL);
    printf("\nWhat is %d x %d? ", r1, r2);
    while (difftime(time(NULL), start) < 6) {
        if (_kbhit()) {
            scanf("%d", &user_answer);
            if (user_answer == answer) {
                printf("Correct!\n");
                return 1;
            } else {
                printf("Wrong! Correct answer: %d\n", answer);
                return 0;   // stop game
            }
        }
    }
    printf("\nTime's up!\n");
    return 0;
}
