#include <stdio.h>
#include <stdlib.h>

#define INFINITY 100000

int findJ(int number,int **mapaMATRIX,int x)
{
	int j=0;
	
	for(j=1;j<x;j++)
	{
		if(mapaMATRIX[0][j] == number)
		{
			return j;
			break;
		}
	}
	return -1;
}

int findI(int number,int **mapaMATRIX,int x)
{
	int i=0;

	for(i=1;i<x;i++)
	{
		if(mapaMATRIX[i][0] == number)
		{
			return i;
			break;
		}
	}
	return -1;
}

int algoritmus(int **matrix,int n,int source, int findThis,int *poleHciek, int pocetH, int *cestovnaMapa, int *indexCMapy, int urobit,int** princezne, int pocetP)
{
	int tempIndex = 0;
	int z;
	int cena = 0;
	int count = 1,temp,next,i,j,k;
	
	int *tempArray;
	tempArray = (int *)malloc(INFINITY*sizeof(int));
 	
	int **cost;
 	cost = (int**)malloc(n*sizeof(int*));
 	for(k=0;k<n;k++)
 		cost[k] = (int *)malloc(n*sizeof(int));
	
	int **info;
	info = (int**)malloc(n*sizeof(int*));
	for(k=0;k<n;k++)
		info[k] = (int *)malloc(3*sizeof(int));
	
	// 0 visited 0 / 1
	// 1 distance
	// 2 previous

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(matrix[i][j]!=0){
				cost[i][j]=matrix[i][j];
			}
			else cost[i][j]=INFINITY;
		}
	}

	
	for(i=0;i<n;i++)
	{
		info[i][0] = 0;
		info[i][1] = cost[source][i];
		info[i][2] = source;
	}
	
	info[source][1]=0;
	info[source][0]=1;
	 
	for(j=0;j<n-1;j++)
	{
		temp=INFINITY;
		
		for(i=0;i<n;i++)
		{
			if( info[i][1] < temp && info[i][0]==0  )
			{
				next=i;
				temp = info[i][1];
			}
		}

		info[next][0]=1;	

		for(i=0;i<n;i++)
		{
			if( info[i][0] == 0 )
				if( temp + cost[next][i] < info[i][1] ) 
				{
					info[i][1] = temp + cost[next][i];
					info[i][2] = next;
				}
		}
	}
 
	for(i=0;i<n;i++)
	{
		if(i==findThis && i != source)
		{
			if(urobit==1){
				tempArray[tempIndex] = i;
				tempIndex++;
			}
			j=i;
			while(1)
			{
				if(j==source)
				{
					break;
				}
				for(z=0;z<pocetH;z++){
					if(j==poleHciek[z]){
						cena+=2;
						z=0;
						break;
					}
					else continue;
				}

				if(z==pocetH)cena++;
				j = info[j][2];
				if(urobit==1){
					tempArray[tempIndex] = j;
					tempIndex++;
				}
			}
		}
	}
	
	if(urobit==1)
	{
		for(i=tempIndex-1;i>=0;i--){
			cestovnaMapa[*indexCMapy] = tempArray[i];
			*indexCMapy += 1;
		}
	}
	
	for(i=0;i<pocetP;i++)
	{
		if( info[princezne[i][1]][1]== INFINITY){
					free(tempArray);
					return -1;
		}
	}
	if( info[findThis][1] == INFINITY)
	{
		free(tempArray);
		return -1;
	}

 	for(k=0;k<n;k++)
 		free(cost[k]);
	free(cost);

	
	for(k=0;k<n;k++)
		free(info[k]);
	free(info);

	free(tempArray);
	return cena;
}

int* zachran_princezne(char **mapa, int n, int m, int t, int *dlzka_cesty)
{
	int cestaDraka = -1;
	
	// vlastnu generovaciu funkciu som neurobil lebo som to nepokladal pri zadani za dolezite
	// su tu len akoby rucne vypisane vsetky permutacie
	
	int perm5[120][5] = {   {1,2,3,4,5,}, {2,1,3,4,5,}, {3,1,2,4,5,}, {1,3,2,4,5,}, {2,3,1,4,5,},
							{3,2,1,4,5,}, {4,2,3,1,5,}, {2,4,3,1,5,}, {3,4,2,1,5,}, {4,3,2,1,5,},
							{2,3,4,1,5,}, {3,2,4,1,5,},	{4,1,3,2,5,}, {1,4,3,2,5,}, {3,4,1,2,5,},
							{4,3,1,2,5,}, {1,3,4,2,5,}, {3,1,4,2,5,}, {4,1,2,3,5,},	{1,4,2,3,5,},
							{2,4,1,3,5,}, {4,2,1,3,5,},	{1,2,4,3,5,}, {2,1,4,3,5,},	{5,1,2,3,4,},
							{1,5,2,3,4,}, {2,5,1,3,4,},	{5,2,1,3,4,}, {1,2,5,3,4,},	{2,1,5,3,4,},
							{3,1,2,5,4,}, {1,3,2,5,4,},	{2,3,1,5,4,}, {3,2,1,5,4,},	{1,2,3,5,4,},
							{2,1,3,5,4,}, {3,5,2,1,4,},	{5,3,2,1,4,}, {2,3,5,1,4,},	{3,2,5,1,4,},
							{5,2,3,1,4,}, {2,5,3,1,4,},	{3,5,1,2,4,}, {5,3,1,2,4,},	{1,3,5,2,4,},
							{3,1,5,2,4,}, {5,1,3,2,4,},	{1,5,3,2,4,}, {4,5,1,2,3,},	{5,4,1,2,3,},
							{1,4,5,2,3,}, {4,1,5,2,3,},	{5,1,4,2,3,}, {1,5,4,2,3,},	{2,5,1,4,3,},
							{5,2,1,4,3,}, {1,2,5,4,3,},	{2,1,5,4,3,}, {5,1,2,4,3,},	{1,5,2,4,3,},
							{2,4,1,5,3,}, {4,2,1,5,3,},	{1,2,4,5,3,}, {2,1,4,5,3,},	{4,1,2,5,3,},
							{1,4,2,5,3,}, {2,4,5,1,3,},	{4,2,5,1,3,}, {5,2,4,1,3,},	{2,5,4,1,3,},
							{4,5,2,1,3,}, {5,4,2,1,3,},	{3,4,5,1,2,}, {4,3,5,1,2,},	{5,3,4,1,2,},
							{3,5,4,1,2,}, {4,5,3,1,2,}, {5,4,3,1,2,}, {1,4,5,3,2,}, {4,1,5,3,2,},
							{5,1,4,3,2,}, {1,5,4,3,2,}, {4,5,1,3,2,}, {5,4,1,3,2,}, {1,3,5,4,2,},
							{3,1,5,4,2,}, {5,1,3,4,2,}, {1,5,3,4,2,}, {3,5,1,4,2,},	{5,3,1,4,2,},
							{1,3,4,5,2,}, {3,1,4,5,2,},	{4,1,3,5,2,}, {1,4,3,5,2,},	{3,4,1,5,2,},
							{4,3,1,5,2,}, {2,3,4,5,1,},	{3,2,4,5,1,}, {4,2,3,5,1,},	{2,4,3,5,1,},
							{3,4,2,5,1,}, {4,3,2,5,1,}, {5,3,4,2,1,}, {3,5,4,2,1,},	{4,5,3,2,1,},
							{5,4,3,2,1,}, {3,4,5,2,1,},	{4,3,5,2,1,}, {5,2,4,3,1,},	{2,5,4,3,1,},
							{4,5,2,3,1,}, {5,4,2,3,1,},	{2,4,5,3,1,}, {4,2,5,3,1,},	{5,2,3,4,1,},
							{2,5,3,4,1,}, {3,5,2,4,1,},	{5,3,2,4,1,}, {2,3,5,4,1,},	{3,2,5,4,1,}
	};
	
	int perm4[24][4]={	{1,2,3,4,},	{2,1,3,4,},	{3,1,2,4,},	{1,3,2,4,},
						{2,3,1,4,},	{3,2,1,4,},	{4,2,3,1,},	{2,4,3,1,},
						{3,4,2,1,},	{4,3,2,1,},	{2,3,4,1,},	{3,2,4,1,},
						{4,1,3,2,},	{1,4,3,2,},	{3,4,1,2,},	{4,3,1,2,},
						{1,3,4,2,},	{3,1,4,2,},	{4,1,2,3,},	{1,4,2,3,},
						{2,4,1,3,},	{4,2,1,3,}, {1,2,4,3,},	{2,1,4,3,}
	};
	
	int perm3[6][3]={	{1,2,3,}, {2,1,3,},	{3,1,2,},
						{1,3,2,}, {2,3,1,},	{3,2,1,}
	};
	
	int perm2[2][2]={	{1,2,},	{2,1,}
	};
	
	int perm1 = 1;
	
	int i;
	int j;
	int x;
	int k;
	int f;
	int drak;
	int helper;
	int pom1, pom2;
	int **mapaExtra;
	int **mapaMATRIX;
	int **mapaMATRIXfinal;
	int *poleHciek;
	int *cestovnaMapa;
	int indexCMapy = 0;
	
	int **prin;
	prin = (int**)malloc(5*sizeof(int*));
	for(i=0;i<5;i++)
		prin[i] = (int*)malloc(2*sizeof(int));
	
	mapaExtra = (int**)malloc(n*sizeof(int*));
	for(i=0; i<n; i++){
	 	mapaExtra[i] = (int*)malloc(m*sizeof(int));
	}
	
	// vytvorenie IDciek
	int c = 200000;
	int h = 100000;
	int d = 50000;
	int p = 60000;
	int counter = 0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{		
			if(mapa[i][j]=='C')
			{
				mapaExtra[i][j]=c;
				c++;
			}	
			if(mapa[i][j]=='H')
			{
				mapaExtra[i][j]=h;
				h++;
			}
			if(mapa[i][j]=='N')
			{
				mapaExtra[i][j]=-1;
			}
			if(mapa[i][j]=='D')
			{
				mapaExtra[i][j]=d;
				d++;
			}
			if(mapa[i][j]=='P')
			{
				mapaExtra[i][j]=p;
				p++;
			}
		}
	}
	
	// osetrenie okrajovych situacii, ked je viac ako jeden drak, viac ako 5 princezien, pripadne ziadna
	// ak nie je ani jedno H ani jedna P, ani DRAK ani C
	if(d>50001 || d==50000)
	{
		printf("Neplatna mapa\n");
		*dlzka_cesty = -1;
		return NULL;
	}
	if(p>60005 || p==60000)	
	{
		printf("Neplatna mapa\n");
		*dlzka_cesty = -1;
		return NULL;
	}if(c == 200000 && h == 100000 && d==50000 && p==60000)
	{
		printf("Neplatna mapa\n");
		*dlzka_cesty = -1;
		return NULL;
	}
	
	// vytvorenie celkoveho poctu prvkov pre maticu + 1, pre pomocny riadok a stlpec ktory budem vyuzivat na lepsiu orientaciu
	// idcka som zvolil rozdielne preto aby som pri porovnavani / modulovani vedel zistit o aky druh policka sa jedna a nasledne
	// s nim korektne pracovat
	x = 0;
	x += (c%200000);
	x += (h%100000);
	x += (d%50000);
	x += (p%60000);
	x++;	
	
	// v pripade, ze vsetko prebehlo v poriadku, allocujeme si pole na maticu 
	mapaMATRIX = (int**)malloc(x*sizeof(int*));
	for(i=0; i<x; i++){
	 	mapaMATRIX[i] = (int*)malloc(x*sizeof(int));
	}
	
	// vyplnime ju nulami aby tam nahodou nevznikali problemy s neinicializovanymi polickami, konkretne jedno policko uplne vlavo hore, ktore tam bude akoby navyse
	for(i=0;i<x;i++)
	{
		for(j=0;j<x;j++)
		{
			mapaMATRIX[i][j]=0;
		}
	}
	
	// teraz urobím jednoduché pole ktoré priradí riadky a stlpce danej pomocnej matici
	// helper sluzi na to aby dosiahol pocet prvkov a 
	// k ako ratacka pomaha na to aby nam urcila spravny index
	k = 1;
	helper = 0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			
			if( mapaExtra[i][j] >= 0)
			{	
				mapaMATRIX[k][0] = mapaExtra[i][j];
				mapaMATRIX[0][k] = mapaExtra[i][j];	
				k++;
				helper++;
			}
			
			if(x==helper)
			{
				break;
			}
		}
	}

	// 2 pomocne premenne, kde si budeme ukladat I a J indexy pri vyplnani matice zatial iba jednotkami
	pom1=0;
	pom2=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if( i==n-1 && j==m-1)
			{
				//hore
				if(mapaExtra[i-1][j]>0 && mapaExtra[i][j]>0)
				{
					pom1 = findI(mapaExtra[i-1][j],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					
					//printf("1 %d 2 %d\n",pom1,pom2);
					if(pom1!=-1 && pom2!=-1)
					{	
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					};

				}
				
				//dolava
				if(j>0 && mapaExtra[i][j-1]>0 && mapaExtra[i][j]>0)
				{
					pom1 = findI(mapaExtra[i][j-1],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					//printf("%d -- %d\n",mapaExtra[i][j-1],mapaExtra[i][j]);
					if(pom1!=-1 && pom2!=-1)
					{
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					}	
				}
			}


			if( i == 0)
			{
				//doprava
				if(mapaExtra[i][j+1]>0 && mapaExtra[i][j]>0 && j!=m-1) 
				{
				    pom1 = findI(mapaExtra[i][j],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j+1],mapaMATRIX,x);
					if(pom1!=-1 && pom2!=-1)
					{	
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					}
				}
				
				//dole
				if(mapaExtra[i+1][j]>0 && mapaExtra[i][j]>0 && i!=n-1) 
				{
					pom1 = findI(mapaExtra[i+1][j],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					if(pom1!=-1 && pom2!=-1)
					{
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					};
				}
				
			}

			if(i>0 && i<n-1)
			{
				//hore
				if(mapaExtra[i-1][j]>0 && mapaExtra[i][j]>0)
				{
					pom1 = findI(mapaExtra[i-1][j],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					if(pom1!=-1 && pom2!=-1)
					{	
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					};

				}
				
				// doprava
				if(j<m-1 && mapaExtra[i][j+1]>0 && mapaExtra[i][j]>0)
				{
					pom1 = findI(mapaExtra[i][j+1],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					if(pom1!=-1 && pom2!=-1)
					{
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					};
				}
				
				// dolava
				if(j>0 && mapaExtra[i][j-1]>0 && mapaExtra[i][j]>0)
				{
					pom1 = findI(mapaExtra[i][j-1],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					if(pom1!=-1 && pom2!=-1)
					{
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					}	
				}
				
				// dole
				if ( i<n-1 && mapaExtra[i+1][j]>0 && mapaExtra[i][j]>0 )
				{
				    pom1 = findI(mapaExtra[i+1][j],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					if(pom1!=-1 && pom2!=-1)
					{
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					};
				}
			}

			if(i==n-1)
			{
				// hore
				if(mapaExtra[i-1][j]>0 && mapaExtra[i][j]>0)
				{
					pom1 = findI(mapaExtra[i-1][j],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					if(pom1!=-1 && pom2!=-1)
					{
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					};
				}
				
				//right
				if(j<m-1 && mapaExtra[i][j+1]>0 && mapaExtra[i][j]>0)
				{
					pom1 = findI(mapaExtra[i][j+1],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					if(pom1!=-1 && pom2!=-1)
					{
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					};
				}
				
				// dolava
				if(j>0 && mapaExtra[i][j-1]>0 && mapaExtra[i][j]>0)
				{
					
					pom1 = findI(mapaExtra[i][j-1],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					
					if(pom1!=-1 && pom2!=-1)
					{
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					};
				}
			}

			if(j==0)
			{
				// dole
				if ( i<n-1 && mapaExtra[i+1][j]>0 && mapaExtra[i][j]>0 )
				{
				    pom1 = findI(mapaExtra[i+1][j],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					if(pom1!=-1 && pom2!=-1)
					{
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					};
				}
				
				//right
				if(j<m-1 && mapaExtra[i][j+1]>0 && mapaExtra[i][j]>0 && j<m-1)
				{
					pom1 = findI(mapaExtra[i][j+1],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					if(pom1!=-1 && pom2!=-1)
					{
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					};
				}
				
				// dolava
				if(j>0 && mapaExtra[i][j-1]>0 && mapaExtra[i][j]>0 && j>=1)
				{
					
					pom1 = findI(mapaExtra[i][j-1],mapaMATRIX,x);
					pom2 = findJ(mapaExtra[i][j],mapaMATRIX,x);
					if(pom1!=-1 && pom2!=-1)
					{
						mapaMATRIX[pom1][pom2]=1;
						mapaMATRIX[pom2][pom1]=1;
					};
				}
				
			}
		}
	}

	for(j=0;j<x;j++)
	{
		if(mapaMATRIX[j][0]>=100000 && mapaMATRIX[j][0]<200000)
		{
			for(i=1;i<x;i++)
			{
				mapaMATRIX[j][i]*=2;
			}
		}
	}
	
	poleHciek = (int*)malloc(h*sizeof(int));
	f = 0;
	for(i=0;i<x;i++)
	{
		for(j=0;j<x;j++)
		{
			if(mapaMATRIX[i][j]==50000){
				if(i==0)drak = j-1;
			}
			if(mapaMATRIX[i][j]>=60000 && mapaMATRIX[i][j]<=60004)
			{
				if(mapaMATRIX[i][j]==60000 && i==0){
					prin[0][0]=1;
					prin[0][1]=j-1;
				}
				else if (prin[0][0]!=1)prin[0][0]=0;
				
				if(mapaMATRIX[i][j]==60001 && i==0)
				{
					prin[1][0]=1;
					prin[1][1]=j-1;
				}
				else if (prin[1][0]!=1)prin[1][0]=0;
				
				if(mapaMATRIX[i][j]==60002 && i==0){
					prin[2][0]=1;
					prin[2][1]=j-1;
				}
				else if (prin[2][0]!=1)prin[2][0]=0;
				
				if(mapaMATRIX[i][j]==60003 && i==0)
				{
					prin[3][0]=1;
					prin[3][1]=j-1;
				}
				else if (prin[3][0]!=1)prin[3][0]=0;
				
				if(mapaMATRIX[i][j]==60004 && i==0)
				{
					prin[4][0]=1;
					prin[4][1]=j-1;
				}
				else if (prin[4][0]!=1)prin[4][0]=0;
			}
		
			if(mapaMATRIX[i][j]>=100000 && mapaMATRIX[i][j]<=100000+(h%100000) && i==0)
			{
				poleHciek[f]=j-1;
				f++;
			}
		}
	}
	
	mapaMATRIXfinal = (int**)malloc( (x-1)*sizeof(int*));
	for(i=0; i<x-1; i++){
	 	mapaMATRIXfinal[i] = (int*)malloc( (x-1)*sizeof(int));
	}
	
	for(i=0;i<(x-1);i++)
	{
		for(j=0;j<(x-1);j++)
		{
			mapaMATRIXfinal[i][j]=mapaMATRIX[i+1][j+1];
		}
	}
		
	cestovnaMapa = (int *)malloc(INFINITY*sizeof(int));
	for(i=0;i<INFINITY;i++)
		cestovnaMapa[i]=-2;
	
	//printf("Hladanie draka.\n");
	cestaDraka = algoritmus(mapaMATRIXfinal,x-1,0,drak,poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
	if(cestaDraka==-1)
	{
		printf("Nedostupnost draka / princezien alebo iny problem. Vraciam NULL na pointer pola a dlzku_cesty nastavujem na -1.\n");
		*dlzka_cesty = -1;
		return NULL;
	}
	cestaDraka += 1;
	if(cestaDraka>t)
	{
		printf("Nestihol som draka. Preto nema zmysel zachranovat princezne.\nVraciam NULL na pointer pola a dlzku_cesty nastavujem na -1. \n");
		*dlzka_cesty = -1;
		return NULL;
	}
	if(p%60000==5)
	{
		for(i=0;i<120;i++)
		{
			for(j=0;j<5;j++)
			{
				if( perm5[i][j]==1 && prin[0][0]==1 && prin[0][1]!=-1 )perm5[i][j]=prin[0][1];
				if( perm5[i][j]==2 && prin[1][0]==1 && prin[1][1]!=-1 )perm5[i][j]=prin[1][1];
				if( perm5[i][j]==3 && prin[2][0]==1 && prin[2][1]!=-1 )perm5[i][j]=prin[2][1];
				if( perm5[i][j]==4 && prin[3][0]==1 && prin[3][1]!=-1 )perm5[i][j]=prin[3][1];
				if( perm5[i][j]==5 && prin[4][0]==1 && prin[4][1]!=-1 )perm5[i][j]=prin[4][1];
			}
		}
		
		int minCesta = INFINITY;
		int tempCesta = 0;
		int pom = -1;
		
		for(i=0;i<120;i++)
		{
			tempCesta = 0;
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,drak,perm5[i][0],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);		
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm5[i][0],perm5[i][1],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm5[i][1],perm5[i][2],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm5[i][2],perm5[i][3],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm5[i][3],perm5[i][4],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);
			if(cestaDraka + tempCesta < minCesta){
				minCesta=cestaDraka+tempCesta;
				pom = i;
			}
		}
		
		algoritmus(mapaMATRIXfinal,x-1,drak,perm5[pom][0],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);		
		algoritmus(mapaMATRIXfinal,x-1,perm5[pom][0],perm5[pom][1],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
		algoritmus(mapaMATRIXfinal,x-1,perm5[pom][1],perm5[pom][2],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
		algoritmus(mapaMATRIXfinal,x-1,perm5[pom][2],perm5[pom][3],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
		algoritmus(mapaMATRIXfinal,x-1,perm5[pom][3],perm5[pom][4],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
		
		*dlzka_cesty = minCesta;
		
	}
	else if(p%60000==4)
	{
		for(i=0;i<24;i++)
		{
			for(j=0;j<4;j++)
			{
				if( perm4[i][j]==1 && prin[0][0]==1 && prin[0][1]!=-1 )perm4[i][j]=prin[0][1];
				if( perm4[i][j]==2 && prin[1][0]==1 && prin[1][1]!=-1 )perm4[i][j]=prin[1][1];
				if( perm4[i][j]==3 && prin[2][0]==1 && prin[2][1]!=-1 )perm4[i][j]=prin[2][1];
				if( perm4[i][j]==4 && prin[3][0]==1 && prin[3][1]!=-1 )perm4[i][j]=prin[3][1];
			}
		}
		
		int minCesta = INFINITY;
		int tempCesta = 0;
		int pom = -1;
		
		for(i=0;i<24;i++)
		{
			tempCesta = 0;
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,drak,perm4[i][0],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);		
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm4[i][0],perm4[i][1],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm4[i][1],perm4[i][2],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm4[i][2],perm4[i][3],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);
			if(cestaDraka + tempCesta < minCesta){
				minCesta=cestaDraka+tempCesta;
				pom = i;
			}
		}
		
		tempCesta += algoritmus(mapaMATRIXfinal,x-1,drak,perm4[pom][0],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);		
		tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm4[pom][0],perm4[pom][1],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
		tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm4[pom][1],perm4[pom][2],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
		tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm4[pom][2],perm4[pom][3],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
		
		*dlzka_cesty = minCesta;
	}
	else if(p%60000==3)
	{
		for(i=0;i<6;i++)
		{
			for(j=0;j<3;j++)
			{
				if( perm3[i][j]==1 && prin[0][0]==1 && prin[0][1]!=-1 )perm3[i][j]=prin[0][1];
				if( perm3[i][j]==2 && prin[1][0]==1 && prin[1][1]!=-1 )perm3[i][j]=prin[1][1];
				if( perm3[i][j]==3 && prin[2][0]==1 && prin[2][1]!=-1 )perm3[i][j]=prin[2][1];
			}
		}
		
		int minCesta = INFINITY;
		int tempCesta = 0;
		int pom = -1;
		
		for(i=0;i<6;i++)
		{
			tempCesta = 0;
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,drak,perm3[i][0],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);		
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm3[i][0],perm3[i][1],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm3[i][1],perm3[i][2],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);
			if(cestaDraka + tempCesta < minCesta){
				minCesta=cestaDraka+tempCesta;
				pom = i;
			}
		}
				
		algoritmus(mapaMATRIXfinal,x-1,drak,perm3[pom][0],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);		
		algoritmus(mapaMATRIXfinal,x-1,perm3[pom][0],perm3[pom][1],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
		algoritmus(mapaMATRIXfinal,x-1,perm3[pom][1],perm3[pom][2],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
		
		*dlzka_cesty = minCesta;

	}
	else if(p%60000==2)
	{
		for(i=0;i<2;i++)
		{
			for(j=0;j<2;j++)
			{
				if( perm2[i][j]==1 && prin[0][0]==1 && prin[0][1]!=-1 )perm2[i][j]=prin[0][1];
				if( perm2[i][j]==2 && prin[1][0]==1 && prin[1][1]!=-1 )perm2[i][j]=prin[1][1];
			}
		}
		
		int minCesta = INFINITY;
		int tempCesta = 0;
		int pom = -1;
		
		for(i=0;i<2;i++)
		{
			tempCesta = 0;
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,drak,perm2[i][0],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);		
			tempCesta += algoritmus(mapaMATRIXfinal,x-1,perm2[i][0],perm2[i][1],poleHciek,h%100000,cestovnaMapa,&indexCMapy,0,prin,p%60000);
			if(cestaDraka + tempCesta < minCesta){
				minCesta=cestaDraka+tempCesta;
				pom = i;
			}
		}
		
		algoritmus(mapaMATRIXfinal,x-1,drak,perm2[pom][0],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
		algoritmus(mapaMATRIXfinal,x-1,perm2[pom][0],perm2[pom][1],poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);
		*dlzka_cesty = minCesta;
	}
	else if(p%60000==1)
	{
		if( perm1==1 && prin[0][0]==1 && prin[0][1]!=-1 )perm1=prin[0][1];
	
		
		int minCesta = INFINITY;
		int tempCesta = 0;
		int pom = -1;
		
		tempCesta = 0;
		tempCesta += algoritmus(mapaMATRIXfinal,x-1,drak,perm1,poleHciek,h%100000,cestovnaMapa,&indexCMapy,1,prin,p%60000);		
		if(cestaDraka + tempCesta < minCesta)
		{
			minCesta=cestaDraka+tempCesta;
			pom = i;
		}
		
		*dlzka_cesty = minCesta;
	}
	int pocetHvMape = 0;
	k=0;
	int *cesta;
	cesta = (int*)malloc(INFINITY*sizeof(int));
	int ii,jj;
	int temporary = -1;
	for(i=0;i<INFINITY;i++)
	{
		if(cestovnaMapa[i]==-2)break;
		
		if( cestovnaMapa[i+1]!=-2 )
		{
			
			if(cestovnaMapa[i+1]==cestovnaMapa[i])
			{
				cestovnaMapa[i+1]=-1;
			}
		}
		if(cestovnaMapa[i]<0)continue;
		else
		{

			for(ii=0;ii<n;ii++)
			{
				for(jj=0;jj<m;jj++)
				{
					if( mapaExtra[ii][jj] >= 0){
						temporary++;
						if( temporary == cestovnaMapa[i] )
						{
							if(mapaExtra[ii][jj]>=100000 && mapaExtra[ii][jj]<200000)*dlzka_cesty -= 1;
							cesta[k] = jj;
							k++;
							cesta[k] = ii;
							k++;
							jj=m-1;
							ii=n-1;
						}
					}
				}
			}
			
			temporary = -1;
		} 
	}

	free(cestovnaMapa);
	
	for(i=0;i<x-1;i++)
		free(mapaMATRIXfinal[i]);
	free(mapaMATRIXfinal);

	for(i=0; i<x; i++){
	 	free(mapaMATRIX[i]);
	}
	free(mapaMATRIX);
	
	for(i=0; i<n; i++){
	 	free(mapaExtra[i]);
	}
	free(mapaExtra);
	
	return cesta;
}

int main()
{
	char **mapa;
	int i, test, dlzka_cesty, cas, *cesta;
	int n=0, m=0, t=0;
	FILE* f;
	while(1){
		printf("Zadajte cislo testu (0 ukonci program):\n");
		scanf("%d",&test);
		dlzka_cesty = 0;
		n=m=t=0;
		switch(test){
			case 0://ukonci program
				return 0;
			case 1://nacitanie mapy zo suboru
				f=fopen("test.txt","r");
				if(f)
					fscanf(f, "%d %d %d", &n, &m, &t);
				else
					continue;
				mapa = (char**)malloc(n*sizeof(char*));
				for(i=0; i<n; i++){
					mapa[i] = (char*)malloc(m*sizeof(char));
					int j;
					
					for (j=0; j<m; j++)
					{
						char policko = fgetc(f);
						if(policko == '\n') policko = fgetc(f);
						mapa[i][j] = policko;
					}
				}
				fclose(f);
				cesta = zachran_princezne(mapa, n, m, t, &dlzka_cesty);
				break;
			case 2://nacitanie preddefinovanej mapy
				n = 10;
				m = 10;
				t = 12;
				mapa = (char**)malloc(n*sizeof(char*));
				mapa[0]="CCHCNHCCHN";
				mapa[1]="NNCCCHHCCC";
				mapa[2]="DNCCNNHHHC";
				mapa[3]="CHHHCCCCCC";
				mapa[4]="CCCCCNHHHH";
				mapa[5]="PCHCCCNNNN";
				mapa[6]="NNNNNHCCCC";
				mapa[7]="CCCCCPCCCC";
				mapa[8]="CCCNNHHHHH";
				mapa[9]="HHHPCCCCCC";
				cesta = zachran_princezne(mapa, n, m, t, &dlzka_cesty);
				break;
			case 3: //pridajte vlastne testovacie vzorky
				printf("Zadaj cislo podtestu\n");
				int cisloTestu = 0;
				scanf("%d",&cisloTestu);
				if(cisloTestu==1)f=fopen("testovanieVlastne1.txt","r");
				else if(cisloTestu==2)f=fopen("testovanieVlastne2.txt","r");
				else if(cisloTestu==3)f=fopen("testovanieVlastne3.txt","r");
				else if(cisloTestu==4)f=fopen("testovanieVlastne4.txt","r");
				else if(cisloTestu==5)f=fopen("testovanieVlastne5.txt","r");
				else if(cisloTestu==6)f=fopen("testovanieVlastne6.txt","r");
				else if(cisloTestu==7)f=fopen("testovanieVlastne7.txt","r");
				else if(cisloTestu==8)f=fopen("testovanieVlastne8.txt","r");
				else if(cisloTestu==9)f=fopen("testovanieVlastne9.txt","r");
				else if(cisloTestu==10)f=fopen("testovanieVlastne10.txt","r");
				else f=fopen("testovanieVlastne1.txt","r");
				if(f)
					fscanf(f, "%d %d %d", &n, &m, &t);
				else
					continue;
				mapa = (char**)malloc(n*sizeof(char*));
				for(i=0; i<n; i++){
					mapa[i] = (char*)malloc(m*sizeof(char));
					int j;
					
					for (j=0; j<m; j++)
					{
						char policko = fgetc(f);
						if(policko == '\n') policko = fgetc(f);
						mapa[i][j] = policko;
					}
				}
				fclose(f);
				cesta = zachran_princezne(mapa, n, m, t, &dlzka_cesty);
				break;
			default:
				continue;
		}
		cas = 0;
		for(i=0; i<dlzka_cesty; i++){
			printf("%d %d\n", cesta[i*2], cesta[i*2+1]);
			if(mapa[cesta[i*2+1]][cesta[i*2]] == 'H')
				cas+=2;
			else
				cas+=1;
			if(mapa[cesta[i*2+1]][cesta[i*2]] == 'D' && cas > t)
				printf("Nestihol si zabit draka!\n");
			if(mapa[cesta[i*2+1]][cesta[i*2]] == 'N')
				printf("Prechod cez nepriechodnu prekazku!\n");
			if(i>0 && abs(cesta[i*2+1]-cesta[(i-1)*2+1])+abs(cesta[i*2]-cesta[(i-1)*2])>1)
				printf("Neplatny posun Popolvara!\n");
		}
		printf("%d\n",cas);
		free(cesta);
		//for(i=0; i<n; i++){
		//	free(mapa[i]);
		//}
		//free(mapa);
	}
	return 0;
}
