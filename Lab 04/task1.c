#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Initial balance
int account_balance = 1000;

// Mutex for synchronizing access to account balance
pthread_mutex_t mutex;

// Function for random deposit or withdrawal
void* customer_thread(void* arg) {
    int id = *((int*)arg);
    int i;

    for (i = 0; i < 5; i++) {
        // Random amount between 1 and 100
        int amount = rand() % 100 + 1;
        int action = rand() % 2; // 0 for withdraw, 1 for deposit

        // Lock the mutex to ensure exclusive access to the account balance
        pthread_mutex_lock(&mutex);

        if (action == 0) { // Withdraw
            if (account_balance >= amount) {
                account_balance -= amount;
                printf("Customer %d withdrew %d, new balance: %d\n", id, amount, account_balance);
            } else {
                printf("Customer %d attempted to withdraw %d, but insufficient balance.\n", id, amount);
            }
        } else { // Deposit
            account_balance += amount;
            printf("Customer %d deposited %d, new balance: %d\n", id, amount, account_balance);
        }

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Simulate some processing time
        usleep(100000);
    }

    return NULL;
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create 4 threads representing 4 customers
    pthread_t threads[4];
    int thread_ids[4];
    
    for (int i = 0; i < 4; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, customer_thread, &thread_ids[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    printf("Final account balance: %d\n", account_balance);
    
    return 0;
}