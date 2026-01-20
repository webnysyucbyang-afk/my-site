/* All-pair Shortest Path of a Directed Graph,without getting the path */
#include<stdio.h>
#define SIZE 50      //maximum number of nodes
#define INF 9999     //used a large number denote infinity

void all_pair_shortest(int record[][SIZE],int dis[][SIZE],int n)
/* author: Kam-Fai Wong
   purpose: find all-pair shortest paths of a direct graph
   record[][]: input matrix to represent a graph,unchanged
   dis[][]: output data, length of the shortest path of each pair
   n: # of nodes (vertices) in the graph
   Note:  A very large number in a[][] represents that no edge connects
	  the pair of nodes   (ie INF)
*/
{
   int i,j,k;

     for(i=0;i<n;i++)    /*copy data from record to dis*/
       for(j=0;j<n;j++)
	   dis[i][j]=record[i][j];

     for(k=0;k<n;k++)
       for(i=0;i<n;i++)
	 for(j=0;j<n;j++){
	   if(dis[i][k]==INF || dis[k][j]==INF)
	     continue;
	   if(dis[i][j]>dis[i][k]+dis[k][j])
	     dis[i][j]=dis[i][k]+dis[k][j];
	 }
}

void main(void)
{
   int n;      /* # of nodes in the graph */
   int i,j;    /* index */
   int record[SIZE][SIZE]; /* input data */
   int dis[SIZE][SIZE];  /* output data */
   FILE *in_file,*out_file;


   /* read input data */
   printf("*** All pair shortest path ***\n");
   in_file=fopen("all_pair.in","r");
   fscanf(in_file,"%d",&n);
   for(i=0;i<n;i++)
      for(j=0;j<n;j++)
	 fscanf(in_file,"%d",&record[i][j]);
   fclose(in_file);

   /* All pair shortest path */
   all_pair_shortest(record,dis,n);

   /* write output data */
   out_file=fopen("all_pair.out","w");
    for(i=0;i<n;i++)  {
       for(j=0;j<n;j++)
	 fprintf(out_file,"%3d",dis[i][j]);
	 fprintf(out_file,"\n");
    }
   fclose(out_file);
}

 /* test data format:
    input file name: all_pair.in
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

    output filename: all_pair.out
    sample output:
      0 14  8  9  9 15
     14  0  6  7  6  1
      8  6  0  1  3  7
      9  5 11  0  9  6
     17  9  9  9  0 10
     18 14 18  9  9  0
 */