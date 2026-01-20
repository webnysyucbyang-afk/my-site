/* Calculate the disance between a point and a line segment */
/* 計算點到直線的距離 */
#include <math.h>
typedef struct 
{
   double x, y;
} Point;
double linepd(Point p1, Point p2, Point x)
/*
   Author  : Jong-rong Shyy
   Subject : 計算點到線段的距離
   Input   : 
      p1, p2 : 線段上之端點 
      x      : 線段外之一點
   Output  :
      傳回值 : 點到線段的距離
*/
{
   double v[3], av;
   double d0, d1, d2;
   d0 = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
   d1 = sqrt((p1.x - x.x) * (p1.x - x.x) + (p1.y - x.y) * (p1.y - x.y));
   d2 = sqrt((p2.x - x.x) * (p2.x - x.x) + (p2.y - x.y) * (p2.y - x.y));
   if (d0 == d1 + d2)
      return 0;
   if ((d0 * d0 + d1 * d1) <= d2 * d2)
      if ((d0 * d0 + d2 * d2) <= d1 * d1)
      {
         v[0] = p1.y - p2.y;
         v[1] = p2.x - p1.x;
         v[2] = -(p1.x * v[0] + p1.y * v[1]);
         av = -(x.x * v[0] + x.y * v[1]);
         av -= v[2];
         if (av < 0)
            av = -av;
         return av / sqrt(v[0] * v[0] + v[1] * v[1]);
      }
   if (d2 > d1)
      return d1;
   return d2;
}
/* ***************************************************** */
#include <stdio.h>
void main()
{
   FILE *in, *out;
   int n, i;
   Point pts[3];
   double disp;
   in  = fopen("pnt2seg.in", "r");
   out = fopen("pnt2seg.out", "w");
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
   input file name: pnt2seg.in
   sample input:
      6
      0 0 2 0 1 1
      0 0 2 0 0 0
      0 0 1 0 2 1
      0 0 1 0 -1 1
      0 0 2 0 1 0
      0 0 2 0 2 0
   sample output (file pnt2seg.out):
      disp = 1.4142
      disp = 0.0000
      disp = 1.4142
      disp = 1.4142
      disp = 0.0000
      disp = 0.0000
*/