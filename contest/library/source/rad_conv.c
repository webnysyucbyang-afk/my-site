/* radix conversion (from x to 10 or from 10 to x, long)*/
#include<stdio.h>
#define SIZE 100

/*  author: Kam-Fai Wong
    purpose: radix conversion (from x to 10 or 10 to x )
*/

int char2int(int temp[],char in[])
/* 將char in[]轉成 int temp[] */
{
   int i,n;  //n = # of digit of in[]

   for(n=0;in[n]!='\0';n++){}
   for(i=0;i<n;i++)
   {
     temp[SIZE-n+i]=(int)(in[i]-'0');
     if(temp[SIZE-n+i]>=17) temp[SIZE-n+i]-=7; 
   }

   return(n);
}

void int2char(char out[],int temp[])
/*  將int temp[] 轉成 char out[]*/
{
   int i,j;

   for(i=0;temp[i]==0;i++){}
   for(j=0;i<SIZE;i++)
   {
	 if(temp[i]>=10) temp[i]+=7;
     out[j++]=(char)(temp[i]+'0');
   }
     out[j]='\0';
}

void check(int out[])
/* perform carry after calculation (add, multiply) */
{
 int i;

   for(i=SIZE-1;i>0;i--)
     if(out[i]>=10)
       {
	out[i-1]+=out[i]/10;
	out[i]%=10;
       }
}

void longmul(int out[],int in[],int x)
/* multiplication of two integers, one in an array
   out[]=in[]*x
*/
{
 int i;

   for(i=0;i<SIZE;i++)
     out[i]=in[i]*x;
     check(out);
}

void longadd(int out[],int in1[], int in2[])
/* addition of two integers in two arrays
   out[]=in1[]+in2[]
*/
{
 int i;

   for(i=0;i<SIZE;i++)
     out[i]=in1[i]+in2[i];
     check(out);
}

int longdiv(int quote[],int in[],int req)
/* one integer in an array is divided by an integer
   quote[]=in[]/req
   retrun: remainder=in[] mod req
*/
{
 int i,remain=0;

   for(i=0;i<SIZE;i++)
     if(in[i]>0) break;

   for(;i<SIZE;i++)
     {
      remain+=in[i];
      quote[i]=remain/req;
      remain=(remain%req)*10;
     }
   remain/=10;
   return(remain);
}

void x_to_ten(int giv,char out[],char in[])
/*  convert a number from radix giv to 10
    giv: given radix
    in[]: value under given radix
    out[]: coressponding decimal value
*/
{
 int temp[SIZE],pow[SIZE]={0};
 int temp_in[SIZE]={0},temp_out[SIZE]={0};
 int i,j;
 int n;     //digit of in[]

 n=char2int(temp_in,in);

 pow[SIZE-1]=1;          //assign pow[]=1

 temp_out[SIZE-1]=temp_in[SIZE-1];
 check(temp_out);
 for(i=SIZE-2,j=0;j<n-1;j++,i--)
   {
    longmul(pow,pow,giv);
    if(temp_in[i]==0) continue;
    longmul(temp,pow,temp_in[i]);
    longadd(temp_out,temp_out,temp);
   }

  int2char(out,temp_out);
}

void ten_to_x(int req,char out[],char in[])
/*  convert a number from 10 to radix req
    req: given radix
    in[]: value under radix 10
    out[]: coressponding value under radix req
*/
{
  int i,j;
  int n;                          //digit of in[]
  int quote[SIZE]={0},rec[SIZE]={0};
  int temp_in[SIZE]={0},temp_out[SIZE]={0};

    n=char2int(temp_in,in);

    for(j=SIZE-n;j<SIZE;j++)
       rec[j]=temp_in[j];

     for(i=SIZE-1;i>=0;i--)
      {
       temp_out[i]=longdiv(quote,rec,req);
	   for(j=SIZE-n;rec[j]==0 && j<SIZE;j++){}
	   if(j==SIZE) break;
	   for(;j<SIZE;j++)
	     rec[j]=quote[j];
      }

   int2char(out,temp_out);
}

void main(void)
{
  int giv,req;  /*given & required radix respectively*/
  char in[SIZE]; /* input data */
  char out[SIZE],out1[SIZE]; /* output data (decimal & given radix
			                                  respectively)*/

  /* read input data */
  printf("*** Radix conversion ***\n");
  scanf("%d %d",&giv,&req);
    scanf("%s",in);

   x_to_ten(giv,out,in);  /*radix conversion from ? to decimal*/
   ten_to_x(req,out1,out); /*radix conversion from dec to ?*/

  /* write output data */
     printf("\n%s (BASE %d)\n\n",out,10);
     printf("%s (BASE %d)\n\n",out1,req);
}

/* test data format:
    input file name: rad_conv.in
    (8= radix of given value , 5 means we need to find the
     coressponding value under radix 5)
    sample input:
    8 5
    7030211121120(value under radix 8)

    output filename: rad_conv.out
    sample output:
    484293517904       (coressponding decimal value)

    30413313120033104  (coressponding value under radix 5)
 */
