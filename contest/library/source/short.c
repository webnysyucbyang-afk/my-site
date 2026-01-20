/*
  Single source shortest path in a graph
  Author:  林嵩慶
  DATE:      96/11/05
*/

#include <stdio.h>

#define INF       1000
#define MAXNODE   7          //maximum number of nodes
#define MEMBER    1
#define NONMEMBER 0

void shortpath(int weight[][MAXNODE],int s,int t,int *pd,int precede[],int n)
/*
    weight[][]  輸入路徑的資料
                如果兩點不通的話,以INF表示
    s           起點
    t           終點
    *pd         傳回路徑長
    precede[]   傳回所走的路
    n           所需計算的nodes數
*/
{
  int i,j,perm[MAXNODE],distance[MAXNODE];
  int smalldist,current,dc,k,stack[MAXNODE],index;
  long newdist;

  for(i=0;i<n;i++)
  {
    perm[i]=NONMEMBER;
    distance[i]=INF;
  }

  perm[s]=MEMBER;
  distance[s]=0;
  current=s;

  while(current!=t)
  {
    smalldist=INF;
    dc=distance[current];
    for(i=0;i<n;i++)
      if(perm[i]==NONMEMBER)
      {
 newdist=dc+(long)weight[current][i];
 if(newdist<distance[i])
 {
    distance[i]=(int)newdist;
    precede[i]=current;
 }
 if(distance[i]<smalldist)
 {
   smalldist=distance[i];
   k=i;
 }
      }
      current=k;
      perm[current]=MEMBER;
  }
  *pd=distance[t];

  //求出所經過的路徑
  i=0;
  while(t!=s)
  {
     stack[i++]=t;
     t=precede[t];
  }
  stack[i++]=s;

  index=0;
  for(j=i-1;j>=0;j--)
    precede[index++]=stack[j];

  for(i=index;i<n;i++)
    precede[i]=0;
}

void main(void)
{
  int data[MAXNODE][MAXNODE];
  int PathWeight,path[MAXNODE];
  int i,j,start,end,n;
  FILE *fp;

  fp=fopen("short.in","r");

  fscanf(fp,"%d",&n);

  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      fscanf(fp,"%d",&data[i][j]);

  start=0;
  end=5;

  shortpath(data,start,end,&PathWeight,path,n);
  printf("long = %d\n",PathWeight);

  for(i=0;path[i]!=end;i++)
    printf("%d ",path[i]);

    printf("%d\n",path[i]);

}
/*
  input file:short.in
    6
    0 28 8 1000 9 80
    1000 0 6 7 6 1 
    8 1000 0 1 3 82
    9 5 1000 0 9 1000
    1000 9 9 9 0 19 
    1000 1000 1000 9 9 0

  output:
    long = 15
    0 2 3 1 5
*/