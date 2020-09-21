#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int total = 0;
int counter = 0;
pthread_cond_t condition;
pthread_mutex_t mutex;

void *do_work( void *arg )
{
   int id = (int)arg;

   while( total < 990 )
   {
      pthread_mutex_lock( &mutex );

      while( counter != id )
      {
         pthread_cond_wait( &condition, &mutex );
      }
         
      total = total + id;
      printf( "my num: %d, total: %d\n", id, total );

      if( id == 9 )
      {
        counter = 0;
      }
      else
      {
         counter++;
      }

      pthread_cond_signal( &condition );
      pthread_mutex_unlock( &mutex );
      usleep(10000);
   }

   return NULL;
}

int main()
{
   pthread_mutex_init( &mutex, NULL );
   pthread_cond_init( &condition, NULL );

   pthread_t thread_0, thread_1, thread_2, thread_3, thread_4, thread_5, thread_6, thread_7, thread_8, thread_9;

   int id_0 = 0;
   int id_1 = 1;
   int id_2 = 2;
   int id_3 = 3;
   int id_4 = 4;
   int id_5 = 5;
   int id_6 = 6;
   int id_7 = 7;
   int id_8 = 8;
   int id_9 = 9;

   pthread_create(&thread_0, NULL, do_work, (void *)id_0);
   pthread_create(&thread_1, NULL, do_work, (void *)id_1);
   pthread_create(&thread_2, NULL, do_work, (void *)id_2);
   pthread_create(&thread_3, NULL, do_work, (void *)id_3);
   pthread_create(&thread_4, NULL, do_work, (void *)id_4);
   pthread_create(&thread_5, NULL, do_work, (void *)id_5);
   pthread_create(&thread_6, NULL, do_work, (void *)id_6);
   pthread_create(&thread_7, NULL, do_work, (void *)id_7);
   pthread_create(&thread_8, NULL, do_work, (void *)id_8);
   pthread_create(&thread_9, NULL, do_work, (void *)id_9);

   pthread_join( thread_0, NULL );
   pthread_join( thread_1, NULL );
   pthread_join( thread_2, NULL );
   pthread_join( thread_3, NULL );
   pthread_join( thread_4, NULL );
   pthread_join( thread_5, NULL );
   pthread_join( thread_6, NULL );
   pthread_join( thread_7, NULL );
   pthread_join( thread_8, NULL );
   pthread_join( thread_9, NULL );

   return 0;
}
