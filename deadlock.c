#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

// Text attributes
#define RESET "\033[0m"
#define BOLD "\033[1m"

// Foreground colors
#define F_RED "\033[31m"
#define F_GREEN "\033[32m"
#define F_CYAN "\033[36m"


//GUNS
pthread_mutex_t ugly_gun = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t bad_gun = PTHREAD_MUTEX_INITIALIZER;


typedef struct s_cowboy
{
 char   *name;
 unsigned long reaction_time;
 pthread_t  thread;
}    t_cowboy;

void *action(void *data)
{
 t_cowboy cowboy;

 cowboy = *(t_cowboy *)data;
 // How 🔥 the cowboy is
 printf("⏰%s reaction_time "BOLD F_CYAN"%lu⏰\n"RESET,
   cowboy.name,
   cowboy.reaction_time);
 usleep(cowboy.reaction_time);


 if (!strcmp(cowboy.name, "ugly"))
  pthread_mutex_lock(&ugly_gun);
 else
  pthread_mutex_lock(&bad_gun);
 printf("%s has taken his own gun\n", cowboy.name);

 // I wanna take the other gun
 // DEADLOCK
 if (!strcmp(cowboy.name, "ugly"))
  pthread_mutex_lock(&bad_gun);
 else
  pthread_mutex_lock(&ugly_gun);

 // The killer will reach this position
 printf(F_RED"\t%s killed the other ☠️☠️☠️☠️☠️\n\n"RESET, cowboy.name);
 exit(EXIT_SUCCESS);

 return NULL;
}


int main()
{
 srand(time(NULL) * getpid());
 t_cowboy ugly = {"ugly", rand() % 10000};
 t_cowboy bad = {"bad", rand() % 10000};

 pthread_create(&ugly.thread, NULL, action, &ugly);
 pthread_create(&bad.thread, NULL, action, &bad);

 pthread_join(ugly.thread, NULL);
 pthread_join(bad.thread, NULL);
}
