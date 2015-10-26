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
	int j,k,m;

	for(m=0;m<(n/100);m++){
		for(j=0;j<n;j++){
			for(k=0;k<n;k++){
				prod[(*i)+m][j]+=mat1[*i][k]*mat2[k][j];
			}
		}
	}
}

int main()
{	
    int n,i,j,l,nth;

	int num[23];
	num[0]=100;
	num[1]=200;
	num[2]=500;

	for(l=0;l<20;l++){
		num[l+3]=1000+(100*l);
	}

	for(l=0;l<23;l++){

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

   		pthread_t thread_id[100];

   		for(i=0;i<100;i++){
   			int* k=malloc(sizeof(*k));
   			*k=i*(n/100);
   			pthread_create(&thread_id[i],NULL,thread_f,k);
   		}

   		for(j=0; j < 100; j++)
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