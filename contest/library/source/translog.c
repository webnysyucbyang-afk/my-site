/* Trnansitive Closure of a Directed Graph (logn iterations) */
#include <stdio.h>
#define  SIZE 50
/* Set the stack size to be greater than the default (4k bytes). */
/* This declaration must be done in the global data area.  */
extern unsigned _stklen = 30000U;

void matrix_add(int array[][SIZE],int record[][SIZE],int n)
{
   int i,j,k,temp[SIZE][SIZE];

     for(i=0;i<n;i++)
       for(j=0;j<n;j++)
  temp[i][j]=record[i][j];

     for(i=0;i<n;i++)
       for(j=0;j<n;j++)
  for(k=0;k<n;k++)
  {
     if(temp[i][j]==1)
     break;

     temp[i][j] |= array[i][k]&array[k][j];
  }

  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      array[i][j]=temp[i][j];
}

void transitive(int record[][SIZE],int array[][SIZE],int n)
 /* author: Kam-Fai Wong
    purpose: find the transitive closure of a directed graph
    record[][]: input matrix to represent a graph,unchanged
  0/1 matrix
    array[][]: output data,transitive closure of record[][]
        0/1 matrix
    n: # of nodes (vertices) in the graph
 */
{
  int i,j,k;

    for(i=0;i<n;i++)     /* copy data from record to array*/
      for(j=0;j<n;j++)
     array[i][j]=record[i][j];

    for(k=1;k<n;k*=2)    /* calculate log n time */
    matrix_add(array,record,n);

}

void main(void)
{
  int n;      /* # of nodes in the graph */
  int i,j;    /* index */
  int record[SIZE][SIZE]; /* input data */
  int array[SIZE][SIZE];  /* output data */
  FILE *in_file,*out_file;

  /* read input data */
  printf("*** Transitive Closure ***\n");
  in_file=fopen("trans.in","r");
  fscanf(in_file,"%d",&n);

    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
 fscanf(in_file,"%d",&record[i][j]);
  fclose(in_file);

  /* Transitive closure */
  transitive(record,array,n);

  /* write output data */
  out_file=fopen("trans.out","w");

    for(i=0;i<n;i++)
      {
       for(j=0;j<n;j++)
  fprintf(out_file,"%3d",array[i][j]);
  fprintf(out_file,"\n");
      }

  fclose(out_file);
  printf("\nPress any key to continue...");  //use it only on TC
  getch();
}
 /* test data format:
    input file name: trans.in
   The number on the first line is the number of nodes
   in the graph.
    sample input:
    5
    0 0 1 1 0
    0 0 1 0 0
    0 0 0 1 1
    0 0 0 0 1
    0 0 0 1 0
    output filename: trans.out
    sample output:
    0 0 1 1 1
    0 0 1 1 1
    0 0 0 1 1
    0 0 0 1 1
    0 0 0 1 1
 */