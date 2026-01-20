/* 求兩圓內公切線方程式 */
/* Author: Wei-hung Yeh 葉韋宏 */
#include <stdio.h>
#include <math.h>

#define INPUTFILE "c_intan.in"              /* 輸入檔檔名*/

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

/*
 c1 :圓1的座標
 r1 :圓1的半徑
 c2 :圓2的座標
 r2 :圓2的半徑
 *m1 :回傳外公切線斜率(若公切線只有一條,則斜率存放在*m1)
 *m2 :回傳外公切線斜率
 *p  :兩外公切線的交點
*/
int inner_tangent(POINT c1, double r1, POINT c2, double r2, double* m1,
double* m2, POINT* p)
{
        if (r1 + r2 > sqrt(pow(c1.x - c2.x,2) + pow(c1.y - c2.y,2)))
                return ERROR;
        p->x = (r2*c1.x + r1*c2.x) / (r1 + r2);
        p->y = (r2*c1.y + r1*c2.y) / (r1 + r2);
        return point2circle_slope(c1,r1,*p,m1,m2);
}

void main(void)
{
        POINT c1,c2,p;
        double r1,r2,m1,m2;
        int count;
        FILE* in_file = fopen(INPUTFILE,"r");

        count = 0;

while(fscanf(in_file,"%lf%lf%lf%lf%lf%lf",&c1.x,&c1.y,&r1,&c2.x,&c2.y,&r2)
!= EOF){
                printf("Case %d:\n",++count);
                switch (inner_tangent(c1,r1,c2,r2,&m1,&m2,&p)){
                case ERROR:
                        printf("ERROR!\n");
                        break;
                case ONLY_ONE_PERPENDICULAR_LINE:
                        printf("x = %lf\n",p.x);
                        break;
                case AMONG_ONE_IS_PERPENDICULAR:
                        printf("x = %lf\n",p.x);
                        printf("y = %lf * (x - %lf) + %lf\n",m1,p.x,p.y);
                        break;
                case TWO_GENERAL_LINES:
            printf("y = %lf * (x - %lf) + %lf\n",m1,p.x,p.y);
            printf("y = %lf * (x - %lf) + %lf\n",m2,p.x,p.y);
                        break;
                case ONLY_ONE_GENERAL_LINE:
                        printf("y = %lf * (x - %lf) + %lf\n",m1,p.x,p.y);
                        break;
                }
        }

        fclose(in_file);

}

/* test data format:
   Intput File: c_intan.in
   Sample Input: (圓1.x 圓1.y 圓1半徑 圓2.x 圓2.y 圓2半徑)
   0 0 2 6 0 2   兩圓不相交
   0 0 2 2 0 2   兩圓相交兩點,無內公切線
   0 0 2 4 0 2   兩圓相切,切線垂直X軸
   0 0 2 0 4 2   兩圓相切,切線平行X軸

   Sample Output:
   Case 1:
   y = 0.894427 * (x - 3.000000) + 0.000000
   y = -0.894427 * (x - 3.000000) + 0.000000
   Case 2:
   ERROR!
   Case 3:
   x = 2.000000
   Case 4:
   y = 0.000000 * (x - 0.000000) + 2.000000

*/
