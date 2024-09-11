#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Sieve of Eratosthenes

The sieve is used to find prime numbers below any given upper limit.
*/

int *generate_sieve(const int upper_limit) {
    unsigned int size = upper_limit * sizeof(int);
    int *prime = (int *)malloc(size);
    memset(prime, -1, size);
    prime[0] = 0;
    prime[1] = 0;
    for (int i = 2; i < upper_limit; i++) {
        if (!prime[i])
            continue;
        int j = i + i;
        while (j < upper_limit) {
            prime[j] = 0;
            j += j;
        }
    }
    return prime;
}

void print_primes(int upper_limit, int *primes) {
    printf("---PRIME NUMBERS----\n");
    printf("[");
    for (int i = 0; i < upper_limit; i++) {
        if (primes[i] == -1) {
            if (i != 2)
                printf(",");
            printf("%d", i);
        }
    }
    printf("]\n");
}

int main() {
    const int upper_limit = 100;
    int *primes = generate_sieve(upper_limit);
    print_primes(upper_limit, primes);
    free(primes);
    return 0;
}