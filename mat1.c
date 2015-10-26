#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int n,i,j,k,l;

	int num[]={1,5,10,20,50,100,200,500,1000,2000,3000};

	for(l=0;l<11;l++){

		n=num[l];

		int **mat1 = (int **)malloc(n * sizeof(int *));
		int **mat2 = (int **)malloc(n * sizeof(int *));
		int **prod = (int **)malloc(n * sizeof(int *));

		for(i=0; i<n; i++){
	        mat1[i] = (int *)malloc(n * sizeof(int));
	        mat2[i] = (int *)malloc(n * sizeof(int));
	        prod[i] = (int *)calloc(n,sizeof(int));
	    }

		srand(time(NULL));

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

		clock_t t;
		t=clock();

		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				for(k=0;k<n;k++){
					prod[i][j]+=mat1[i][k]*mat2[k][j];
				}
			}
		}

		t=clock()-t;
		FILE* f1;
		f1=fopen("matmuld.txt","a");
		fprintf(f1, "%d        %f\n",n,(float)t);
		close(f1);
	}

}