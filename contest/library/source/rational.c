/* purpost: 分數的加減乘除
  author: Chia-Mau Huang
*/
#include <stdio.h>
#define TRUE 1
#define FALSE 0

struct rational {
        int numerator;
        int denominator;
};

void reduce (struct rational *inrat,struct rational *outrat) {
        int a, b, rem;

        if (inrat->numerator > inrat->denominator) {
                a = inrat->numerator;
                b = inrat->denominator;
        } /* end if */
        else {
                a = inrat->denominator;
                b = inrat->numerator;
        } /* end else */
        while (b != 0) {
                rem = a % b;
                a = b;
                b = rem;
        } /* end while */
        outrat->numerator = inrat->numerator / a;
        outrat->denominator = inrat->denominator / a;
} /* end reduce */

int equal (struct rational *rat1,struct rational *rat2) {
        struct rational r1, r2;
        
        reduce(rat1, &r1);
        reduce(rat2, &r2);
        if ((r1.numerator == r2.numerator)&&(r1.denominator == r2.denominator))
                return(TRUE);
        return(FALSE);
} /* end equal */

void add (struct rational *r1, struct rational *r2, struct rational *r3) {
/* r3 points to the result of add *r1 and *r2 */
        struct rational rat3;
        
        rat3.numerator   = r1->numerator   * r2->denominator + r2->numerator * r1->denominator;
        rat3.denominator = r1->denominator * r2->denominator;
        reduce(&rat3, r3);
} /* end add */

void sub (struct rational *r1, struct rational *r2, struct rational *r3) {
/* r3 points to the result of sub *r1 and *r2 */
        struct rational rat3;
        
        rat3.numerator   = r1->numerator   * r2->denominator - r2->numerator * r1->denominator;
        rat3.denominator = r1->denominator * r2->denominator;
        reduce(&rat3, r3);
} /* end sub */

void multiply (struct rational *r1, struct rational *r2, struct rational *r3) {
/* r3 points to the result of multiplying *r1 and *r2 */
        struct rational rat3;
        
        rat3.numerator   = r1->numerator   * r2->numerator;
        rat3.denominator = r1->denominator * r2->denominator;
        reduce(&rat3, r3);
} /* end multiply */

void divide (struct rational *r1, struct rational *r2, struct rational *r3) {
/* r3 points to the result of dividing *r1 and *r2 */
        struct rational rat3;
        
        rat3.numerator   = r1->numerator   * r2->denominator;
        rat3.denominator = r1->denominator * r2->numerator;
        reduce(&rat3, r3);
} /* end divide */

void main(void) {
        FILE *in, *out;
        int n;
        struct rational r1,r2,r3;

        in  = fopen("rational.in", "r");
        out = fopen("rational.out", "w");

        fscanf(in, "%d\n", &n);
        for ( ; n > 0; n--) {
                fscanf(in, "%d %d", &(r1.numerator), &(r1.denominator));
                fscanf(in, "%d %d", &(r2.numerator), &(r2.denominator));
                
                if (equal(&r1,&r2)==1)
                        fprintf(out, "%d /%d = %d /%d\n",
                                        r1.numerator, r1.denominator, 
                                        r2.numerator, r2.denominator);

                add(&r1,&r2,&r3);
                fprintf(out, "%d /%d + %d /%d = %d /%d\n",
                                r1.numerator, r1.denominator, 
                                r2.numerator, r2.denominator,
                                r3.numerator, r3.denominator);

                sub(&r1,&r2,&r3);
                fprintf(out, "%d /%d - %d /%d = %d /%d\n",
                                r1.numerator, r1.denominator, 
                                r2.numerator, r2.denominator,
                                r3.numerator, r3.denominator);
                multiply(&r1,&r2,&r3);
                fprintf(out, "%d /%d * %d /%d = %d /%d\n",
                                r1.numerator, r1.denominator, 
                                r2.numerator, r2.denominator,
                                r3.numerator, r3.denominator);
                divide(&r1,&r2,&r3);
                fprintf(out, "%d /%d / %d /%d = %d /%d\n",
                                r1.numerator, r1.denominator, 
                                r2.numerator, r2.denominator,
                                r3.numerator, r3.denominator);

        }

        fclose(in);
        fclose(out);
}

/* test data format:
   input file name:rational.in
Sample Input:
4
1 2 1 2
4 6 7 5
9 3 5 8
8 9 4 3

   output file name:rational.out
Sample Output:
1 /2 = 1 /2
1 /2 + 1 /2 = 1 /1
1 /2 - 1 /2 = 0 /1
1 /2 * 1 /2 = 1 /4
1 /2 / 1 /2 = 1 /1
4 /6 + 7 /5 = 31 /15
4 /6 - 7 /5 = -11 /15
4 /6 * 7 /5 = 14 /15
4 /6 / 7 /5 = 10 /21
9 /3 + 5 /8 = 29 /8
9 /3 - 5 /8 = 19 /8
9 /3 * 5 /8 = 15 /8
9 /3 / 5 /8 = 24 /5
8 /9 + 4 /3 = 20 /9
8 /9 - 4 /3 = -4 /9
8 /9 * 4 /3 = 32 /27
8 /9 / 4 /3 = 2 /3
*/
