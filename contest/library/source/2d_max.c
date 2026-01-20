/* author: Chia-Mau Huang
   purpose: Max. point on 2-D plane
*/
#include <math.h>
#include <stdio.h>

#define SIZE 100
/* p[SIZE][2]: Input Point
   ans[SIZE][2]: Max Point
   n: # of input points
   return: # of max. point
*/
int findmaxpoint(int p[SIZE][2],int ans[SIZE][2],int n) {
	int tmp[SIZE][2],index,i,j,temp;
	int min=-30000;
	for (i=0;i<n;i++) {
		tmp[i][0]=p[i][0];
		tmp[i][1]=p[i][1];
	}
	for (i=0;i<n;i++)
		for (j=0;j<n-i-1;j++)
			if (tmp[j][0]>tmp[j+1][0]) {
				temp=tmp[j][0];
				tmp[j][0]=tmp[j+1][0];
				tmp[j+1][0]=temp;
				temp=tmp[j][1];
				tmp[j][1]=tmp[j+1][1];
				tmp[j+1][1]=temp;
			}
	for (i=n-1,index=0;i>=0;i--)
		if (tmp[i][1]>=min) {
			ans[index][0]=tmp[i][0];
			ans[index][1]=tmp[i][1];
			min=tmp[i][1];
			index++;
		}

	return index;
}

void main(void) {
	FILE *in_file,*out_file;
	int n,i,index,p[SIZE][2],ans[SIZE][2];
	printf("*** 2-D Max Point ***\n");
        in_file=fopen("2d_max.in","r"); 
	fscanf(in_file,"%d",&n);
	for (i=0;i<n;i++)
		fscanf(in_file,"%d %d",&p[i][0],&p[i][1]);
	fclose(in_file);
	index = findmaxpoint(p,ans,n);
	out_file=fopen("2d_max.out","w");
	for (i=0;i<index;i++)
		fprintf(out_file,"%d %d\n",ans[i][0],ans[i][1]);
	fclose(out_file);
}

/* test data format:
   input file name: 2d_max.in
Sample Input:
10
5 6
1 3
2 26
15 63
35 61
15 43
36 16
45 32
76 42
23 72

Sample Output (file 2d_max.out):
76 42
35 61
23 72
*/
