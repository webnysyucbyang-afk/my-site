/* 求兩直線夾角 */
/* author:史忠榮 */
#include <math.h>
typedef struct
{
   double x, y;
} Point;

double angle(Point p1, Point p2, Point p3, Point p4)
/*
   Author  : Jong-rong Shyy
   Subject : 求兩直線夾角

   p1, p2  : 直線上兩點
   p3, p4  : 直線上兩點
   return value : 直線夾角中較小者 (單位為"弳")
*/
{
   double v1[2], v2[2];
   double dot, dia, dib;

   v1[0] = p1.x - p2.x;
   v1[1] = p1.y - p2.y;
   v2[0] = p3.x - p4.x;
   v2[1] = p3.y - p4.y;

   dot = v1[0] * v2[0] + v1[1] * v2[1];
   dia = v1[0] * v1[0] + v1[1] * v1[1];
   dib = v2[0] * v2[0] + v2[1] * v2[1];

   return acos(abs(dot) / sqrt(dia * dib));
}



#include <stdio.h>
void main()
{
   FILE *in = fopen("2lin_ang.in", "r"),
        *out = fopen("2lin_ang.out", "w");
   int n, i, j;
   Point pnt[4];


   fscanf(in, "%d", &n);
   for (i = 0; i < n; i++)
   {
      for (j = 0; j < 4; j++)
         fscanf(in, "%lf %lf", &(pnt[j].x), &(pnt[j].y));

      fprintf(out, "%lf\n", angle(pnt[0], pnt[1], pnt[2], pnt[3]));
   }
   
   fclose(in);
   fclose(out);
}


/* Test data format
   input file name : 2lin_ang.in
   sample input :
      4
      1 0 -1 0 0 1 0 -1
      0 0 1 0 0 0 1 1
      0 0 1 0 0 0 -1 0
      4 0 5 0 0 0 -100 -100

   sample output (file 2lin_ang.out):
      1.570796
      0.785398
      0.000000
      0.785398
*/
