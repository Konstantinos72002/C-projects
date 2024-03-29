#include <stdio.h>
#include <stdlib.h>
#include "func.h"
//#define COSTS
int shop(int m, int n, int *k, int **c)
{      
    int result,**array,i,j;
    array = malloc((n+1) * sizeof(int*));                       //dinamiki desmeysi n int* theseon gia to kathe proion     
    if (array == NULL)                                           //elegxos an yparxei katalilos xoros sti mnimi
    {
        printf("Sorry, cannot allocate memory\n");
        exit(-1);
    } 
    for(i=0;i<=n;i++) 
    {
        *(array+i) = malloc((m+1) * sizeof(int));
        if (*(array+i) == NULL)                                           //elegxos an yparxei katalilos xoros sti mnimi
        {
            printf("Sorry, cannot allocate memory\n");
            exit(-1);
        } 
    }
    for(i=0;i<=n;i++)
    for(j=0;j<=m;j++)
    array[i][j] = -1;
    result = recursive_2(m,n,0,m,k,c,m,array);
    #ifdef COSTS 
    printf("Item costs: ");
    int cost = m,sum=0;
    for(i=1;i<=n;i++)
    for(j=0;j<=m;j++)
    if(result == array[i][j]) 
    {
        printf("%d ",cost - j);
        cost -= cost -j;
        break;
    } 
    printf("\n");
    #endif
    for(i=0;i<=n;i++) free(*(array+i));
    free(array);
    return result; 
}
int recursive_2(int m,int n,int i,int p,int *k,int **c,int r,int **array)
{
    if(i>=0 && i<n && p>=0)
    {
        int min=m,j,temp;
        for(j=0;j<*(k+i);j++)
        {
            if(array[i][p] < 0) temp = recursive_2(m,n,i+1,p-c[i][j],k,c,r,array);
            else 
            {
                r = array[i][p];
                break;
            }
            if (min > temp) min = temp;
        }
        r = min;
        array[i][p] = r;
    }  
    else if(i == n  && p>=0) 
    {
        r = p;
        array[i][p] = r;
    }
    else r = m;
    return r;
}