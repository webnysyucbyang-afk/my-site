/* purpose: 計算兩圓交點
   author: Chia-Mau Huang
*/
#include <stdio.h>
#include <math.h>

struct circle {
        double x, y, r;
};
struct answer {
        double x, y;
};


int cxc(struct circle cir1, struct circle cir2, struct answer *ans1, struct answer *ans2) {
        double a, b, R, D, rem;
        double LA, A, B, C, Hmm;
        a = cir2.x - cir1.x;
        b = cir2.y - cir1.y;
        R = cir1.r + cir2.r;
        D = hypot(a, b);
        if (D > R) {
                return 0;       // 兩圓無交點
        }
        else if (D == R) {
                ans1->x = ans2->x = cir1.x + a * cir1.r / R;
                ans1->y = ans2->y = cir1.y + b * cir1.r / R;
                return 1;       // 兩圓交於一點
        }
        else {
                if (cir2.r > cir1.r) {
                        rem = cir2.x;
                        cir2.x = cir1.x;
                        cir1.x = rem;
                        rem = cir2.y;
                        cir2.y = cir1.y;
                        cir1.y = rem;
                        rem = cir2.r;
                        cir2.r = cir1.r;
                        cir1.r = rem;
                }
                if (D < cir1.r) {
                        if (cir2.r < cir1.r - D)
                                return 0;
                        else if (cir2.r == cir1.r - D) {
                                ans1->x = ans2->x = cir1.x + a * cir1.r / R;
                                ans1->y = ans2->y = cir1.y + b * cir1.r / R;
                                return 1;
                        }
                }
                if (a == 0) {
                        ans1->y = ans2->y = (cir1.r*cir1.r - cir2.r*cir2.r + b*b) / (2*b);
                        ans1->x = sqrt(cir1.r*cir1.r - (ans1->y)*(ans1->y));
                        ans2->x = -(sqrt(cir1.r*cir1.r - (ans1->y)*(ans1->y)));
                        return 2;       // 兩圓相交兩點
                }
                else if (b == 0) {
                        ans1->x = ans2->x = (cir1.r*cir1.r - cir2.r*cir2.r + a*a) / (2*a);
                        ans1->y = sqrt(cir1.r*cir1.r - (ans1->x)*(ans1->x));
                        ans2->y = -(sqrt(cir1.r*cir1.r - (ans1->x)*(ans1->x)));
                        return 2;       // 兩圓相交兩點
                }
                else {
                        LA = (a*a + b*b + cir1.r*cir1.r - cir2.r*cir2.r) / (2*b);
                        B = LA * (a/b);
                        A = 1 + (a*a) / (b*b);
                        C = LA * LA - cir1.r*cir1.r;
                        Hmm = sqrt(B*B - A*C);
                        ans1->x = (-b + Hmm) / a + cir1.x;
                        ans1->y = sqrt(cir1.r*cir1.r - ((-b + Hmm) / a) * ((-b + Hmm) / a)); 
                        ans2->x = (-b - Hmm) / b + cir1.x;
                        ans2->y = sqrt(cir1.r*cir1.r - ((-b - Hmm) / a) * ((-b - Hmm) / a)); 
                        return 2;       // 兩圓相交兩點
                }
        }
        
}

void main(void) {
        FILE *in, *out;
        int n, flag;
        struct circle cir1, cir2;
        struct answer ans1, ans2;

        in  = fopen("cirinter.in", "r");
        out = fopen("cirinter.out", "w");

        fscanf(in, "%d\n", &n);
        for ( ; n > 0; n--) {
                fscanf(in, "%lf %lf %lf", &(cir1.x), &(cir1.y), &(cir1.r));
                fscanf(in, "%lf %lf %lf", &(cir2.x), &(cir2.y), &(cir2.r));
                flag = cxc(cir1, cir2, &ans1, &ans2);

                if (flag==0) 
                        fprintf(out, "兩圓無交點\n");
                else if (flag==1) {
                        fprintf(out, "兩圓交一點\n");
                        fprintf(out, "(%4.4f, %4.4f)\n",
                                                ans1.x, ans1.y);
                }
                else {
                        fprintf(out, "兩圓交兩點\n");
                        fprintf(out, "(%4.4f, %4.4f), (%4.4f, %4.4f)\n",
                                                ans1.x, ans1.y, ans2.x, ans2.y);
                }
        }
        
        fclose(in);
        fclose(out);
}

/* test data format:
  input file name: cirinter.in
Sample Input :
3
0 0 5 0 10 5
0 0 1 0 10 1
0 0 8 0 10 8

  output file name: cirinter.out
Sample Output :
兩圓交一點
(0.0000, 5.0000)
兩圓無交點
兩圓交兩點
(6.2450, 5.0000), (-6.2450, 5.0000)

*/

