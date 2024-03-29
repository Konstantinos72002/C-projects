#include <stdio.h>
#include <stdlib.h>
#define MINNUM 2100000000
#define MAXNUM 2101000000
#define MAXK 5
#define COMPUTATIONS 20

int main() 
{
	 int plk=0,pli=0,number,plpar,divisor,temp,par1,par2,curtime,i,z,x,y,simetrikos;
		printf("checking numbers in [%d,%d]\n",MINNUM,MAXNUM);
		for (number=MINNUM; number<=MAXNUM;number++)  //elegxos gia kathe arithmo number sto diastima MINNUM-MAXNUM
	{
		plpar=0;   //plithos paragonton tou ekastote arithmou
		par1=0;         //1os paragontas enos indresting semiprime aithmou                     
		temp = number ;	// temp h metabalomeni timi tou number meta apo diairesi tou me paragonta
		simetrikos = 0;	// o simetrikos arithmos tou par1 o opoios briskete pano apo tin tetrag riza tou number 
		for (divisor=2;divisor<=3 && divisor*divisor<=number && plpar<=MAXK ;divisor++) //diairoume ton temp me to 2 kai to 3 oso ginete      
		{																				
			while(temp%divisor==0) 
			{
				if (temp/divisor!=1) //apothikeusi simetrikou efoson den exei brethei idi
				{
					simetrikos = temp/divisor;	
					par1 = divisor;
				}	
				temp = temp/divisor;						
				plpar++;	//eyresi paragonta
			}	
		}
		for (divisor=6; (divisor-1)*(divisor-1)<=number && plpar<=MAXK ;  divisor+=6)	 //diairoyme me protoys arithmous 6n+1 6n-1 (n akeraios)
		{
			while (temp%(divisor-1)==0)        
				{
					if (temp/(divisor-1)!=1)  //apothikeusi simetrikou efoson den exei brethei idi
					{
						simetrikos = temp/(divisor-1);	
						par1 = divisor-1;
					}
					temp = temp /(divisor-1);
					plpar++;					//eyresi paragonta
				}
				while (temp%(divisor+1)==0)
				{
					if (temp/(divisor+1)!=1) //apothikeusi simetrikou efoson den exei brethei idi
					{
							simetrikos = temp/(divisor+1);
							par1 = divisor+1;
					}				
					temp = temp /(divisor+1);
					plpar++; //eyresi paragonta
										
				}		
		}
			if (temp!=1) plpar++; //an yparxei simetrikos ton metrame sto plithos paragonton
		if (plpar == 2 && simetrikos > par1 && simetrikos-par1<=simetrikos/100 ) // elegxos gia indresting semiprime number
			printf("%ld * %ld = %ld is an indresting semiprime\n",par1,simetrikos, number); 	
		if (plpar>=2 && plpar<=MAXK) plk = plk + 1; //plk to plithos ton k-almost numbers
		if (plpar==2) pli = pli + 1;		//pli to plithos ton semiprimes		
	}	
	printf("Found %d k-almost prime numbers (2<=k<=%d)\n",plk,MAXK); //tiposi ton k-almost
	printf("Found %d semiprimes\n\n",pli);  //tiposi ton semiprimes
	printf("checking %d random numbers\n", COMPUTATIONS);    //2o meros tis askisis
	curtime = time(NULL);   //curtime ta deyteropta poy exoyn perasei apo tis 1/1/1970
	srand((unsigned int) curtime);  //curtime to fitro tis rand
	for (i=1;i<=20;i++)  // elegxoume 20 tyxaioys arithmoys
	{
		plpar=0;  //plithos ton paragonton toy ekastote arithmou
		z= rand(); //z tixaios arithmos
		y= rand();// y tixaios arithmos
		x = ((y % 32768) + 1) * ((z % 32768) + 1) + 1;   //x o tixaios aritmos me basi ti sxesi tis ekfonisis
		temp = x;   // temp h metabalomeni timi tou x meta apo diairesi tou me paragonta
		for (divisor = 2;divisor<=3  && divisor*divisor<=x;divisor++) //diairoume ton temp me to 2 kai to 3 oso ginete 
		{
			while(temp%divisor == 0)
			{
				temp = temp/divisor; 
				plpar++; //eyresi paragonta
			}
		}
		for (divisor = 6 ; (divisor-1)*(divisor-1)<=x ; divisor+=6) //diairoyme me protoys arithmous 6n+1 6n-1 (n akeraios)
		{
			while(temp%(divisor-1) == 0)
			{
				temp = temp/(divisor-1);
				plpar++;  //eyresi paragonta
			}
			while(temp%(divisor+1) == 0)
			{
				temp = temp/(divisor+1);
				plpar++;  //eyresi paragonta
			}
		}
		if (temp!=1) plpar++;  //an yparxei simetrikos ton metrame sto plithos paragonton
		printf("%d is a %d-almost prime number\n",x,plpar); //tiposi apotelesmatos 
	}
}

