* 圓外一點與圓的切線方程式之斜率 */
/* Author: Wei-hung Yeh 葉韋宏 */
#include <stdio.h>
#include <math.h>

#define INPUTFILE "cir2pnt.in"              /* 輸入檔檔名*/

typedef struct POINT{
        double x,y;
}POINT;

/* center : 圓心的座標 (center.x,center.y)
   r      : 圓的半徑
   p      : 圓外一點的座標 (p.x,p.y)
   m1,m2  : 傳回的切線斜率
*/

#define ERROR 0                         /* 點在圓內 */
#define ONLY_ONE_PERPENDICULAR_LINE 1   /* 點在圓上,切線垂直x軸 */
#define AMONG_ONE_IS_PERPENDICULAR 2    /* 兩條切線,其中一條垂直x軸 */
#define TWO_GENERAL_LINES 3             /* 兩條不垂直X軸的切線 */
#define ONLY_ONE_GENERAL_LINE 4         /* 點在圓上,切線不垂直X軸 */

int point2circle_slope(POINT center, double r,POINT p, double* m1, double*
m2)
{
        double a,b,c,t;
        double D=0;
        bool OnCircle=false;

        a = p.x - center.x;
        a *= a;
        b = p.y - center.y;
        b *= b;
        c = sqrt(a + b);
        if (c < r)
                return ERROR;
        else if (c == r)
                OnCircle = true;
        b = (p.y - center.y) * (center.x - p.x);
    a = center.x - p.x;
        a *= a;
        a -= r*r;
        c = p.y - center.y;
        c *= c;
        c -= r*r;
                        
        if (a == 0 && !OnCircle){
        *m1 = (-c) / (2 * b);
                return AMONG_ONE_IS_PERPENDICULAR;
        }
        else{
                D = 4 * (b*b - a*c);
                if (D == 0){
                        if (p.y - center.y == 0)
                                return ONLY_ONE_PERPENDICULAR_LINE;
                        else{
                                *m1 = (-2*(p.y - center.y) * (center.x -
p.x)) / (2*a);
                                return ONLY_ONE_GENERAL_LINE;
                        }
                }
                else{
                D = sqrt(D);
                t = -2*(p.y - center.y) * (center.x - p.x);
                *m1 = (t + D) / (2*a);
                *m2 = (t - D) / (2*a);
                return TWO_GENERAL_LINES;
                }
        }
}

void main(void)
{
        double m1,m2;
        int count;
        POINT c,p;
        double r;
    FILE *in_file=fopen(INPUTFILE,"r");

        count = 0;
        while(fscanf(in_file,"%lf%lf%lf%lf%lf",&c.x,&c.y,&r,&p.x,&p.y) !=
EOF){
                printf("Case %d:\n",++count);
                switch (point2circle_slope(c,r,p,&m1,&m2)){
                case ERROR:
                        printf("The point is inside the circle.\n");
                        break;
                case ONLY_ONE_PERPENDICULAR_LINE:
                        printf("Just one line is x = %.6lf\n",p.x);
                        break;
                case AMONG_ONE_IS_PERPENDICULAR:
                        printf("One slope is %.6lf\n",m1);
                        printf("Another line is x = %.6lf\n",p.x);
                        break;
                case TWO_GENERAL_LINES:
                        printf("1st slope is %.6lf\n",m1);
                        printf("2nd slope is %.6lf\n",m2);
                        break;
                case ONLY_ONE_GENERAL_LINE:
                        printf("Just one slope:%.6lf\n",m1);
                        break;
                }
        }
        fclose(in_file);
}

/* test data format:
       input file name: cir2pnt.in
  Sample Input: (圓心.x 圓心.y 圓半徑 點.x 點.y)
  1 1 2 3 3     切線一條水平,一條垂直x軸
  1 1 2 2 2     點在圓內
  1 1 2 1 3     點在圓上,切線只有一條,平行x軸
  1 1 2 -1 1    點在圓上,切線只有一條,垂直x軸
  1 1 2 5 5     有兩條切線

  Sample Output:
  Case 1:
  One slope is 0.000000
  Another line is x = 3.000000
  Case 2:
  The point is inside the circle.
  Case 3:
  Just one slope:0.000000
  Case 4:
  Just one line is x = -1.000000
  Case 5:
  1st slope is 2.215250
  2nd slope is 0.451416
*/


