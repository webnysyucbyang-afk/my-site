/* permutation of a given sequence # in P(n, k) permutations
   count from 0, e,g, in P(4, 3), the sequence # of acb is 2*/

/* PS : need initiation (call permute1(0, 0, NULL, NULL, 0)*/

#include <stdio.h>
typedef char Type;       // data type of elements
void permute1(int n, int k, Type src[], Type ret[], int seq)
/*
   Author  : Jong-rong Shyy
   Subject : permutation method vol. 1

   Input   :
      n      : # of total elements
      k      : # of picked elements
      src    : elements, i.e. seq = 0;
      ret    : the seq-th permutation of src
      seq    : the sequence #
   Output  :
      return value : none
*/
{
   static int c[32][32], nf[13];
   
   int tmp[32];
   int a, b, s;
   int q, r, mu;

   if (src == NULL && ret == NULL)
   {
      nf[0] = 1;
      for (a = 1; a < 13; a++)
         nf[a] = a * nf[a - 1];
      for (a = 0; a < 32; a++)
         c[a][0] = 1;
      for (a = 1; a < 32; a++)
         for (b = 1; b <= a; b++)
            c[a][b] = c[a - 1][b] + c[a - 1][b - 1];
      return;
   }

   for (a = 0; a < n; a++)
      tmp[a] = 1;

   r = seq;
   for (a = 0; a < k; a++)
   {
      mu = c[n - a - 1][k - a - 1] * nf[k - a - 1];
      q = r / mu;
      r = r % mu;

      for (b = 0, s = -1; b < n; b++)
         if (tmp[b] == 1)
            if (++s == q)
            {
               tmp[b] = 0;
               break;
            }
      ret[a] = src[b];
   }
}


/* ***************************************************** */
#include <stdio.h>
void main()
{
   FILE *in_file, *out_file;
   int m, n, k, seq;
   char src[50], ret[50];

   in_file  = fopen("permute1.in", "r");
   out_file = fopen("permute1.out", "w");

   permute1(0, 0, NULL, NULL, 0);

   fscanf(in_file, "%d", &m);
   for ( ; m > 0; m--)
   {
      fscanf(in_file, "%d %d %s %d", &n, &k, src, &seq);
    
      permute1(n, k, src, ret, seq);

      ret[k] = '\0';
      printf("%s\n", ret);
      fprintf(out_file, "%s\n", ret);
   }

   fclose(in_file);
   fclose(out_file);
}

/* test data format:
   input file name: permute1.in

   sample input:

      3                     // # of test data (following is test data)
      5 3 abcde 0           // n, k, src, seq
      5 3 abcde 59
      4 4 abcd 23

   outfile name: permute1.out
   sample output:

      abc
      edc
      dcba
*/