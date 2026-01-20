/* one long integer in an array divided by an integer */
#include<stdio.h>
#define SIZE 50

int shortdiv(char in[],int d,char out[])
/* one integer in an array is divided by an integer
   out[]=in[]/d
   return: remain=in[] mod d
*/
{
 int i,j,n,remain=0;
 int temp_in[SIZE]={0},temp_out[SIZE]={0};

  for(n=0;in[n]!='\0';n++)
     temp_in[n]=(int)(in[n]-'0');

   for(i=0;i<n;i++)
     {
      remain+=temp_in[i];
      temp_out[i]=remain/d;
      remain=(remain%d)*10;
     }
   remain/=10;

   for(j=0;temp_out[j]==0;j++){}

   for(i=0;i<n-j;i++)
      out[i]=(char)(temp_out[i+j]+'0');
      out[i]='\0';

   return(remain);
}

void main(void)
/*  author: Kam-Fai Wong
    purpose: one integer in an array is divided by an integer
	     out[]=in[]/d  &  remain=in[]%d
*/
{
  int d;          /* input data */
  char in[SIZE];  /* input data */
  char out[SIZE]; /* output data */
  int remain;      /*output data*/
  FILE *in_file,*out_file;


  /* read input data */
  printf("*** Short_div ***\n");
  in_file=fopen("shortdiv.in","r");
  fscanf(in_file,"%s %d",in,&d);
  fclose(in_file);

  remain=shortdiv(in,d,out);

  /* write output data */
  out_file=fopen("shortdiv.out","w");
     fprintf(out_file,"%s / %d = %s\n",in,d,out);
     fprintf(out_file,"%s mod %d = %d\n",in,d,remain);
  fclose(out_file);
}

/* test data format:
    input file name: shortdiv.in
    sample input:
    123456789 33

    output filename: shortdiv.out
    sample output:
    123456789 / 33 = 3741114
    123456789 mod 33 = 27

 */
