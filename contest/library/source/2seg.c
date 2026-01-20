/* Calculate the intersection between two line segments */
/* 計算線段與線段的交點 */

typedef struct
{
   double x, y;
} Point;

Point linexx(Point p1, Point p2, Point p3, Point p4, int *flag)
/*
   Author  : Jong-rong Shyy
   Subject : 計算線段與線段的交點

   Input   : 
      p1, p2 : 直線之端點 
      p3, p4 : 另一線段之端點
      flag   : 存放兩線段的關係
   Output  :
      傳回值 : 兩直線交點
      flag   : = 0 (有交點)
               = 1 (兩直線重合, 傳回值未定義, 且線段不一定有交集)
                      ^^^^
               = 2 (兩線平行, 傳回值未定義)
               = 3 (無交點)
*/
{
   Point ret;
   double v1[3], v2[3];
   double xy, xc, yc;

   v1[0] = p2.y - p1.y;
   v1[1] = p1.x - p2.x;
   v1[2] = -(v1[0] * p1.x + v1[1] * p1.y);

   v2[0] = p4.y - p3.y;
   v2[1] = p3.x - p4.x;
   v2[2] = -(v2[0] * p3.x + v2[1] * p3.y);

   xy = v1[0] * v2[1] - v1[1] * v2[0];
   xc = v1[2] * v2[0] - v1[0] * v2[2];
   yc = v1[1] * v2[2] - v1[2] * v2[1];

   if (xy == 0)
   {
      *flag = (xc == 0) ? 1 : 2;
      return ret;
   }

   *flag = 0;
   ret.x = yc / xy;
   ret.y = xc / xy;

   if ((ret.x - p1.x) * (p2.x - ret.x) < 0)
      *flag = 3;
   if ((ret.y - p1.y) * (p2.y - ret.y) < 0)
      *flag = 3;
   if ((ret.x - p3.x) * (p4.x - ret.x) < 0)
      *flag = 3;
   if ((ret.y - p3.y) * (p4.y - ret.y) < 0)
      *flag = 3;


   return ret;
}


/* ***************************************************** */
#include <stdio.h>
void main()
{
   FILE *in, *out;
   int n, i, flag;
   Point pts[4], is;

   in  = fopen("2seg.in", "r");
   out = fopen("2seg.out", "w");

   fscanf(in, "%d\n", &n);
   for ( ; n > 0; n--)
   {
      for (i = 0; i < 4; i++)
         fscanf(in, "%lf %lf", &(pts[i].x), &(pts[i].y));

      is = linexx(pts[0], pts[1], pts[2], pts[3], &flag);

      if (flag == 0)
         fprintf(out, "(%4.4f, %4.4f)\n", is.x, is.y);
      if (flag == 1)
         fprintf(out, "兩直線重合\n");
      if (flag == 2)
         fprintf(out, "兩線平行\n");
      if (flag == 3)
         fprintf(out, "無交點");
   }

   fclose(in);
   fclose(out);
}

/* Test data format
   input file name: 2seg.in
   sample input:
      5
      0 0 1 1 1 0 0 1
      0 1 100 20 43 42 53 2
      0 0 1 1 1 1 2 2
      1.5 1.5 0 0 2.5 1.5 1 0
      0 0 1 0 1 1 1 2

   sample output (file 2seg.out):
      (0.5000, 0.5000)
      (50.8353, 10.6587)
      兩直線重合
      兩線平行
      無交點
*/