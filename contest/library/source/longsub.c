/* Long integer substraction      */
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
		if(x[i]<0) {
			x[i-1]--;
			x[i] += base;
		} else {
			x[i-1] += (x[i] / base);
			x[i] %= base;
		}
	}
}


int i_sub(int x[], int y[], int x_digit, int y_digit, int offset, int base)
{
	int i, w;
	
	for(i=0; i<y_digit; i++) {
		x[i+offset] -= y[i];
	}

	i_trans(x, x_digit, base);

	return (0);
}

void longsub(char n1[], char n2[], char result[], int base)
{
        int x[DIGIT], y[DIGIT], x_digit, y_digit;
 
	if (strlen(n1) > strlen(n2)) {		/* n1 位數大於 n2 */ 
        	x_digit = char2int(n1, x);
        	y_digit = char2int(n2, y);
		i_sub(x, y, x_digit, y_digit, x_digit-y_digit, base);
       		int2char(x, result, x_digit);
	} else if(strlen(n1) < strlen(n2)) {	/* n2 位數大於 n1 */
        	x_digit = char2int(n1, x);
        	y_digit = char2int(n2, y);
                i_sub(y, x, y_digit, x_digit, y_digit-x_digit, base);
                int2char(y, result+1, y_digit);
		result[0] = '-';
	} else if (strcmp(n1, n2) >= 0)	{	/* n1 大於等於 n2 */
        	x_digit = char2int(n1, x);
        	y_digit = char2int(n2, y);
                i_sub(x, y, x_digit, y_digit, x_digit-y_digit, base);
        	int2char(x, result, x_digit);
	} else {				/* n1   小於   n2 */ 
        	x_digit = char2int(n1, x);
        	y_digit = char2int(n2, y);
                i_sub(y, x, y_digit, x_digit, y_digit-x_digit, base);
                int2char(y, result+1, y_digit);
		result[0] = '-';
	} 
}

void main()
{
	char n1[DIGIT], n2[DIGIT], result[DIGIT];
	char oper;
	int base, i;

	FILE *fp = fopen("longsub.in", "r");

	while(1) {

		if(fscanf(fp, "%d %s %c %s", &base, n1, &oper, n2)==EOF)
			break;
		printf("[%d]", base);
	
		longsub(n1, n2, result, base);
		printf("%s - %s = %s\n", n1, n2, result);

	} /* end of while */

	fclose(fp);
}

/* test data format:
Input fime name: longsub.in
Sample input:
10 3423452343452 - 35325325
10 5235325 - 532532523523

Sample output:
[10]3423452343452 - 35325325 = 3423417018127
[10]5235325 - 532532523523 = -532527288198

*/
