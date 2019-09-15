/*
This is a test of shellSort

Author: Yen-Jie Lee

*/

#include <iostream.h>
#include "shellSort.h"

int main()
{

float a[10][10];

int dimension=2;
int size=10;

a[0][0]=321;
a[1][0]=143;
a[2][0]=2231;
a[3][0]=33241;
a[4][0]=1323;
a[5][0]=112;
a[6][0]=6123;
a[7][0]=7123;
a[8][0]=2131;
a[9][0]=22311;

a[0][1]=231;
a[1][1]=1;
a[2][1]=32231;
a[3][1]=3341;
a[4][1]=23123;
a[5][1]=13321;
a[6][1]=612;
a[7][1]=7123;
a[8][1]=23132;
a[9][1]=21123;

cout <<"before"<<endl;
for (int i=0;i<size;i++)
{
   for (int j=0;j<dimension;j++)
   {
      cout <<a[i][j]<<" ";
   }

   cout <<endl;


}

cout <<"after:"<<endl;

shellsort(a,size,1,dimension);

for (int i=0;i<size;i++)
{
   for (int j=0;j<dimension;j++)
   {
      cout <<a[i][j]<<" ";
   }

   cout <<endl;


}

return 1;
}
