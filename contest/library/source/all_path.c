/* All-pair Shortest Path of a Directed Graph,with getting the path */
#include<stdio.h>
#define SIZE 50      //maximum number of nodes
#define INF 9999     //used a large number denote infinity
int grob=0;

void printpath(int path[][SIZE],int pse[],int start,int end)
{
  if(path[start][end]==start){
    pse[grob++]=end;
    return;
  }

  printpath(path,pse,start,path[start][end]);
  printpath(path,pse,path[start][end],end);
}

void all_pair_shortest(int record[][SIZE],int dis[][SIZE],
         int path[][SIZE],int n)
/* author: Kam-Fai Wong
   purpose: find all-pair shortest paths of a direct graph
   record[][]: input matrix to represent a graph,unchanged
   dis[][]: output data, length of the shortest path of each pair
   path[][]: the path of shortest path
   n: # of nodes (vertices) in the graph
   Note:  A very large number in a[][] represents that no edge connects
	  the pair of nodes   (ie INF)
*/
{
   int i,j,k;

     for(i=0;i<n;i++)       /*copy data from record to dis*/
       for(j=0;j<n;j++){     /*also initial the path*/
	   dis[i][j]=record[i][j];
	   path[i][j]=i;
       }

     for(k=0;k<n;k++)
       for(i=0;i<n;i++)
	 for(j=0;j<n;j++){
	    if(dis[i][k]==INF || dis[k][j]==INF)
	      continue;
	    if(dis[i][j]>dis[i][k]+dis[k][j]){
	      dis[i][j]=dis[i][k]+dis[k][j];
	      path[i][j]=k;
	    }
	 }
}

void main(void)
{
   int n;      /* # of nodes in the graph */
   int i,j;    /* index */
   int record[SIZE][SIZE]; /* input data */
   int dis[SIZE][SIZE];    /* output data */
   int path[SIZE][SIZE];   /* path of shortest path*/
   int start,end;
   int pse[SIZE];
   FILE *in_file,*out_file;


   /* read input data */
   printf("*** All pair shortest path ***\n");
   in_file=fopen("all_path.in","r");
   fscanf(in_file,"%d",&n);
   for(i=0;i<n;i++)
      for(j=0;j<n;j++)
	 fscanf(in_file,"%d",&record[i][j]);
   fclose(in_file);

   /* All pair shortest path */
   all_pair_shortest(record,dis,path,n);

   /* write output data */
   out_file=fopen("all_path.out","w");
    fprintf(out_file,"distance:\n");
    for(i=0;i<n;i++)  {
       for(j=0;j<n;j++)
	 fprintf(out_file,"%3d",dis[i][j]);
	 fprintf(out_file,"\n");
    }
    fprintf(out_file,"\n\npath:\n");
    for(i=0;i<n;i++)  {
       for(j=0;j<n;j++)
	 fprintf(out_file,"%3d",path[i][j]);
	 fprintf(out_file,"\n");
    }

   /*print the shortest path from start to end*/
   start=0;end=5;
   pse[grob++]=start;   //this is the starting node
   printpath(path,pse,start,end);

   fprintf(out_file,"\npath from %d to %d:\n",start,end);
   for(i=0;i<grob;i++)
     fprintf(out_file,"%3d",pse[i]);

   fclose(out_file);
}

 /* test data format:
    input file name: all_path.in
	  The number on the first line is the number of nodes
	  in the graph.
	 (We use a large number (here is 9999) to represent that
	  there is no edge connecting a pair of nodes.)
    input sample:
    6
    0 28 8 9999 9 80
    9999 0 6 7 6 1
    8 9999 0 1 3 82
    9 5 9999 0 9 9999
    9999 9 9 9 0 19
    9999 9999 9999 9 9 0

    output filename: all_path.out
    sample output:
    distance:
     0 14  8  9  9 15
    14  0  6  7  6  1
     8  6  0  1  3  7
     9  5 11  0  9  6
    17  9  9  9  0 10
    18 14 18  9  9  0


    path:
     0  3  0  2  0  3
     2  1  1  1  1  1
     2  3  2  2  2  3
     3  3  1  3  3  1
     2  4  4  4  4  1
     3  3  4  5  5  5


    path from 0 to 5:
     0  2  3  1  5
 */