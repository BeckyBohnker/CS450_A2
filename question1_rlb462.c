#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
int buffer[3];
int correctCycles = 0;

void *do_work( void *arg )
{
   int id = (int) arg;
   
   int totalCycles = 0;
   
   while( correctCycles < 10 )
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
            correctCycles++;

            // print out buffer
            printf("%d%d%d\n", buffer[0], buffer[1], buffer[2]);
            printf("Total sequences generated: %d\n", totalCycles);
            printf("Number of correct sequences: %d\n", correctCycles);

         }


         buffer[0] = 0;
         buffer[1] = 0;
         buffer[2] = 0;

      }

      pthread_mutex_unlock(&mutex);  
      usleep(500000);    
   }
   
}

int main()
{
   pthread_t thread_1;
   pthread_t thread_2;
   pthread_t thread_3;
   
   int id_1 = 1;
   int id_2 = 2;
   int id_3 = 3;

   pthread_mutex_init( &mutex, NULL );
   buffer[0] = 0;
   buffer[1] = 0;
   buffer[2] = 0;
   
   pthread_create(&thread_1, NULL, do_work, (void *)id_1);
   pthread_create(&thread_2, NULL, do_work, (void *)id_2);
   pthread_create(&thread_3, NULL, do_work, (void *)id_3);


   pthread_join( thread_1, NULL );
   pthread_join( thread_2, NULL );
   pthread_join( thread_3, NULL );

   return 0;
}











































