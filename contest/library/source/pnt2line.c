/* Calculate the distance between a point and straight line */
/* 計算點到直線的距離 */

#include <math.h>
typedef struct
{
   double x, y;
} Point;

double linepd(Point p1, Point p2, Point x)
/*
   Author  : Jong-rong Shyy
   Subject : 計算點到直線的距離

   Input   : 
      p1, p2 : 直線上之兩點 
      x      : 直線外之一點
   Output  :
      傳回值 : 點到直線的距離
*/
{
   double v[3], av;

   v[0] = p2.y - p1.y;
   v[1] = p1.x - p2.x;
   v[2] = -(v[0] * p1.x + v[1] * p1.y);

   av = -(v[0] * x.x + v[1] * x.y) - v[2];

   if (av < 0)
      av = -av;

   return  av / sqrt(v[0] * v[0] + v[1] * v[1]);
}


/* ***************************************************** */
#include <stdio.h>
void main()
{
   FILE *in, *out;
   int n, i;
   Point pts[3];
   double disp;

   in  = fopen("pnt2line.in", "r");
   out = fopen("pnt2line.out", "w");

   fscanf(in, "%d\n", &n);
   for ( ; n > 0; n--)
   {
      for (i = 0; i < 3; i++)
         fscanf(in, "%lf %lf", &(pts[i].x), &(pts[i].y));

      disp = linepd(pts[0], pts[1], pts[2]);

      fprintf(out, "disp = %4.4f\n", disp);
   }

   fclose(in);
   fclose(out);
}

/* Test data format
   input file name: pnt2line.in
   sample input:
      3
      0 0 0 1 1 0
      -1.11 -2 99 2.34 1 0
      1 2 3 4 5 6

   sample output (file pnt2line.out):
      disp = 1.0000
      disp = 1.9067
      disp = 0.0000
*/