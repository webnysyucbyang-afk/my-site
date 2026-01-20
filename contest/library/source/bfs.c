/* Author:¶À¹Å­Z
   Purpose:Breadth-First Search of a directed graph
   */
   
#include <stdio.h>
#define SIZEN 50

void BFS(int a[SIZEN][SIZEN],int b[SIZEN],int n)
/*  a[][]: input matrix to represent a graph,not changed 0/1 matrix
    b[]: output data
        i: # of nodes(vertices) in the graph
        */
{
  int c[SIZEN]; /* node 0/1 */
  int d[SIZEN]; /* queue */
  int i,j; /* index */
  int queue_h; /* queue head */
  int queue_t; /* queue tail */
  int node_i; /* node index */
  for (i=0;i<n;i++)
    c[i]=0;
  for (i=0;i<n;i++)
    d[i]=0;
  queue_h=0;
  queue_t=1;
  node_i=0;
  b[0]=1;
  c[0]=1;
  d[0]=1;
  while (queue_h!=queue_t) {
    for (i=0;i<n;i++)
         if ((!c[i])&&(a[d[queue_h]-1][i])) {
           c[i]=1;
           d[queue_t]=i+1;
           queue_t++;
           node_i++;
           b[node_i]=i+1;
           }
         d[queue_h]=0;
         queue_h++;
    }
}

void main(void)
{
  int n; /* # of nodes in the graph */
  int i,j; /* index */
  int a[SIZEN][SIZEN]; /* input data */
  int b[SIZEN]; /* output data */
  FILE *in_file,*out_file; 
  printf("*** Breath_First_Search ***\n");
  /* read input data */
  in_file=fopen("bfs.in","r");
  fscanf(in_file,"%d",&n);
  for (i=0;i<n;i++)
    for (j=0;j<n;j++)
         fscanf(in_file,"%d",&a[i][j]);
  fclose(in_file);
  /* Breadth_First Search */
  BFS(a,b,n);
  /* write output data */
  out_file=fopen("bfs.out","w");
  for (i=0;i<n;i++)
    fprintf(out_file,"%3d",b[i]);
  fclose(out_file);
}
/*test data format
  input filename:bfs.in
sample input:
6
0 1 0 0 1 0
1 0 1 0 0 1
0 0 0 1 1 0
0 0 1 0 1 1
1 1 0 0 0 1
0 1 0 0 1 0

sample output (file bfs.out):
  1  2  5  3  6  4
*/  

/* Test : Jong-rong Shyy

   input :
   6
   0 1 0 0 0 1
   0 0 1 0 1 0
   0 0 0 1 0 0
   0 0 0 0 0 0
   0 0 0 0 0 0
   0 0 0 0 0 0

   output :
        1  2  6  3  5  4
*/
