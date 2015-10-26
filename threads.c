#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <pthread.h>

#define NTHREADS 4

int printFib(int x){
  int arr[]={1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,
  46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,14930352,
  24157817,39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170};

  return arr[x-1];
}

void *thread_f1(void *);
void *thread_f2(void *);
void *thread_f3(void *);
void *thread_f4(void *);

pthread_mutex_t mutex1;
pthread_cond_t  cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t  cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t  cond3 = PTHREAD_COND_INITIALIZER;

int  n;
int fibn;
char str[20];
char enstr[20];
int done=0;

void *thread_f1(void *dummyPtr)
{
	   pthread_mutex_lock( &mutex1 );

	   printf("Thread number 1 ", pthread_self());
	   printf("Enter the number and the string: ");
	   scanf("%d%s",&n,str);

	   pthread_cond_broadcast( &cond1);
	   done=1;
	   pthread_mutex_unlock( &mutex1 );
}

void *thread_f2(void *dummyPtr)
{
	pthread_mutex_lock( &mutex1 );

	while(done!=1){
		pthread_cond_wait( &cond1, &mutex1 );
	}

		printf("Thread number 2 %ld: ", pthread_self());
		//************************************************************************//
	   //encrypt the string
	    int i,j;
	    char table[37][2];

	    FILE* ftable=fopen("charMap.txt","r");
	    for(i=0;i<37;i++){
	        fscanf(ftable,"%c%*c%c%*c",&table[i][0],&table[i][1]);
	    }
	    fclose(ftable);

	    for(i=0;i<strlen(str);i++){
	        for(j=0;j<37;j++){
	            if(str[i]==table[j][0]){
	                enstr[i]=table[j][1];
	                break;
	            }
	        }
	    }

	    enstr[i+1]='\0';

	    printf("%s\n",enstr);
	    //************************************************************************//
	    pthread_cond_broadcast( &cond2);
	    done=2;
	    pthread_mutex_unlock( &mutex1 );
}

void *thread_f3(void *dummyPtr)
{
   pthread_mutex_lock( &mutex1 );
   
   while(done!=2){
   		pthread_cond_wait( &cond2, &mutex1 );
   }

   printf("Thread number 3 %ld: ", pthread_self());
   fibn = printFib(n);
   printf("%d\n",fibn);

   pthread_cond_broadcast( &cond3);
   done=3;
   pthread_mutex_unlock( &mutex1 );
}

void *thread_f4(void *dummyPtr)
{
   
   pthread_mutex_lock( &mutex1 );
   while(done!=3){
   		pthread_cond_wait( &cond3, &mutex1);
   	}

   printf("Thread number 4 %ld: ", pthread_self());
   printf("%d %s\n",fibn,enstr);

   pthread_mutex_unlock( &mutex1 );
}

int main()
{
	int j;
   pthread_t thread_id[NTHREADS];

   pthread_mutex_init(&mutex1, NULL);

   pthread_create( &thread_id[0], NULL, thread_f1, NULL );
   pthread_create( &thread_id[1], NULL, thread_f2, NULL );
   pthread_create( &thread_id[2], NULL, thread_f3, NULL );
   pthread_create( &thread_id[3], NULL, thread_f4, NULL );

   for(j=0; j < NTHREADS; j++)
   {
      pthread_join( thread_id[j], NULL); 
   }
}