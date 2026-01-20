/* multiplication of one long integer in an array and an integer */
#include<stdio.h>
#define SIZE 50

void check(int out[])
/* perform carry after calculation multiply
*/
{
 int i;

   for(i=SIZE-1;i>0;i--)
     while(out[i]>=10)
       {
	out[i-1]+=out[i]/10;
	out[i]%=10;
       }
}

void shortmul(char in[],int m,char out[])
/* multiplication of two integers, one in an array
   out[]=in[]*m
*/
{
 int i,n,j;
 int temp_in[SIZE]={0},temp_out[SIZE];

   for(n=0;in[n]!='\0';n++){}
      for(i=0;i<n;i++)
	 temp_in[SIZE-n+i]=(int)(in[i]-'0');

   for(i=0;i<SIZE;i++)
      temp_out[i]=temp_in[i]*m;
      check(temp_out);

   for(i=0;temp_out[i]==0;i++){}
      for(j=0;i<SIZE;i++)
	 out[j++]=(char)(temp_out[i]+'0');
	 out[j]='\0';
}

void main(void)
/*  author: Kam-Fai Wong
    purpose: multiplication of two integers, one in an array
	     out[] = in[] * m
*/
{
  int m;    /* input data */
  char in[SIZE]; /* input data */
  char out[SIZE]; /*output data*/
  FILE *in_file,*out_file;


  /* read input data */
  printf("*** Radix conversion ***\n");
  in_file=fopen("shortmul.in","r");
  fscanf(in_file,"%s %d",in,&m);
  fclose(in_file);

   shortmul(in,m,out);      // out[] = in[] * m

  /* write output data */
  out_file=fopen("shortmul.out","w");
     fprintf(out_file,"%s\n",out);
  fclose(out_file);
}

/* test data format:
    input file name: shortmul.in
    sample input:
    123456789 33          (ie 123456789*33)

    output filename: shortmul.out
    sample output:
    4074074037
 */
