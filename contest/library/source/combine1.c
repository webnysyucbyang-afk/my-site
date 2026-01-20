/* combination of a given sequence # in C(n, k) combinations */
/*    count from 0, e,g, in C(4,3), all combinations are
      abc, abd, acd, bcd. Thus, the sequence # of acd is 2 */

/* PS : need initiation (call combine1(0, 0, NULL, NULL, 0)*/

#include <stdio.h>

typedef char Type;       // data type of elements
void combine1(int n, int k, Type src[32], Type ret[32], int seq)
/*
   Author  : Zhong Ming-Xun
   Subject : combination method vol. 1

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
	static int c[32][32];
	int i, j;
	int r, p;
	int tn, tk;

	if (src == NULL && ret == NULL) {

		n=32;
		   
		for(i=1;i<n;i++) {
			c[i][1]=i;
			c[i][0]=1;
		}
	   
		for(i=0;i<n+1;i++)
			c[i][i]=1;
	   
		for(j=2;j<n+1;j++)
			for(i=j+1;i<n+1;i++)
				c[i][j]=c[i-1][j]+c[i-1][j-1];
		   
		return;
	}

	tn=n-1, tk=k-1;
	r = seq+1;
	p=0;
	for (i=0; i < k; i++)	{
		while(c[tn][tk]<r) {
			r -= c[tn][tk];
			tn--;
			p++;
		}

		ret[i] = src[p];
		tn--;
		tk--;
		p++;
	}
}

/* ***************************************************** */
#include <stdio.h>
void main()
{
   FILE *in_file, *out_file;
   int m, n, k, seq;
   char src[50], ret[50];

   in_file  = fopen("combine1.in", "r");
   out_file = fopen("combine1.out", "w");

   combine1(0, 0, NULL, NULL, 0);

   fscanf(in_file, "%d", &m);
   for ( ; m > 0; m--)
   {
      fscanf(in_file, "%d %d %s %d", &n, &k, src, &seq);
    
      combine1(n, k, src, ret, seq);

      ret[k] = '\0';
      printf("%s\n", ret);
      fprintf(out_file, "%s\n", ret);
   }

   fclose(in_file);
   fclose(out_file);
}

/* test data format:
   input file name: combine1.in

   sample input:
	3		// # of test data (following is test data)
	6 4 123456 0	// n, k, src, seq
	6 4 123456 12	
	6 3 123456 16


   outfile name: combine1.out
   sample output:

	1234
	2356
	345

*/