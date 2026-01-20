/* get the sequence # of a permutation in P(n, k) permutations
 count from 0, e,g, in P(4, 3), the sequence # of acb is 2*/
/* PS : need initiation (call permute2(0, 0, NULL, NULL)*/

#include <stdio.h>
typedef char Type;
int permute2(int n, int k, Type src[], Type des[])
/*
   Author  : Jong-rong Shyy
   Subject : permutation method vol. 2

   Input   :
      n      : # of total elements
      k      : # of picked elements
      src    : permutation of sequence # 0
      des    : the problem
   Output  :
      return value : sequence #
*/
{
   static int c[32][32], nf[13];
   int i, j, s, sum;
   int num[32];

   if (src == NULL && des == NULL)
   {
      nf[0] = 1;
      for (i = 1; i < 13; i++)
         nf[i] = i * nf[i - 1];
      for (i = 0; i < 32; i++)
         c[i][0] = 1;
      for (i = 1; i < 32; i++)
         for (j = 1; j <= i; j++)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
      return 0;
   }

   for (i = 0; i < n; i++)
      num[i] = 1;
   sum = 0;
   for (i = 0; i < k; i++)
   {
      s = -1;
      for (j = 0; j < n; j++)
         if (num[j] == 1)
         {
            s++;
            if (des[i] == src[j])
            {
               num[j] = 0;
               break;
            }
         }
      sum += s * c[n - i - 1][k - i - 1] * nf[k - i - 1];
   }
   return sum;
}


/* ******************************************* */
void main()
{
   FILE *in_file, *out_file;
   int m, n, k;
   char src[50], des[50];

   in_file  = fopen("permute2.in", "r");
   out_file = fopen("permute2.out", "w");

   permute2(0, 0, NULL, NULL);
   fscanf(in_file, "%d", &m);
   for ( ; m > 0; m--)
   {
      fscanf(in_file, "%d %d %s %s", &n, &k, src, des);

      fprintf(out_file, "%d\n", permute2(n, k, src, des));
   }

   fclose(in_file);
   fclose(out_file);
}

/* test data format:
   input file name: permute2.in
                (²Õ¼Æ
                 n k src des
                 ....)
   sample input:
      
      4
      5 3 abcde edc
      5 3 abcde bde
      4 4 abcd dcba
      12 12 0123456789ab ba9876543210

   output file name : permute2.out
   sample output:

      59
      20
      23
      479001599
*/