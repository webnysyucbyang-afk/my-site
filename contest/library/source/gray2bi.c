/*Convert Gray code to binary code with 0/1 bit string*/
#include <stdio.h>
#define SIZE 50

int gray_bi(char g[],int b[])
/* author: wongkf
   purpose: convert graycode to binary code
   g[]: given graycode in string
   b[]:corresponding binary code in array
   return (n):# of bits of the binary codes
*/
{
  int i,n;
  int temp[SIZE];

    for(n=0;g[n]!='\0';n++)
      temp[n]=(int)(g[n]-'0');

    b[0]=temp[0];

    for(i=1;i<n;i++)
      b[i]=(b[i-1]^temp[i]);

    return(n);
}

void main(void)
{
   int i;          /* index */
   char g[SIZE];   /* input data */
   int b[SIZE];    /* output data */
   int n;          /*# of bits of the binary code*/
   FILE *in_file,*out_file;

   /* read input data */
   printf("Graycode ==> Binary code\n\n");
   in_file=fopen("gray2bi.in","r");
     fscanf(in_file,"%s",g);
   fclose(in_file);

   n=gray_bi(g,b);

   /* write output data */
   out_file=fopen("gray2bi.out","w");

   fprintf(out_file,"binary code\n");
   for(i=0;i<n;i++)
     fprintf(out_file,"%d ",b[i]);
   fclose(out_file);
}

/* test data format
	input filename:gray_bi.in
	sample input:
	00111001

	input file name: gray_bi.out
	sample output:
	binary code
	0 0 1 0 1 1 1 0    (where b[0]=0 b[1]=0 b[2]=1 ...)
*/