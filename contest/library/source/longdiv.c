/* Long integer division      */
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

/* x[] must greater than y[] */
void i_add(int x[], int y[], int x_digit, int y_digit, int offset, int base)
{
	int i;

	for(i=0; i<y_digit; i++) {
		x[i+offset] += y[i];
	}

	i_trans(x, x_digit, base);
}

int i_sub(int x[], int y[], int x_digit, int y_digit, int offset, int base)
{
	int i, w;
	
	for(i=0; i<y_digit; i++) {
		x[i+offset] -= y[i];
	}

	i_trans(x, x_digit, base);

	for(w=0; w<DIGIT; w++) {
		if (x[w]!=0) break;
	}

	if (x[w]>0) return(1);
	return(0);
}


void i_div(int x[], int y[], int x_digit, int y_digit, int result[], int base)
{
	int i, j, w, check;

	w = x_digit - y_digit + 1; /* 被除數減除數加一為要做的次數 */

	for(i=0; i<w; i++) {
		check=1;
	
		for(j=0;;j++) {
			if (check==0) break;
			check=i_sub(x, y, x_digit, y_digit, i, base);
		}

		i_add(x, y, x_digit, y_digit, i, base);
		result[i] = j-1;
	}
}

void longdiv(char n1[], char n2[], char result[], int base)
{
        int x[DIGIT], y[DIGIT], i_result[DIGIT], x_digit, y_digit;

        x_digit = char2int(n1, x);
        y_digit = char2int(n2, y);
        i_div(x, y, x_digit, y_digit, i_result, base);
	int2char(i_result, result, x_digit-y_digit+1);
}

void main()
{
	char n1[DIGIT], n2[DIGIT], result[DIGIT];
	char oper;
	int base, i;

	FILE *fp = fopen("longdiv.in", "r");

	while(1) {

		if(fscanf(fp, "%d %s %c %s", &base, n1, &oper, n2)==EOF)
			break;
		printf("[%d]", base);
	
		longdiv(n1, n2, result, base);
		printf("%s / %s = %s\n", n1, n2, result);

	} /* end of while */

	fclose(fp);
}

/* test data format: 
  Input fime name: longdiv.in

Sample input:
10 3452353245235325234543543234 / 54352345234

Sample output:
[10]3452353245235325234543543234 / 54352345234 = 63518018042682592 

*/
