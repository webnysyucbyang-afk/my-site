/* 求兩圓外公切線方程式 */
/* Wei-hung Yeh 葉韋宏*/
#include <stdio.h>
#include <math.h>

#define INPUTFILE "c_outtan.in"              /* 輸入檔檔名*/

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
#define SAME 5                   /* 兩圓半徑一樣,兩外公切線不垂直X軸 */
#define TWO_ORTHOGONAL_LINES 6   /* 兩圓半徑一樣,兩外公切線垂直X軸 */

int outer_tangent(POINT c1, double r1, POINT c2, double r2, double* m1,
double* m2, POINT* p)
{
        POINT t;
        double tr;
        
        if (fabs(r1 - r2) >= sqrt(pow(c1.x - c2.x,2) + pow(c1.y -
c2.y,2)))
                return ERROR;
        if (r1 == r2){
                if (c1.x == c2.x){
                        p->y = c1.y;
                        p->x = c1.x + r1;
                        return TWO_ORTHOGONAL_LINES;
                }
                else{
                        *m1 = (c1.y - c2.y) / (c1.x - c2.x);
                        p->x = c1.x + sqrt((pow(r1,2) + pow(*m1,2)) /
(pow(*m1,2) + 1));
                        if (*m1 == 0)
                                p->y = c1.y+r1;
                        else
                            p->y = -(p->x - c1.x) / *m1 + c1.y;
                        return SAME;
                }
        }
        else if (r2 > r1){
                t.x = c1.x; t.y = c1.y; tr = r1;
                c1.x = c2.x; c1.y = c2.y; r1 = r2;
                c2.x = t.x; c2.y = t.y; r2 = tr;
        }

    p->x = (r1*c2.x - r2*c1.x) / (r1 - r2);
        p->y = (r1*c2.y - r2*c2.y) / (r1 - r2);
        return point2circle_slope(c1,r1,*p,m1,m2);
}

void main(void)
{
        POINT c1,c2,p;
        double r1,r2,m1,m2;
    FILE *in_file = fopen(INPUTFILE,"r");
        int count;

        count = 0;

while(fscanf(in_file,"%lf%lf%lf%lf%lf%lf",&c1.x,&c1.y,&r1,&c2.x,&c2.y,&r2)
!= EOF){
            printf("Case %d:\n",++count);
                switch (outer_tangent(c1,r1,c2,r2,&m1,&m2,&p)){
                case ERROR:
                        printf("ERROR!\n");
                        break;
                case SAME:
                        printf("y = %lf * (x - %lf)% + lf\n",m1,p.x,p.y);
            printf("y = %lf * (x - %lf)% +
lf\n",m1,2*c1.x-p.x,2*c1.y-p.y);
                        break;
                case TWO_ORTHOGONAL_LINES:
                        printf("x = %lf\n",p.x);
                        printf("x = %lf\n",2*c1.x - p.x);
                        break;
                case AMONG_ONE_IS_PERPENDICULAR:
                        printf("y = %lf * (x - %lf)% + lf\n",m1,p.x,p.y);
                        printf("x = %lf\n",p.x);
                        break;
                case TWO_GENERAL_LINES:
                        printf("y = %lf * (x - %lf) + %lf\n",m1,p.x,p.y);
            printf("y = %lf * (x - %lf) + %lf\n",m2,p.x,p.y);
                        break;
                }
        }

        fclose(in_file);
}

/* test data format:
   input file name: c_outtan.in
   Sample Input: (圓1.x 圓1.y 圓1半徑 圓2.x 圓2.y 圓2半徑)
    0 0 2 0 5 2         兩圓半徑一樣,外公切線皆垂直X軸
    0 0 2 5 0 2         兩圓半徑一樣,外公切線皆平行X軸
    0 0 4 5 0 2         兩圓大小不一樣,有兩條外公切線
    0 0 2 3 3 2         兩圓大小一樣,兩外公切線不平行也不垂直X軸
 
    Sample OutPut:
    Case 1:
    x = 2.000000
    x = -2.000000
    Case 2:
    y = 0.000000 * (x - 2.000000)+2.000000
    y = 0.000000 * (x - -2.000000)-2.000000
    Case 3:
    y = 0.436436 * (x - 10.000000) + 0.000000
    y = -0.436436 * (x - 10.000000) + 0.000000
    Case 4:
    y = 1.000000 * (x - 1.581139)-1.581139
    y = 1.000000 * (x - -1.581139)+1.581139

*/


