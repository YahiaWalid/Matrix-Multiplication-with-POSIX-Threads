#include<stdlib.h>
#include<pthread.h>
#define Item(X, I, J, NCOL)      X[((J) + (I) * (NCOL))]

//struct element that holds info for each element
typedef struct element {
    int i;      //used to store row number
    int j;      //used to srore column number
    int *A;     //used to point to matrix A
    int *B;     //used to point to matrix B
    int *C;     //used to point to matrix C
    int n ,m,l; //used to store matrices dimensions
} element;

//struct element that holds info for each row
typedef struct row {
    int i;      //used to store row number
    int *A;     //used to point to matrix A
    int *B;     //used to point to matrix B
    int *C;     //used to point to matrix C
    int n ,m,l; //used to store matrices dimensions
} row;

//thread function that calculates the value of each element and stores it in resultant matrix C
void *calculateELement(void *etemp){

    element* e = (element*)etemp;

    int sum = 0;
    for(int k=0; k<e->m; k++)                                          //(loop 3)
        sum += Item(e->A, e->i, k, e->m) * Item(e->B, k, e->j, e->n);
    Item(e->C, e->i, e->j, e->n) = sum;

    return NULL;
}

//thread function that calculates the value of each row and stores it in resultant matrix C
void *calculateRow(void *rtemp){

    row* r = (row*)rtemp;

    for(int j=0; j<r->n; j++)                                       //(loop 2)
    {
        int sum = 0;
        for(int k=0; k<r->m; k++)                                   //(loop 3)
            sum += Item(r->A, r->i, k, r->m) * Item(r->B, k, j, r->n);
        Item(r->C, r->i, j, r->n) = sum;
    }



    return NULL;
}


/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void matmult(int* A, int* B, int* C, int l, int m, int n)       // O(n^3)
{
    for(int i=0; i<l; i++)                          // (loop 1)
        for(int j=0; j<n; j++)                      // (loop 2)
        {
            int sum = 0;
            for(int k=0; k<m; k++)                  // (loop 3)
                sum += Item(A, i, k, m) * Item(B, k, j, n);
            Item(C, i, j, n) = sum;
        }


}


/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */

 //The computation of each element of the output matrix happens in a thread.
void matmult_v1(int* A, int* B, int* C, int l, int m, int n)  // O(n^3)
{
    //Declaring an array of threads of size = # elements in matrix C (resultant)
    //Number of elements in the matrix = C.#columns * C.#rows = n*l
    int size = n*l;
    pthread_t element_thread[size];

    element e[size];


        int index = 0;
        for(int i=0; i<l; i++)  //iterating over each row in C                   (loop 1)
        for(int j=0; j<n; j++)  //iterating over each column in C                (loop 2)
        {

            //initializing and making members of the struct instant point to the matrices we are working on
            e[index].i=i;
            e[index].j=j;
            e[index].A = A;
            e[index].B = B;
            e[index].C = C;
            e[index].l = l;
            e[index].m = m;
            e[index].n = n;

            //creating threads to compute each element
            pthread_create( &element_thread[index], NULL, calculateELement, &e[index]);//function has loop 3

            index++;
        }


        //joining threads after we have created them all
        for(int k=0;k<size;k++)
            pthread_join( element_thread[k], NULL);



}


/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */

//The computation of each element of the output matrix happens in a thread.
void matmult_v2(int* A, int* B, int* C, int l, int m, int n)   // O(n^3)
{

    //Declaring an array of threads of size = # rows in matrix C (resultant)
    int size = l;
    pthread_t row_thread[size];

    row r[size];


    int index = 0;
    for(int i=0; i<l; i++){                                 //(loop 1)


            //initializing and making members of the struct instant point to the matrices we are working on
            r[index].i=i;
            r[index].A = A;
            r[index].B = B;
            r[index].C = C;
            r[index].l = l;
            r[index].m = m;
            r[index].n = n;


            //creating threads to compute each element
            pthread_create( &row_thread[index], NULL, calculateRow, &r[index]); // function has loop2,3


            index++;
    }

    //joining threads after we have created them all
    for(int k=0;k<size;k++)
        pthread_join( row_thread[k], NULL);

}
