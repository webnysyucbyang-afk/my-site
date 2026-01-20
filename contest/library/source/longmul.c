/* Long integer multiplication   */
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

void i_mul(int x[], int y[], int x_digit, int y_digit, int result[], int base)
{
	int i, j, tempmul=0;

        for(i=0; i< DIGIT; i++)
                result[i]=0;
 
	for(i=x_digit-1; i>=0; i--) {
		for(j=y_digit-1; j>=0; j--) {
			result[j+i+1] += (y[j] * x[i]);
		}
		i_trans(result, x_digit+y_digit, base);
	}
}

void longmul(char n1[], char n2[], char result[], int base)
{
	int x[DIGIT], y[DIGIT], i_result[DIGIT], x_digit, y_digit;

        x_digit = char2int(n1, x);
        y_digit = char2int(n2, y);
        i_mul(x, y, x_digit, y_digit, i_result, base);
        int2char(i_result, result, x_digit+y_digit);
}

void main()
{
	char n1[DIGIT], n2[DIGIT], result[DIGIT];
	char oper;
	int base, i;

	FILE *fp = fopen("longmul.in", "r");

	while(1) {

		if(fscanf(fp, "%d %s %c %s", &base, n1, &oper, n2)==EOF)
			break;
		printf("[%d]", base);
	
		longmul(n1, n2, result, base);
		printf("%s * %s = %s\n", n1, n2, result);

	} /* end of while */

	fclose(fp);
}

/* test data format:
Input fime name: longmul.in
Sample input:
10 100 * 200
10 10 * 2
10 2 * 10
10 46543265343254324 * 6436436234
10 46543265 * 4564236436436234

Sample output:
[10]100 * 200 = 20000
[10]10 * 2 = 20
[10]2 * 10 = 20
[10]46543265343254324 * 6436436234 = 299572759503998578470775816
[10]46543265 * 4564236436436234 = 212434465983707294664010

*/
