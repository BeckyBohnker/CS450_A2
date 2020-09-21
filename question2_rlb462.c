#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;

int buffer[3];
int correctCycles1 = 0;
int firstloopgoing = 0;
int totalCycles1 = 0;

int buffer2[3];
int correctCycles2 = 0;
int secondloopgoing = 0;
int totalCycles2 = 0;

void *do_work( void *arg )
{
   int id = (int) arg;
   
   int totalCycles = 0;
   
   while( correctCycles1 < 10 && secondloopgoing == 0 )
   {
      pthread_mutex_lock(&mutex);

      totalCycles++;

      if( buffer[0] == 0 )
      {
         // first position empty

         printf( "My id: %d\n", id );
         buffer[0] = id;
      }
      else if( buffer[1] == 0 )
      { 
         // second position empty

         printf( "My id: %d\n", id );
         buffer[1] = id;
      }
      else
      { 
         // last spot only one left

         printf( "My id: %d\n", id );
         buffer[2] = id;

         if( buffer[0] == 1 && buffer[1] == 2 && buffer[2] == 3 )
         {
            // undate correctCycles
            correctCycles1++;

            // print out buffer
            printf("%d%d%d\n", buffer[0], buffer[1], buffer[2]);
         }

         buffer[0] = 0;
         buffer[1] = 0;
         buffer[2] = 0;

      }

      pthread_mutex_unlock(&mutex);  
      usleep(500000);    
   }   

      if( correctCycles1 == 10 )
      {
         firstloopgoing = 1;
      }
      totalCycles1 = totalCycles;

}

void *do_work2( void *arg )
{
   int id = (int) arg;
   
   int totalCycles = 0;
   
   while( correctCycles2 < 10 && firstloopgoing == 0 )
   {
      pthread_mutex_lock(&mutex);

      totalCycles++;

      if( buffer2[0] == 0 )
      {
         // first position empty

         printf( "My id: %d\n", id );
         buffer2[0] = id;
      }
      else if( buffer2[1] == 0 )
      { 
         // second position empty

         printf( "My id: %d\n", id );
         buffer2[1] = id;
      }
      else
      { 
         // last spot only one left

         printf( "My id: %d\n", id );
         buffer2[2] = id;

         if( buffer2[0] == 4 && buffer2[1] == 5 && buffer2[2] == 6 )
         {
            // undate correctCycles
            correctCycles2++;

            // print out buffer
            printf("%d%d%d\n", buffer2[0], buffer2[1], buffer2[2]);
         }

         buffer2[0] = 0;
         buffer2[1] = 0;
         buffer2[2] = 0;

      }

      pthread_mutex_unlock(&mutex);  
      usleep(500000);    
   }   

      if( correctCycles2 == 10 )
      {
         secondloopgoing = 1;
      }
      totalCycles2 = totalCycles;
}

int main()
{
   pthread_t thread_1;
   pthread_t thread_2;
   pthread_t thread_3;
   pthread_t thread_4;
   pthread_t thread_5;
   pthread_t thread_6;
   
   int id_1 = 1;
   int id_2 = 2;
   int id_3 = 3;
   int id_4 = 4;
   int id_5 = 5;
   int id_6 = 6;

   pthread_mutex_init( &mutex, NULL );

   buffer[0] = 0;
   buffer[1] = 0;
   buffer[2] = 0;
   buffer2[0] = 0;
   buffer2[1] = 0;
   buffer2[2] = 0;
   
   pthread_create(&thread_1, NULL, do_work, (void *)id_1);
   pthread_create(&thread_2, NULL, do_work, (void *)id_2);
   pthread_create(&thread_3, NULL, do_work, (void *)id_3);
   pthread_create(&thread_4, NULL, do_work2, (void *)id_4);
   pthread_create(&thread_5, NULL, do_work2, (void *)id_5);
   pthread_create(&thread_6, NULL, do_work2, (void *)id_6);

   pthread_join( thread_1, NULL );
   pthread_join( thread_2, NULL );
   pthread_join( thread_3, NULL );
   pthread_join( thread_4, NULL );
   pthread_join( thread_5, NULL );
   pthread_join( thread_6, NULL );

   if( correctCycles1 == 10 )
   {
      printf("Team 1 won!\n");
   }
   if( correctCycles2 == 10 )
   {
      printf("Team 2 won!\n");
   }

   printf("Total sequences generates team1: %d\n", totalCycles1);
   printf("Number of correct sequences team1: %d\n", correctCycles1);
   printf("Total sequences generates team2: %d\n", totalCycles2);
   printf("Number of correct sequences team2: %d\n", correctCycles2);

   return 0;
}











































