/* purpose: 三角形外心
   author: Chia-Mau Huang
*/
#include <stdio.h>

typedef struct {
        double x, y;
} Point;

Point circum(Point c1, Point c2, Point c3) {
        Point ret;
        double a1, b1, a2, b2;

        a1 = c1.x - c3.x;
        b1 = c1.y - c3.y;

        a2 = c2.x - c3.x;
        b2 = c2.y - c3.y;

        ret.x = (a1*a1 * b2 - a2*a2 * b1 + b1*b1 * b2 - b1 * b2*b2)
                    / (2 * (b2 * a1 - b1 * a2)) + c3.x;
        ret.y = (b1*b1 * a2 - b2*b2 * a1 + a1*a1 * a2 - a1 * a2*a2)
                    / (2 * (a2 * b1 - a1 * b2)) + c3.y;
        return ret;
}

void main(void) {
        FILE *in, *out;
        int n, i;
        Point pts[3], is;

        in  = fopen("tri_outc.in","r");
        out = fopen("tri_outc.out","w");
        
        fscanf(in, "%d\n", &n);
        for ( ; n > 0; n--) {
                for (i = 0; i < 4; i++)
                        fscanf(in, "%lf %lf", &(pts[i].x) , &(pts[i].y));
                is = circum(pts[0], pts[1], pts[2]);
                fprintf(out, "(%4.4f, %4.4f)\n", is.x, is.y);
        }

        fclose(in);
        fclose(out);
}

/* test data format:
   input file name: tri_outc.in
Sample Input:
1
0 0 0 1 1 0

   output file name:tri_outc.in
Sample Output:
(0.5000, 0.5000)
*/
