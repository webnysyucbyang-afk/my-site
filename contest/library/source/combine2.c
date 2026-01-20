/* get the sequence # of a combination in C(n, k) combinations */
   count from 0, e,g, in C(4,3), all combinations are
      abc, abd, acd, bcd. Thus, the sequence # of acd is 2 */
/* PS : need initiation (call combine2(0, 0, NULL, NULL, 0)*/

#include <stdio.h>

typedef char Type;       // data type of elements
int combine2(int n, int k, Type src[], Type des[])
/*
   Author  : Zhong Ming-Xun
   Subject : combination method vol. 2

   Input   :
      n      : # of total elements
      k      : # of picked elements
      src    : permutation of sequence # 0
      des    : the problem
   Output  :
      return value : sequence #
*/
{
	static int c[32][32];
	int i, j;
	int sum, p;
	int tn, tk;

	if (src == NULL && des == NULL) {
		for(i=1;i<32;i++) {
			c[i][1]=i;
			c[i][0]=1;
		}
	   
		for(i=0;i<32;i++)
			c[i][i]=1;
	   
		for(j=2;j<32;j++)
			for(i=j+1;i<32;i++)
				c[i][j]=c[i-1][j]+c[i-1][j-1];
		   
		return 0;
	}

	tn=n-1, tk=k-1;
	p=0;
	sum=0;
	for (i=0; i < k; i++)	{

		while(src[p]<des[i]) {
			sum += c[tn][tk];
			tn--;
			p++;
		}

		tn--;
		tk--;
		p++;
	}

	return sum;
}

/* ******************************************* */
void main()
{
	
	FILE *in_file, *out_file;
	int m, n, k;
	char src[50], des[50];
	
	in_file  = fopen("combine2.in", "r");
	out_file = fopen("combine2.out", "w");
	
	combine2(0, 0, NULL, NULL);
	fscanf(in_file, "%d", &m);
	for ( ; m > 0; m--)
	{
		fscanf(in_file, "%d %d %s %s", &n, &k, src, des);
		
		fprintf(out_file, "%d\n", combine2(n, k, src, des));
	}
	
	fclose(in_file);
	fclose(out_file);
	
	
}

/* test data format:
   input file name: combine2.in

   sample input:
	3			// # of test data (following is test data)
	6 4 123456 1234		// n, k, src, des
	6 4 123456 2345		
	6 3 123456 345


   outfile name: combine2.out
   sample output:

	0
	12
	16

*/