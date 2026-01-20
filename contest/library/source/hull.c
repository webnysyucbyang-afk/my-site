// Find the convex hull for n given points on the 2-D plane
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define SIZE  1000 
// anhutor : Fie-tian (Mong-Chi Shieh)
/* Set the stack size to be greater than the default. */
/* This declaration must go in the global data area. */
extern unsigned _stklen = 60000U;

const double EPSILON = 0.00001;
int hull(int ans[], int point[][2], int n)
// ahthor: Fei-tain
// purpose: find the convex hull of given points on 2-D plane
// ans[]: output, indices of point[][2]
// point[][2]: input data, 2-D points
// n : number of input points
// return: number of points on the convex hull
{
  int maxp, maxx=INT_MIN, maxy=INT_MIN;
  int i, ac=0;
  double vx1, vy1, vx2, vy2;
  double vmax, vmaxp, vmaxlength, value, vlength, tmp;

  vx1 = (double)INT_MAX;
  vy1 = 0.0;

   for(i=0;i<n;i++)
    if(point[i][0]>maxx)
	{
	 maxx = point[i][0];
	 maxy = point[i][1];
	 maxp = i;
	}
    else if(point[i][0]==maxx && point[i][1]>maxy)
	{
	 maxx = point[i][0];
	 maxy = point[i][1];
	 maxp = i;
	}

   ans[ac++] = maxp;

   do {
	  vmax = -10000.0;
	  vmaxlength = 0.0;
	  for(i=0;i<n;i++)
	  {
	   vx2 = (double)point[i][0] - point[ans[ac-1]][0];
	   vy2 = (double)point[i][1] - point[ans[ac-1]][1];
	   vlength = pow(fabs(vx2),2)+pow(fabs(vy2),2);
	   tmp = sqrt(pow(fabs(vx1),2)+pow(fabs(vy1),2))*sqrt(vlength);
	   if(tmp<=EPSILON && tmp>=-1*EPSILON) continue;

	   value = (vx1*vx2 + vy1*vy2)/tmp;
	   if(value > vmax+EPSILON)
	   {
	    vmax = value;
	    vmaxp = i;
	    vmaxlength = vlength;
	   }
	   else if(value <= vmax+EPSILON && value >= vmax-EPSILON && vmaxlength < vlength)
	   {
	    vmax = value;
	    vmaxp = i;
	    vmaxlength = vlength;
	   }

	  }
	  ans[ac++] = vmaxp;
	  vx1 = (double)(point[ans[ac-1]][0] - point[ans[ac-2]][0]);
	  vy1 = (double)(point[ans[ac-1]][1] - point[ans[ac-2]][1]);

    }while(ans[0] != ans[ac-1]);
    return ac-1;
 }

 void main()
 {
  int point[SIZE][2];
  int ans[SIZE];
  int c,i;
  FILE *fp=fopen("hull.in","rt");
  int count=0;
  while(fscanf(fp,"%d %d", &point[count][0], &point[count][1])!=EOF)
   count++;
  c = hull(ans,point,count);
  for(i=0;i<c;i++)
   printf("%d:(%d,%d)\n",ans[i],point[ans[i]][0],point[ans[i]][1]);

  fclose(fp);
 }
/* test data format
   input file name: hull.in
Sample input :
1 1
1 2
1 3
1 4
1 5
2 1
2 2
2 3
2 4
2 5
3 1
3 2
3 3
3 4
3 5
4 1
4 2
4 3
4 4
4 5
5 1
5 2
5 3
5 4
5 5

Sample output:
24:(5,5)
20:(5,1)
0:(1,1)
4:(1,5)

*/
