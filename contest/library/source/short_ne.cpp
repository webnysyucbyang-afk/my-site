#include<stdio.h>
#define max 20  //max # of vertices
#define big 100000

void n_s_path(int n,int s,int p[max][max],int ans[max])
/*
Author:Huang Shou-Da(¶ÀºÓ¹F)
Purpose:find a shortest path in a direct graph G(V,E) with negative edges
        (The total cost of any cycle is positive )
input:
n: # of vertices
s: the source vertex of shortest path(with negative edges)
p: a matrix with the cost between any pair of vertices
ans: cost of the shortest path from source to any vertex

"NOTE" 1. the 1st vertex is numbered by 0, 2nd vertex is numbered by 1....
       2. ans is come from main(),it does not declared in n_s_path()
       3. the sum of the costs around any cycle in graph is positive
*/
{
        int lp[max][max]={big},min=big,index=0,ok[max]={0},l=1;
        for(int d=0,next=0;d<n;d++)
        {
                lp[0][d]=p[s][d];
                ok[s]=-1;
                if((lp[l-1][d]<min) && (ok[d]!=-1))
                {
                        min=lp[l-1][d];
                        next=d;
                }
        }
        ok[s]=-1;
        s=next;
        while(index!=n-1)
        {               
            min=big;
                for(int a=0;a<n;a++)                                    
                {
                        if(p[s][a]+lp[l-1][s]<lp[l-1][a])
                        {
                                lp[l][a]=p[s][a]+lp[l-1][s];
                                if(ok[a]==-1)
                                {
                                        ok[a]=0;
                                        index--;
                                }
                        }
                        else
                                lp[l][a]=lp[l-1][a];
                }
                ok[s]=-1;
                index++;
        for(int b=0;b<n;b++)
                        if((lp[l][b]<min) && (ok[b]!=-1))
                        {
                                min=lp[l][b];
                                next=b;
                        }
                s=next;
                l++;            
        }           
        for(int m=0;m<n;m++)
                ans[m]=lp[l-1][m];
}
void main(void)
{
        int map[max][max],ans[max];
        int n=0,s;
        FILE *in,*out;

        in=fopen("short_ne.in","r");
        out=fopen("short_ne.out","w");

        fscanf(in,"%d%d",&n,&s);
        for(int a=0;a<n;a++)
                for(int b=0;b<n;b++)
                        fscanf(in,"%d",&map[a][b]);
        n_s_path(n,s,map,ans);
		for(int b=0;b<n;b++)
       	{
           if(b==0)
	          fprintf(out,"%d",ans[0]);
	       else
	          fprintf(out," %d",ans[b]);
        }
}

/*

test data format
input file name: short_ne.in

5// # of vertices in this graph
0//the source vertex
0 6 999 999 7  // the graph
999 0 -1 2 -3
999 3 0 999 999
999 999 -1 0 999
999 999 999 2 0

// 999 means no edge

output file name ne_path.out

0 6 4 5 3//means v1->v2 is 6
         //      v1->v3 is 4
                 //      v1->v4 is 5
                 //      v1->v5 is 3
*/
