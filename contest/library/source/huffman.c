/* Huffman code of radix k (k-ary tree), k>=2 */

#include <stdlib.h>
#define N     100          // maximun # of elements
#define SIZEN 100          // maximun length of code
void huffman(const int num[], const int n, const int radix, 
            char code[N][SIZEN])
/*
   Author  : Jong-rong Shyy
   Subject : Huffman code
   Input   : 
      num   : # of every element
      n     : elements of num
      radix : radix
      code  : result of encoded (string format)
   Output  :
      return value : none
*/
{
   typedef struct NODE
   {
      int freq;
      char sym, count;
      struct NODE *father;
   } Node;

   Node node[N * 2], *tmp;
   int newn, a, b, i, j, k, sw;
   int max[N][2], m;
   char cd[SIZEN];

   for (i = 0; i < n; i++)
   {
      node[i].freq = num[i];
      node[i].father = NULL;
   }
   for (newn = n; ; newn++)
      if ((newn - radix) % (radix - 1) == 0)
         break;
   for ( ; i < newn; i++)
   {
      node[i].freq = 0;
      node[i].father = NULL;
   }

   for (i = newn; ; i++)
   {
      m = 0;
      for (j = 0; j < i; j++)
         if (node[j].father == NULL)
         {
            max[m][0] = node[j].freq;
            max[m++][1] = j;
         }
      if (m < radix)
         break;

      for (a = m - 1; a >= 0; a--)
      {
         sw = 0;
         for (b = 0; b < a; b++)
            if (max[b][0] > max[b + 1][0])
            {
               sw = 1;
               k = max[b][0];
               max[b][0] = max[b + 1][0];
               max[b + 1][0] = k;
               k = max[b][1];
               max[b][1] = max[b + 1][1];
               max[b + 1][1] = k;
            }
         if (sw == 0)
            break;
      }

      node[i].freq = 0;
      node[i].father = NULL;
      node[i].count = '0';

      for (j = 0; j < radix; j++)
      {
         node[max[j][1]].father = &node[i];
         node[max[j][1]].sym = node[i].count++;
         node[i].freq += node[max[j][1]].freq;
      }
   }

   for (i = 0; i < n; i++)
   {
      m = 0;
      for (tmp = &node[i]; ; tmp = tmp->father, m++)
      {
         if (tmp->father == NULL)
            break;
         cd[m] = tmp->sym;
         if (cd[m] > '9')
            cd[m] += 10 - 'A';
      }
      for (j = 0, k = m - 1; j < m; j++, k--)
         code[i][j] = cd[k];
      code[i][j] = '\0';
   }
}

/* ***************************************************** */
#include <stdio.h>
void main()
{
   FILE *in_file, *out_file;
   int n, num, radix, i, m[N];
   char code[N][SIZEN];
   int a;

   in_file  = fopen("huffman.in", "r");
   out_file = fopen("huffman.out", "w");

   fscanf(in_file, "%d", &n);
   for ( ; n > 0; n--)
   {
      fscanf(in_file, "%d %d", &radix, &num);
      for (i = 0; i < num; i++)
         fscanf(in_file, "%d", &m[i]);

      huffman(m, num, radix, code);

      for (a = 0; a < num; a++)
         fprintf(out_file, "%d = %s\n", a, code[a]);
      fprintf(out_file, "\n");
   }

   fclose(in_file);
   fclose(out_file);
}

/* test data format:
   input file name: huffman.in

   sample input:

      3                      // # of test data (following is test data)
      2  4  7 7 7 7          // (radix)  (# of elements)  (elements...)
      2  5  5 10 20 25 40
      3  7  20 5 8 5 12 6 9

   outfile name: huffman.out
   sample output:

      0 = 00
      1 = 01
      2 = 10
      3 = 11

      0 = 1100
      1 = 1101
      2 = 111
      3 = 10
      4 = 0

      0 = 1
      1 = 00
      2 = 20
      3 = 01
      4 = 22
      5 = 02
      6 = 21
*/