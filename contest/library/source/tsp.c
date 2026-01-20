/* author: Chia-Mau Huang
   purpose: Traveling Salesperson Problem (branch and bound)
*/
#include <math.h>
#include <stdio.h>
#define SIZE 10
int min(int map[SIZE][SIZE],int n) {
	int minisum=0;
	int i,j,mini;
	for (i=0;i<n;i++) {
		for (mini=30000,j=0;j<n;j++)
			if ((map[i][j]>=0)&&(mini>map[i][j]))
				mini=map[i][j];
		for (j=0;j<n;j++)
			map[i][j]=map[i][j]-mini;
		minisum=minisum+mini;
	}
	for (j=0;j<n;j++) {
		for (mini=30000,i=0;i<n;i++)
			if ((map[i][j]>=0)&&(mini>map[i][j]))
				mini=map[i][j];
		for (i=0;i<n;i++)
			map[i][j]=map[i][j]-mini;
		minisum=minisum+mini;
	}		
	return minisum;
}

void split(int map[SIZE][SIZE],int tmp[SIZE][2],
   int tmpout[SIZE*SIZE][2],int sum,int n,int *lowerbound) {
	int with[SIZE][2],without[SIZE*SIZE][2];
	int i,j,m,mini,tmpmini,minii,minij,flag;
	for (i=0;i<n;i++) {
		with[i][0]=tmp[i][0];
		with[i][1]=tmp[i][1];
	}
	for (i=0;i<n*n;i++) {
		without[i][0]=tmpout[i][0];
		without[i][1]=tmpout[i][1];
	}
	for (i=0,mini=30000;i<n;i++)
	  for (j=0;j<n;j++,flag=1) {
	    for (m=0;(m<n)&&(flag==1);m++)  
	       if ((with[m][0]==i)||(with[m][1]==j)||((with[m][0]==j)
                       &&(with[m][1]==i)))
	           flag=0;
	    for (m=0;(m<n*n)&&(flag==1);m++) 
	       if ((without[m][0]==i)&&(without[m][1]==j))
		  flag=0;
	       if ((flag==1)&&(map[i][j]>=0)&&(mini>map[i][j])) {
		  mini=map[i][j];
		  minii=i;
	          minij=j;
	       }			
	  }
	if (mini==30000)
		return;
	for (j=0,tmpmini=30000;j<n;j++)
	   if ((j!=minij)&&(tmpmini>map[minii][j])&&(map[minii][j]>=0))
			tmpmini=map[minii][j];
	if (sum + mini < *lowerbound) { 
		if (with[n-2][0]>=0) {
			*lowerbound=sum+mini;
			return;
		}
		else {
			for (i=0;(i<n)&&(with[i][0]>=0);i++) {}
			with[i][0]=minii;
			with[i][1]=minij;
			split(map,with,tmpout,sum+mini,n,lowerbound);
		}
	}
	if ((sum+tmpmini<*lowerbound)&&(without[n*n-2][0]==-1)) {
		for (i=0;(i<n*n)&&(without[i][0]>=0);i++) {}
		without[i][0]=minii;
		without[i][1]=minij;
		split(map,tmp,without,sum,n,lowerbound);
	}
	return;
		
}

void main(void) {
	int i,j,sum,n,map[SIZE][SIZE],lowerbound;
	int with[SIZE][2],without[SIZE*SIZE][2];
	FILE *in_file,*out_file;
	printf("Traveling Salesperson\n");
	in_file=fopen("tsp.in","r");
	fscanf(in_file,"%d",&n);
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			fscanf(in_file,"%d",&map[i][j]);
	fclose(in_file);
	for (i=0;i<n;i++)
		with[i][0]=with[i][1]=-1;
	for (i=0;i<n*n;i++)
		without[i][0]=without[i][1]=-1;
	sum=0;
	sum = sum + min(map,n);
	lowerbound=30000;
	split(map,with,without,sum,n,&lowerbound);
	out_file=fopen("tsp.out","w");
	fprintf(out_file,"%d\n",lowerbound);
}
/*  test data format:
    input file name: tsp.in
Sample Input:
7
-1 25 27 40 12 71 33
43 -1 23 53 42 30 61 
31 29 -1 7 18 19 41 
5 13 20 -1 62 51 29 
21 33 17 44 -1 23 11 
71 31 54 28 19 -1 20
47 28 29 33 13 28 -1
 
Sample Output (file tsp.out):
116
*/
