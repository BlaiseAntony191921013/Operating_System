#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1) {
        return 0;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }

    return 1;
}

// Function to generate the Fibonacci series
void fibonacci(int n) {
    int first = 0, second = 1;
    printf("Fibonacci Series: %d, %d, ", first, second);

    for (int i = 2; i < n; i++) {
        int next = first + second;
        printf("%d, ", next);
        first = second;
        second = next;
    }

    printf("\n");
}

int main() {
  // Number of Fibonacci numbers to generate

    pid_t pid = fork();
     int n = 10; 

    if (pid < 0) {
        // Error occurred
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        fibonacci(n);
    } else {
        // Parent process
        wait(NULL);

        printf("Prime Numbers: ");
        for (int i = 2; i <= n; i++) {
            if (isPrime(i)) {
                printf("%d ", i);
            }
        }
        printf("\n");
    }

    return 0;
}

