/* Long integer arithmetic operations (+ - * / mod ^)      */
/* Author: Zhong Ming-Xun, 鍾明勳 */

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define DIGIT 1200

/* Purpose: Convert ASCII Number to integer array */
/* Char[] : "65535"                               */
/* Int[]  : Int[0]=6, Int[1]=5, Int[2]=5, Int[3]=3, Int[4]=5 */
/* Return : Digit of Number                      */
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

void longadd(char n1[], char n2[], char result[], int base)
{
        int x[DIGIT], y[DIGIT], x_digit, y_digit;

        /* 以下 x+1, y+1, x_digit+1, y_digit+1 皆為了保留一位
           做為進位用的 dirty hack
        */
        x[0]=0; y[0]=0;         /* dirty hack */
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

void longsub(char n1[], char n2[], char result[], int base)
{
        int x[DIGIT], y[DIGIT], x_digit, y_digit;

        if (strlen(n1) > strlen(n2)) {          /* n1 位數大於 n2 */ 
                x_digit = char2int(n1, x);
                y_digit = char2int(n2, y);
                i_sub(x, y, x_digit, y_digit, x_digit-y_digit, base);
                int2char(x, result, x_digit);
        } else if(strlen(n1) < strlen(n2)) {    /* n2 位數大於 n1 */
                x_digit = char2int(n1, x);
                y_digit = char2int(n2, y);
                i_sub(y, x, y_digit, x_digit, y_digit-x_digit, base);
                int2char(y, result+1, y_digit);
                result[0] = '-';
        } else if (strcmp(n1, n2) >= 0) {       /* n1 大於等於 n2 */
                x_digit = char2int(n1, x);
                y_digit = char2int(n2, y);
                i_sub(x, y, x_digit, y_digit, x_digit-y_digit, base);
                int2char(x, result, x_digit);
        } else {                                /* n1   小於   n2 */ 
                x_digit = char2int(n1, x);
                y_digit = char2int(n2, y);
                i_sub(y, x, y_digit, x_digit, y_digit-x_digit, base);
                int2char(y, result+1, y_digit);
                result[0] = '-';
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

void longmul(char n1[], char n2[], char result[], int base)
{
        int x[DIGIT], y[DIGIT], i_result[DIGIT], x_digit, y_digit;

        x_digit = char2int(n1, x);
        y_digit = char2int(n2, y);
        i_mul(x, y, x_digit, y_digit, i_result, base);
        int2char(i_result, result, x_digit+y_digit);
}

void longmod(char n1[], char n2[], char result[], int base)
{
        char tmp1[DIGIT], tmp2[DIGIT];

        longdiv(n1, n2, tmp1, base);
        longmul(tmp1, n2, tmp2, base);
        longsub(n1, tmp2, result, base); 
}

void longexp(char n1[], int exp, char result[], int base)
{
        char temp[DIGIT];
        int i;
        
        if(exp==0) {
                result[0]='1';
                result[1]='\0';
        } else if(exp==1) {
                strcpy(result, n1);
        } else if(exp==2) {
                longmul(n1, n1, result, base);
        } else if (exp%2 ==0) {
                longexp(n1, exp/2, temp, base);
                longmul(temp, temp, result, base);
        } else { 
                longexp(n1, exp/2, temp, base);
                longmul(temp, temp, result, base);
                strcpy(temp, result);
                longmul(temp, n1, result, base);
        } 
}

void main()
{
        char tmpstr[200];
        char n1[DIGIT], n2[DIGIT], result[DIGIT], remainder[DIGIT];
        char oper;
        int base, i;

        FILE *fp = fopen("long_ari.in", "r");

        while(1) {

        if(fscanf(fp, "%d %s %c %s", &base, n1, &oper, n2)==EOF)
                break;
        printf("[%d]", base);
        
        switch (oper) {
        
        case '+':
                longadd(n1, n2, result, base);
                printf("%s + %s = %s\n", n1, n2, result);
                break;
        case '-':
                longsub(n1, n2, result, base);
                printf("%s - %s = %s\n", n1, n2, result);
                break;
        case '*':
                longmul(n1, n2, result, base);
                printf("%s * %s = %s\n", n1, n2, result);
                break;
        case '/':
                longdiv(n1, n2, result, base);
                longmod(n1, n2, remainder, base);
                printf("%s / %s = %s ...... %s\n", n1, n2, result, remainder);
                break;
        case '^':
                longexp(n1, atoi(n2), result, base);
                printf("%s ^ %s = %s\n", n1, n2, result);
                break;
        }

        } /* end of while */

        fclose(fp);
}

/* test data format:
   input file name: long_ari.in
Sample input:
10 1234567890 + 1234567890
10 3423452343452 - 35325325
10 5235325 - 532532523523
10 100 * 200
10 10 * 2
10 2 * 10
10 46543265343254324 * 6436436234
10 46543265 * 4564236436436234
10 3452353245235325234543543234 / 54352345234
10 2 ^ 10
10 2 ^ 100
10 2 ^ 1000
16 FFFF + FFFF

Sample output:
[10]1234567890 + 1234567890 = 2469135780
[10]3423452343452 - 35325325 = 3423417018127
[10]5235325 - 532532523523 = -532527288198
[10]100 * 200 = 20000
[10]10 * 2 = 20
[10]2 * 10 = 20
[10]46543265343254324 * 6436436234 = 299572759503998578470775816
[10]46543265 * 4564236436436234 = 212434465983707294664010
[10]3452353245235325234543543234 / 54352345234 = 63518018042682592 ...... 46677576706
[10]2 ^ 10 = 1024
[10]2 ^ 100 = 1267650600228229401496703205376
[10]2 ^ 1000 = 10715086071862673209484250490600018105614048117055336074437503883703510511249361224931983788156958581275946729175531468251871452856923140435984577574698574803934567774824230985421074605062371141877954182153046474983581941267398767559165543946077062914571196477686542167660429831652624386837205668069376
[16]FFFF + FFFF = 1FFFE

*/
