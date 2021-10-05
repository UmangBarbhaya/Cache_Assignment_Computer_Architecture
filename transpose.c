#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>


// Function transpose_naive() transposes a (blocksize x blocksize) block in a (n x n) martrix.
// The start indices in each block must be specified

void transpose_naive( int n, int blocksize, int *c_mat, int *ab_mat ) {
    //int i,j,k,m;
	int a=0,b=0;
    for ( int i = 0; i < n; i = i+ blocksize ) {
        for ( int j = 0; j < n; j =j+ blocksize ) {
            for ( int k = i; (k < i + blocksize) & (k < n) ; k=k+1 ) {
                for ( int m = j; (m < j + blocksize) & (m < n); m=m+1 ) {
					a=m + k*n;
					b=k + m*n;
                    c_mat[a] = ab_mat[b];
                }
            }
        }
    }
}

// Function transpose_blocking() iterate through the matrix by a block.
// It transposes each block matrix.
void transpose_blocking(int n,int blocksize, int* c_mat, int* ab_mat) {
    int p, q, cal_x, cal_y, y = 0, x = 0, j = 0, i = 0;

    for(y = 0; y < n / blocksize; y++)
        for(x = 0; x < n / blocksize; x++)
        {
            p = x * blocksize;
            q = y * blocksize;
            for(j = 0; j < blocksize; j++)
                for(i = 0; i < blocksize; i++)
                {
                    c_mat[p + i + q + j * n] = ab_mat[p + i * n + q + j];
                }
        }


    if(n % blocksize != 0)
    {
        p =  n / blocksize * blocksize;
        q =  0;

        for(j = 0; j < n; j++)
            for(i = p; i < n; i++)
            {
                c_mat[i + j * n] = ab_mat[i * n + j];
            }
        q =  n / blocksize * blocksize;
        p =  0;

        for(j = q; j < n; j++)
            for(i = 0; i < n - n % blocksize; i++)
            {
                c_mat[i + j * n] = ab_mat[i * n + j];
            }
    }
}

void transpose(int *A, int *B, int n, int blocksize,void (*transpose)(int, int, int*, int*), char *description) {

    int i, j, a=0, b=0;
	int x=0;
    printf("Testing %s: ", description);

    /* initialize A,B to random integers */
    srand( time( NULL ) );

    for( i = 0; i < n*n; i++ ){
			x= rand()%20000;
            A[i] = 1+x;
			x=rand()%20000;
            B[i] = 1+x;
    }
    /* measure performance */
    struct timeval start, end;

    gettimeofday( &start, NULL );
    transpose( n, blocksize, B, A );
    gettimeofday( &end, NULL );
	a = end.tv_sec - start.tv_sec;
	b = end.tv_usec - start.tv_usec;
    double seconds = (a) + 1.0e-6 * (b);
    printf( "%g milliseconds\n", seconds*1e3 );
}

int main() {
    int n, blocksize;
	printf("Setting 1");
    int n_array[]={100,1000,2000,5000,10000};
    for(int i=0; i<5;i++)
	{
		blocksize=20;
        n=n_array[i];
		int *A = (int*)malloc( n*n*sizeof(int) );
		int *B = (int*)malloc( n*n*sizeof(int) );
		printf("\nBlocking approach at n= %d \n",n);
		transpose(A, B, n, blocksize, transpose_blocking, "transpose with blocking");
		printf("Naive approach at n= %d \n",n);
		transpose(A, B,n , blocksize, transpose_naive, "naive transpose");
		printf("Freeing the resource\n");
		free( A );
		free( B );
    }

    printf("\n\nSetting 2");
    
    int blocksize_array[]={50,100,500,1000,5000};
    for(int i=0; i<5;i++)
	{
		n=10000;
        blocksize=blocksize_array[i];
		printf("Initializing the Matrix");
		int *A = (int*)malloc( n*n*sizeof(int) );
		int *B = (int*)malloc( n*n*sizeof(int) );
		printf("\nBlocking approach at blocksize= %d \n",blocksize);
		transpose(A, B, n, blocksize, transpose_blocking, "transpose with blocking");
        printf("Naive approach at blocksize= %d \n",blocksize);
		transpose(A, B, n , blocksize, transpose_naive, "naive transpose");
		printf("Freeing the resource\n");
		free( A );
		free( B );
    }
    return 0;
}
