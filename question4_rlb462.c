#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_cond_t condition;
pthread_mutex_t mutex;
int counter;

void *increment_work()
{
   int index = 0;

   while( index < 3 )
   {
      pthread_mutex_lock( &mutex );

      while( counter < 10 )
      {
         printf("Count is now (inc fn): %d\n", counter);
         counter++;
      }

      pthread_cond_signal( &condition );
      pthread_mutex_unlock( &mutex );
      usleep(10000);

      while( counter != 0 )
      {
         pthread_cond_wait( &condition, &mutex );
      }

      index++;
   }
}

void *decrement_work()
{
   int index = 0;

   while( index < 2 )
   {
      while( counter != 10 )
      {
         pthread_cond_wait( &condition, &mutex );
      }

      pthread_mutex_lock( &mutex );

      while( counter > 0 )
      {
         printf("Count is now (dec fn): %d\n", counter);
         counter = counter - 1;
      }

      pthread_cond_signal( &condition );
      pthread_mutex_unlock( &mutex );
      usleep(10000);

      index++;
   }
}

int main()
{
   pthread_t thread_0, thread_1;
   counter = 0;

   pthread_cond_t condition;
   pthread_mutex_t mutex;

   pthread_create(&thread_0, NULL, increment_work, NULL);
   pthread_create(&thread_1, NULL, decrement_work, NULL);

   pthread_join( thread_0, NULL );
   pthread_join( thread_1, NULL );
}
