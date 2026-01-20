/* topological sorting (ordering) on an acyclic digraph 拓樸排序 */
/* 作者 : 黃嘉茂 */
#include <stdio.h>
#define SIZEN 50
/* Function topo 用來找任一組拓樸排序 
   topo_number topo_number2 用來找共有幾組拓樸排序 */
void topo_number2(int a[SIZEN][SIZEN],int b[SIZEN],int &s,int n)
/*  a[][]: input matrix to represent a graph,not changed 0/1 matrix
    b[]: 存放走到那...
    n: # of nodes(vertices) in the graph
    s: 共有幾組拓樸排序    
*/
{
  int i,j,k;
  int c[SIZEN];
  for (i=0;i<n;i++)
    c[i]=b[i];
  for (i=0;i<n;i++) {
    if (b[i]==0) {
	 c[i]=-1;

	 for (k=0,j=0;j<n;j++)
	   if (c[j]==-1)
		k++;
	 if (k==n) {
	   s++;
	   }

	 for (j=0;j<n;j++)
	   if (a[i][j])
		c[j]--;
	 topo_number2(a,c,s,n);
	 }
    }
}

void topo_number(int a[SIZEN][SIZEN],int &s,int n)
/* 同 Function topo_number2 */
{
  int i,j;
  int b[SIZEN];
  for (i=0;i<n;i++)
    b[i]=0;
  for (i=0;i<n;i++)
    for (j=0;j<n;j++)
	 if (a[j][i])
	b[i]++;
  topo_number2(a,b,s,n);
}

void topo(int a[SIZEN][SIZEN],int b[SIZEN],int n)
/*  a[][]: input matrix to represent a graph,not changed 0/1 matrix
    b[]: output data
    n: # of nodes(vertices) in the graph
*/
{
  int count[SIZEN];
  int i,j;
  int node_i=0;
  for (i=0;i<n;i++)
    count[i]=0;
  for (i=0;i<n;i++)
    for (j=0;j<n;j++)
	 if (a[j][i])
	count[i]++;
  for (i=0;i<n;i++)
    b[i]=0;
  while (node_i<n) {
    for (i=0;i<n;i++)
	 if (!count[i]) {
	b[node_i]=i+1;
	count[i]=-1;
	node_i++;
	for (j=0;j<n;j++)
	  if (a[i][j])
	    count[j]--;
	 }
    }
}

void main(void)
{
  int n;
  int i,j;
  int a[SIZEN][SIZEN];
  int b[SIZEN];
  int s=0;
  FILE *in_file,*out_file;
  /* read input data */
  printf("Topo Sort\n");
  in_file=fopen("topo.in","r");
  fscanf(in_file,"%d",&n);
  for (i=0;i<n;i++)
    for (j=0;j<n;j++)
	 fscanf(in_file,"%d",&a[i][j]);
  fclose(in_file);
  topo(a,b,n);
  topo_number(a,s,n);
  out_file=fopen("topo.out","w");
  for (i=0;i<n;i++)
    fprintf(out_file,"%3d",b[i]);
  fprintf(out_file,"\n");
  fprintf(out_file,"%d",s);
  printf("\nEnd Topo Sort....OOXX");
}
/*test data format
  input filename:topo.in
  sample input:
      4             
      0 1 1 0
      0 0 0 1
      0 0 0 0
      0 0 0 0

  sample output (file topo.out) :
      1  2  3  4
      3
*/  

/* Test : Jong-rong

   Input :
   6
   0 0 1 0 0 0
   0 0 1 0 0 0
   0 0 0 1 0 0
   0 0 0 0 1 1
   0 0 0 0 0 0
   0 0 0 0 0 0

   Output :
   1 2 3 4 5 6
   4
*/
