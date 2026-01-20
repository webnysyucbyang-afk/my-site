/* Transitive Closure of a Directed Graph (n iterations) */
#include <stdio.h>
#define SIZEN 50
/* Set the stack size to be greater than the default (4k bytes). */
/* This declaration must be done in the global data area.  */
extern unsigned _stklen = 30000U;

void transitive_closure(int a[SIZEN][SIZEN], int b[SIZEN][SIZEN], int n)
/* author: Chang-Biau Yang
   purpose: find the transitive closure of a directed graph
   a[][]: input matrix to represent a graph, not changed
	  0/1 matrix
   b[][]: output data, transitive closure of a[][]
	  0/1 matrix
   n: # of nodes (vertices) in the graph
*/
{
   int h,i,j,k;    /* index */
   int c[SIZEN][SIZEN];   /* temporary storage */

   if (n==0)     /* no elements */
      return;
   for (i=0; i<n; i++)   /* copy data from a[][] to b[][] */
      for (j=0; j<n; j++)
	  b[i][j]=a[i][j];
   /* transitive closure */
   for (h=0; h<n; h++) {     /* calculate n times */
      /* similar to matrix multiplication  + --> or,  * --> and */
      for (i=0; i<n; i++)   /* calculate for each node */
	 for (j=0; j<n; j++) {
	    c[i][j]=b[i][j];   /* initial value */
	    for (k=0; k<n; k++)
	       c[i][j] = c[i][j] || (b[i][k] && b[k][j]);
	 }
      for (i=0; i<n; i++)   /* copy data from c[][] to b[][] */
	 for (j=0; j<n; j++)
	    b[i][j]=c[i][j];
   }
}    /* end of transitive_closure() */

void main(void)
{  int n;     /* # of nodes in the graph */
   int i,j;     /* index */
   int a[SIZEN][SIZEN]; /* input data */
   int b[SIZEN][SIZEN]; /* output data */
   FILE *in_file,*out_file;

   /* read input data */
   printf("*** Transitive Closure ***\n");
   in_file=fopen("trans.in","r");
   fscanf(in_file,"%d",&n);
   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
	 fscanf(in_file,"%d",&a[i][j]);
   fclose(in_file);
   /* transitive closure */
   transitive_closure(a,b,n);
   /* write output data */
   out_file=fopen("trans.out","w");
   for (i=0; i<n ;i++) {
      for (j=0; j<n; j++)
	  fprintf(out_file,"%3d",b[i][j]);
	  fprintf(out_file,"\n");
   }
   fclose(out_file);
   printf("\nPress any key to continue...");
   getch();
}
/* test data format:
   input file name: trans.in
	 The number on the first line is the number of nodes in the
	 graph.
   sample input:
   5
   0 0 1 1 0
   0 0 1 0 0
   0 0 0 1 1
   0 0 0 0 1
   0 0 0 1 0
   outfile name: trans.out
   sample output:
   0 0 1 1 1
   0 0 1 1 1
   0 0 0 1 1
   0 0 0 1 1
   0 0 0 1 1
*/
