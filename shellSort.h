#include <stdio.h>

void shellSort(float A[][10],int size,int N,int dimension);
void ArrayCopy(float tmp[],float A[][10],int i,int dimension);
void ArrayCopy(float A[][10],float tmp[],int i,int dimension);
void ArrayCopy(float A[][10],int i, int j,int dimension);



void shellSort(float A[][10],int size,int N,int dimension)
{

// shell sort the Nth member of a[][]

int i,j,k,inc;
float tmp[size];


// start sorting array A
inc=size;

while (inc > 0)
{

   for (i = 0;i < size; i++)
   {
      j = i;
      
      // make a copy
      
      ArrayCopy(tmp,A,j,dimension);
            
      while ((j >= inc) && (A[j-inc][N] > tmp[N]))
      {
         ArrayCopy(A,j-inc,j,dimension);
	 j -= inc;
      }
      
      ArrayCopy(A,tmp,j,dimension);
      
   }
   
   inc /= 2;

}


}


void ArrayCopy(float tmp[],float a[][10],int i,int dimension)
{

      int k;
      
      // make a copy
      for (k = 0; k < dimension; k++) 
      {
         tmp[k]=a[i][k];
      }
}

void ArrayCopy(float a[][10],float tmp[],int i,int dimension)
{

      int k;
      
      // make a copy
      for (k = 0; k < dimension; k++) 
      {
         a[i][k]=tmp[k];
      }
}


void ArrayCopy(float A[][10],int i,int j, int dimension)
{

      int k;
      
      for (k = 0; k < dimension; k++) 
      {
         	A[j][k]=A[i][k];
      }
     
}
