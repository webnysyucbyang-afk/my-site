/* Long integer addition  */
/* Author: Zhong Ming-Xun, 鍾明勳 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIGIT 1200

/* Purpose: Convert ASCII Number to integer array */
/* Char[] : "65535"				  */
/* Int[]  : Int[0]=6, Int[1]=5, Int[2]=5, Int[3]=3, Int[4]=5 */
/* Return : Digit of Number			 */
int char2int(const char Char[], int Int[])
{
	int i;

	for(i=0; i<DIGIT; i++) {

		if(Char[i]=='\0') break;

		if(Char[i]<='9')
			Int[i] = Char[i] - '0';
		else
			Int[i] = Char[i] - 'A' + 10;
        }

	return(i);
}	

/* Purpose: Convert integer array to ASCII Number */
/* Int[]  : Int[0]=6, Int[1]=5, Int[2]=5, Int[3]=3, Int[4]=5 */
/* Char[] : "65535"                               */
void int2char(const int Int[], char Char[], const digit)
{
	int i, offset;

	for(i=0; i<digit; i++) 
		if(Int[i] != 0)
			break;
	offset=i;

	/* offset 用來消掉前面的 '0' */
	for(; i<digit; i++) {
		if (Int[i] <= 9)
			Char[i-offset] = '0' + Int[i];
		else
			Char[i-offset] = 'A' + Int[i] - 10;
	}
	Char[digit-offset]='\0';
}

/* Purpose: 借位、進位處理 */
void i_trans(int x[], const int digit, const int base)
{
	int i;

	for(i=digit-1; i>0; i--) {
		x[i-1] += (x[i] / base);
		x[i] %= base;
	}
}

/* x[] must greater than y[] */
void i_add(int x[], int y[], int x_digit, int y_digit, int offset, int base)
{
	int i;

	for(i=0; i<y_digit; i++) {
		x[i+offset] += y[i];
	}

	i_trans(x, x_digit, base);
}

void longadd(char n1[], char n2[], char result[], int base)
{
	int x[DIGIT], y[DIGIT], x_digit, y_digit;

	/* 以下 x+1, y+1, x_digit+1, y_digit+1 皆為了保留一位
	   做為進位用的 dirty hack
	*/
	x[0]=0; y[0]=0;		/* dirty hack */
	if(strlen(n1) >= strlen(n2)) {
		x_digit = char2int(n1, x+1);
		y_digit = char2int(n2, y+1);
	} else {
                x_digit = char2int(n2, x+1);
                y_digit = char2int(n1, y+1);
	}
	i_add(x, y, x_digit+1, y_digit+1, x_digit-y_digit, base);
        int2char(x, result, x_digit+1);
}

void main()
{
	char n1[DIGIT], n2[DIGIT], result[DIGIT];
	char oper;
	int base, i;

	FILE *fp = fopen("longadd.in", "r");

	while(1) {

		if(fscanf(fp, "%d %s %c %s", &base, n1, &oper, n2)==EOF)
			break;
		printf("[%d]", base);
	
		longadd(n1, n2, result, base);
		printf("%s + %s = %s\n", n1, n2, result);

	} /* end of while */

	fclose(fp);
}

/* test data format: 
   Input fime name: longadd.in
Sample input:
10 1234567890 + 1234567890
16 FFFF + FFFF

Sample output:
[10]1234567890 + 1234567890 = 2469135780
[16]FFFF + FFFF = 1FFFE

*/
