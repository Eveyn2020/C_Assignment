#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int multiplication();

int main() {
    srand(time(NULL));
    printf("Welcome to the Multiplication Game!\n");
    printf("You have 6 seconds for each question.\n");
    while (multiplication());
    printf("\nThanks for playing!\n");
    return 0;
}

int multiplication() {
    int r1 = rand() % 10;
    int r2 = rand() % 10;
    int answer = r1 * r2;
    int user_answer;
    time_t start, end;

    printf("\nWhat is %d x %d? ", r1, r2);
    time(&start);
    scanf("%d", &user_answer);
    time(&end);
    while (difftime(end, start) > 6) {
        printf("Time's up!\n");
        return 0;
    }
    if (user_answer == answer) {
        printf("Correct!\n");
        return 1;
    } else {
        printf("Wrong! Correct answer: %d\n", answer);
        return 0;
    }
}
