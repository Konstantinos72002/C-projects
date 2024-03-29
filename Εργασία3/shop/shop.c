#include <stdio.h>
#include <stdlib.h>
#include "func.h"
int main(int argc,char *argv[])
{ 
    int m,n,i,j,*k,**c,result;
    m = atoi(*++argv);                    //char m to intiger
    scanf("%d", &n);                             //n proionta               
    k = malloc(n*sizeof(int));              //dinamiki desmeysi mnimis n theseon
    if (k == NULL)                             //elegxos an yparxei katalilos xoros sti mnimi
    {
        printf("Sorry, cannot allocate memory\n");
        return -1;
    }
    c = malloc(n * sizeof(int*));                       //dinamiki desmeysi n int* theseon gia to kathe proion     
    if (c == NULL)                                           //elegxos an yparxei katalilos xoros sti mnimi
    {
        printf("Sorry, cannot allocate memory\n");
        return -1;
    } 
    for(i=0;i<n;i++)                                            //gia kathe proion
    {
        scanf("%d",k+i);                                       //k[i] pinakas me plithi typon toy i proiontos
        *(c+i) = malloc(*(k+i) * sizeof(int));
        if (*(c+i) == NULL)                                   //elegxos an yparxei katalilos xoros sti mnimi
        {
            printf("Sorry, cannot allocate memory\n");
            return -1;
        }
        for(j=0;j<*(k+i);j++)                                      //gia kathe tipo toy i proiontos
        scanf("%d",&c[i][j]);                     //c[i][j] kostos j tipoy toy i proiontos 682                                                                           
    }
    result = shop(m,n,k,c);                                      //klisi shop
    result == m ? printf("No solution found\n") : printf("Maximum amount spent is: %d\n",m - result);
    free(k);                                                    //dinamiki apeleytherosi mnimis
    for(i=0;i<n;i++) free(*(c+i));
    free(c);                                       
}