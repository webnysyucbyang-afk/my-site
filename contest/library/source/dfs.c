/* Author:¶À¹Å­Z
   Purpose:Depth-First Search of a directed graph
*/
#include <stdio.h>
#define SIZEN 50

void DFS(int a[SIZEN][SIZEN],int b[SIZEN],int n)
/*  a[][]: input matrix to represent a graph,not changed 0/1 matrix
    b[]: output data
    n: # of nodes(vertices) in the graph
*/
{
  int c[SIZEN]; /* node 0/1 */
  int d[SIZEN]; /* stack */
  int i,j; /* index */
  int key; 
  int stack_i; /* stack index */
  int node_i; /* node index */
  for (i=0;i<n;i++)
    c[i]=0;
  for (i=0;i<n;i++)
    d[i]=0;
  stack_i=0;
  node_i=0;
  b[0]=1;
  c[0]=1;
  d[0]=1;
  while (d[0]!=NULL) {
    key=1;
    i=1;
    do {
         if ((a[d[stack_i]-1][i]==1)&&(c[i]==0)) {
           c[i]=1;
           node_i++;
           b[node_i]=i+1;
           stack_i++;
           d[stack_i]=i+1;
           key=0;
           }
           else
                i++;
         }
    while ((i<n)&&(key));
    if (i==n) {
         d[stack_i]=0;
         stack_i--;
         }
    }
}

void main(void)
{
  int n; /* # of nodes in the graph */
  int i,j; /* index */
  int a[SIZEN][SIZEN]; /* input data */
  int b[SIZEN]; /* output data */
  FILE *in_file,*out_file; 
  printf("*** Depth_First_Search ***\n");
  /* read input data */
  in_file=fopen("dfs.in","r");
  fscanf(in_file,"%d",&n);
  for (i=0;i<n;i++)
    for (j=0;j<n;j++)
      fscanf(in_file,"%d",&a[i][j]);
  fclose(in_file);
  /* Depth_First Search */
  DFS(a,b,n);
  /* write output data */
  out_file=fopen("dfs.out","w");
  for (i=0;i<n;i++) 
    fprintf(out_file,"%3d",b[i]);
  fclose(out_file);
  printf("\nPress any key to continue...");
}
/* test data format
   input filename:dfs.in
sample input:
6
0 1 0 0 1 0
1 0 1 0 0 1
0 0 0 1 1 0
0 0 1 0 1 1
1 1 0 0 0 1
0 1 0 0 1 0

sample output (file dfs.out):
    1    2    3    4    5    6
*/    

/* Test : Jong-rong Shyy

   Input :
   6
   0 1 1 0 0 0
   0 0 0 1 1 0
   0 0 0 0 0 1
   0 0 0 0 0 0
   0 0 0 0 0 0
   0 0 0 0 0 0

   Output :
        1  2  4  5  3  6
*/
