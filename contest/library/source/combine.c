//calculate the values of all combinations C(n,k), n<=33,for all k<=n
#include<stdio.h>
#define SIZE 35

void combination(long n,long ans[][SIZE])
/* author:Kam-Fai Wong
   purpose:find number of cases that k objects choice from n object
	   where 0<=k<=n.
   n:total number of objects
   ans[][]:ans[i][j]=number of cases that j objects choice from i objects
*/
{
  long i,j;

  for(i=1;i<n;i++)
  {
	  ans[i][1]=i;
	  ans[i][0]=1;
  }

  for(i=0;i<n+1;i++)
	  ans[i][i]=1;

  for(j=2;j<n+1;j++)
	  for(i=j+1;i<n+1;i++)
		  ans[i][j]=ans[i-1][j]+ans[i-1][j-1];
}

void main(void)
{
  long n; //number of cases that k objects choice from n objects
  long k; //n>=k>=0 ,both n,k are positive integer
  long ans[SIZE][SIZE]; //ans[i][j]={number of cases that j objects
			  //           choice from i objects 0<=j<=i<=n}

 //
 //by testing,this program is true if and only if n<=33
 //

  scanf("%ld %ld",&n,&k);

  combination(33,ans);

  printf("%ld\n",ans[n][k]);
}


/*Sample input:
	       33 16

  Sample output:
	       1166803110
*/