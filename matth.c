#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <pthread.h>

void *thread_f(void *);
int  n;
int** mat1;
int** mat2;
int** prod;

void *thread_f(void *num)
{
	int *i= num;
	//printf("%d\n", *i);
	int j,k;

	for(j=0;j<n;j++){
		for(k=0;k<n;k++){
			prod[*i][j]+=mat1[*i][k]*mat2[k][j];
		}
	}
}

int main()
{	
    int n,i,j,l,nth;

	int num[]={1,5,10,20,50,100,200};

	for(l=0;l<5;l++){

		n=num[l];

		mat1 = (int **)malloc(n * sizeof(int *));
		mat2 = (int **)malloc(n * sizeof(int *));
		prod = (int **)malloc(n * sizeof(int *));

		for(i=0; i<n; i++){
	        mat1[i] = (int *)malloc(n * sizeof(int));
	        mat2[i] = (int *)malloc(n * sizeof(int));
	        prod[i] = (int *)calloc(n,sizeof(int));
	    }

		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				mat1[i][j]=rand()%100;
			}
		}

		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				mat2[i][j]=rand()%100;
			}
		}

		srand(time(NULL));

		clock_t t;
		t=clock();

   		pthread_t thread_id[n];

   		for(i=0;i<n;i++){
   			int* k=malloc(sizeof(*k));
   			*k=i;
   			pthread_create(&thread_id[i],NULL,thread_f,k);
   		}

   		for(j=0; j < n; j++)
   		{
      		pthread_join( thread_id[j], NULL); 
   		}
		
		t=clock()-t;
		FILE* f1;
		f1=fopen("matmult.txt","a");
		fprintf(f1, "%d        %f\n",n,(float)t);
		close(f1);
	}
   
}