/* Bubble Sort */
#include <stdio.h>
#define SIZEN 200
void bubble_sort(int a[], int b[], int n)
/* author: Chang-Biau Yang
   purpose: bubble sort to increasing order
   a[]: input data to be sorted, not changed
   b[]: output data, sorted, b[0] <= b[1] <= b[2] <=...
   n: # of data elements to be sorted
*/
{  int flag;   /* initial value=0, and 0 if not exchange */
   int i,j;    /* index */
   int temp;   /* temporary storage, for exchange */

   if (n==0)     /* no elements */
      return;
   for (i=0; i<n; i++)   /* copy data from a[] to b[] */
      b[i]=a[i];
   for (i=0; i<n-1; i++) {   /* bubble sort to increasing order */
      flag=0;
      for(j=0; j<(n-1-i); j++)
	 if (b[j]>b[j+1]) {	       /* exchange */
	    temp=b[j];
	    b[j]=b[j+1];
	    b[j+1]=temp;
	    flag=1;
	 }
      if (flag==0)
	 break;
   }
}    /* end of bubble_sort() */

main()
{  int n;     /* # of elements to be sorted */
   int i;     /* index */
   int a[SIZEN]; /* input data */
   int b[SIZEN]; /* output data */
   FILE *in_file,*out_file;

   /* read input data */
   printf("*** Bubble Sort ***\n");
   in_file=fopen("bubble.in","r");
   fscanf(in_file,"%d",&n);
   for (i=0; i<n; i++)
      fscanf(in_file,"%d",&a[i]);
   fclose(in_file);
   /* bubble sort */
   bubble_sort(a,b,n);
   /* write output data */
   out_file=fopen("bubble.out","w");
   for (i=0; i<n ;i++)
      fprintf(out_file,"%d\n",b[i]);
   fclose(out_file);
   printf("\nPress any key to continue...");
   getch();
}
/* test data format:
   input file name: bubble.in
	 The number on the first line is the number of elements to
	 be sorted.
   sample input:
   8
   10
   3
   12
   6
   9
   4
   5
   3
   outfile name: bubble.out
   sample output:
   3
   3
   4
   5
   6
   9
   10
   12
*/
