

#include <stdio.h>
#include <pthread.h>

#define RACE_CONDITION 100000
int             g_drinks_served;
// Global mutex for synchronizing access to g_drinks_served
// This is a struct, think about a 🔒 that can be closed or open.
pthread_mutex_t mutex;
void *serve_drink(void *arg)
{
 int i;
 i = 0;
 while (i++ < RACE_CONDITION)
    {
    // Locking the mutex before updating the global variable
    // 🔒 closing the lock
    // before the waiter didn't do its stuff, nobody writes here
        pthread_mutex_lock(&mutex);
    /*
     🚨 critical section 🚨
      "scheduler just leave me do my job here"
           1)LOAD    <-
      2)ADD     <-
      3)STORE   <-
    */
      g_drinks_served++;

    // 🔓 opening
        pthread_mutex_unlock(&mutex);
    }
 return (NULL);
}
int main(void)
{
 pthread_t waiter1;
 pthread_t waiter2;
 // Initialize the mutex
 // setting the value to open 🔓 for example
 if(pthread_mutex_init(&mutex, NULL) != 0)
 {
  printf("Mutex initialization failed!\\n");
  return 1;
 }
 pthread_create(&waiter1, NULL, serve_drink, NULL);
 pthread_create(&waiter2, NULL, serve_drink, NULL);

 pthread_join(waiter1, NULL);
 pthread_join(waiter2, NULL);
 // Destroy the mutex after its use
 // it is a struct to clean, no LEAKS
 pthread_mutex_destroy(&mutex);
 printf("Total drinks served: %d\\n", g_drinks_served);
 return (0);
}