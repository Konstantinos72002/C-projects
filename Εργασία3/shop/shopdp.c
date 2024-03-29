#include <stdio.h>
#include <stdlib.h>
#include "func.h"
//#define COSTS
int shop(int m, int n, int *k, int **c)
{
    int i,j,f,**array,x;
    array = malloc(n * sizeof(int*));
    if (array == NULL)                                           //elegxos an yparxei katalilos xoros sti mnimi
    {
        printf("Sorry, cannot allocate memory\n");
        exit(-1);
    } 
    for(i=0;i<n;i++) 
    {
        *(array+i) = malloc((m+1) * sizeof(int));
        if (*(array+i) == NULL)                                           //elegxos an yparxei katalilos xoros sti mnimi
        {   
            printf("Sorry, cannot allocate memory\n");
            exit(-1);
        }
    }
    for(i=0;i<n;i++)
    for(j=0;j<m+1;j++)
    array[i][j] = 0;                                            //array boolean pinakas arxikopoioyme me 0
    for(j=0;j<*k;j++)                                           
    {
        if(m-c[0][j]>=0) array[0][m-c[0][j]] = c[0][j];
        else 
        {
            for(i=0;i<n;i++) free(*(array + i));
            free(array);
            return m;
        }
    }
    for(i=1;i<n;i++)
        for(f=0;f<m+1;f++)
            if(array[i-1][f])
                for(j=0;j<*(k+i);j++)
                    if(f-c[i][j]>=0) array[i][f-c[i][j]] = c[i][j];
    for(j=0;j<m+1;j++)
    {
        if(array[n-1][j]) break;
        if(j==m) 
        {
            j = m;
            break;
        }
    }
    if (j != m)
    {
        #ifdef COSTS 
        printf("Item costs: ");
        int line=n-1,sum;
        for(i=0;i<m;i++)
        if(array[line][i]) break;
        sum = array[line][i];
        printf("%d ",array[line][i]);
        while(line--) 
        {
            printf("%d ",array[line][sum+i]);
            sum += array[line][sum+i];
        }
        printf("\n");
        #endif
    }   
    for(i=0;i<n;i++) free(*(array + i));
    free(array);
    return j;
}