#include <stdio.h>
#include <stdlib.h>
#include "func.h"
int shop(int m, int n, int *k, int **c)
{
    int result;
    result = recursive(m,n,0,m,k,c,m);
    return result;
}
int recursive(int m,int n,int i,int p,int *k,int **c,int r)
{
    if(i>=0 && i<n && p>=0)
    {
        int min=m,j,temp;
        for(j=0;j<*(k+i);j++)
        {
            temp = recursive(m,n,i+1,p-c[i][j],k,c,r);
            if (min > temp) min = temp;
        }
        r = min;
    }   
    else if(i == n  && p>=0) r = p; 
    else r = m;
    return r;
}