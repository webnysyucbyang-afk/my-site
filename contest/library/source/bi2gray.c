/* Convert binary code to Graycode with 0/1 bit string*/
#include <stdio.h>
#define SIZE 50

int bi_gray(char b[],int g[])
/* author: wongkf
   purpose: convert binary code to graycode
   b[]: given binary code in string
   g[]:corresponding graycode in array
   return (n): # of bits of the gray codes
*/
{
  int i,n;
  int temp[SIZE];

    for(n=0;b[n]!='\0';n++)
      temp[n]=(int)(b[n]-'0');  //convert char to int

      g[0]=temp[0];

    for(i=1;i<n;i++)
      g[i]=(temp[i-1]^temp[i]);

      return(n);
}

void main(void)
{
   int i;         /* index */
   char b[SIZE];  /* input data */
   int g[SIZE];   /* output data */
   int n;         /*# of bits of gray codes*/
   FILE *in_file,*out_file;

   /* read input data */
   printf("*** Binary ==> graycode\n");
   in_file=fopen("bi2gray.in","r");
     fscanf(in_file,"%s",b);
   fclose(in_file);

   n=bi_gray(b,g);

   /* write output data */
   out_file=fopen("bi2gray.out","w");

   for(i=0;i<n;i++)
     fprintf(out_file,"%d ",g[i]);
   fclose(out_file);
}

/* test data format
	input file name: bi_gray.in
	sample input:
	00101110

	output filename:bi_gray.out
	sample output:
	graycode
	0 0 1 1 1 0 0 1      (where g[0]=0 g[1]=0 g[2]=1 ...)
*/