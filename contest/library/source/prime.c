/* find all prime numbers between 1 and n */
#include <stdio.h>
#define SIZEN 1000

int prime_number(int a[SIZEN], int n)
/* author: Chang-Biau Yang
   purpose: find the prime numbers between 2 and positive integer n
   a[]: the output prime numbers
        a[0]=2, a[1]=3, a[2]=5, a[3]=7,.....
   n: the upper limit of the positive integer
   return: # of prime numbers
*/
{
   int i,j;    /* index */
   int total;  /* total number of prime numbers */

   if (n<=1)     /* do nothing */
      return(0);
   a[0]=2;      /* The first prime number is 2 */
   total=1;
   for (j=3; j<=n; j++){  /* test each number between 3 and n.  */
      for (i=0; i<total; i++) {
         if (j%a[i]==0)     /* not prime if ==0  */
            break;
         if (j<a[i]*a[i]){  /* j is a prime number */
            a[total]=j;
            total++;
            break;
         }
      }
   }
   return(total);
}    /* end of prime_number() */

main()
{  int n;     /* prime numbers between 2 and n */
   int i;     /* index */
   int total;       /* total # of prime numbers between 2 and n */
   int a[SIZEN];    /* prime numbers */
   FILE *in_file,*out_file;

   /* read input data */
   printf("*** Prime Numbers ***\n");
   in_file=fopen("prime.in","r");
   fscanf(in_file,"%d",&n);
   fclose(in_file);
   /* find prime numbers */
   total=prime_number(a,n);
   /* write output data */
   out_file=fopen("prime.out","w");
   for (i=0;i<total;i++){     /* printout all prime numbers */
      if (i%12==0)            /* 12 prime numbers on each line */
         fprintf(out_file,"\n");
      fprintf(out_file,"%5d",a[i]);
   }
   fprintf(out_file,"\nThere are %d prime numbers between 1 and %d.",total,n);
   fclose(out_file);
   printf("\nPress any key to continue...");
   getch();
}
/* test data format:
   input file name: prime.in
         There is only one number n (finding prime numbers
         between 2 and n.
   sample input:
   300
   outfile name: prime.out
   sample output:
    2    3    5    7   11   13   17   19   23   29   31   37
   41   43   47   53   59   61   67   71   73   79   83   89
   97  101  103  107  109  113  127  131  137  139  149  151
  157  163  167  173  179  181  191  193  197  199  211  223
  227  229  233  239  241  251  257  263  269  271  277  281
  283  293
There are 62 prime numbers between 1 and 300.
*/
