#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
using namespace std;

/*
  Author: Chuang Yi-Lin(²ø©öÀM)
  Purpose: 
    For a set of points on the 2-D plane ,find one minimum distance between two points
  NOTE:
	1. When minimum distance is greater than 10000 ,then output "INFINITY".
    2. Output minimum distance must to be 4 digits followed by the integer.
*/
struct point {
    double x, y;
    point() { x = y = 0.0; }
};

double dist( const point& p1, const point& p2 ) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool compare_x ( const point& p1,const point& p2 ) {
    return p1.x < p2.x;
}

bool compare_y ( const point& p1,const point& p2 ) {
    return p1.y < p2.y;
}

int min( int a, int b ) {
    if ( a < b )
        return a;
    else
        return b;
}

double closest_pair( vector< point >& p, point& close1, point& close2 );

double rec_cl_pair( vector< point >&p, 
                    int i,
                    int j,
                    point& close1,
                    point& close2 );


int main() {
    vector< point > p;
    point ptemp;
	int pointNum;
    fstream in,out;
     
	in.open("cl_pair.txt",ios::in);
    out.open("cl_pair_dist.txt",ios::out);

	while(in>>pointNum && pointNum!=0){
	   for(int i=0;i<pointNum;i++)
       {   in >> ptemp.x >> ptemp.y;
	       p.push_back( ptemp );
	   }
   
    point close1, close2;
    double delta=closest_pair( p, close1, close2 ) ;
	if(delta>=10000 || pointNum==1)
         out << "INFINITY" << '\n'; 
	else out<<setiosflags(ios::fixed)<<setprecision(4)<<delta<<endl;
    p.erase(p.begin(),p.end());

	}

    return 0;
}

double closest_pair( vector< point >& p, point& close1, point& close2 ) {
    point* start = &p[ 0 ];
    point* end = start + p.size();
    
    partial_sort( start, end, end, compare_x );
    return rec_cl_pair( p, 0, p.size() - 1, close1, close2 );
}

double rec_cl_pair( vector< point >&p, 
                    int i,
                    int j,
                    point& close1,
                    point& close2 ) {
    if ( j - i < 3 ) {//if there are only three points
        sort( &p[ i ], &p[ i ] + ( j - i + 1 ), compare_y );
        if ( j - i == 1 ) { 
            close1 = p[ i ];
            close2 = p[ j ];
        }
        else { 
            int p1 = i, p2 = i + 1;
            if ( dist( p[ i ], p[ i + 2 ] ) 
                < dist( p[ p1 ], p[ p2 ] ) )
                p2 = i + 1;
            if ( dist( p[ i + 1 ], p[ i + 2 ] ) 
                < dist( p[ p1 ], p[ p2 ] ) ) {
                p1 = i + 1;
                p2 = i + 2;
            }
            close1 = p[ p1 ];
            close2 = p[ p2 ];
        }
        return sqrt( dist( close1, close2 ) );
    }//recusive divide into two parts(left-right)
    int k = ( i + j ) / 2;
    int l = p[ k ].x;
    point cl1L, cl2L, cl1R, cl2R;
    double deltaL, deltaR, deltasq, delta;
    deltaL = rec_cl_pair( p, i, k, cl1L, cl2L );
    deltaR = rec_cl_pair( p, k + 1, j, cl1R, cl2R );
    if ( deltaL < deltaR ) {
        deltasq = deltaL * deltaL;
        close1 = cl1L;
        close2 = cl2L;
    }
    else {
        deltasq = deltaR * deltaR;
        close1 = cl1R;
        close2 = cl2R;
    }
    delta = sqrt( deltasq );

    vector< point > v( j - i + 1 );

    merge( &p[ i ], &p[ k ] + 1, &p[ k ] + 1, &p[ j ] + 1, 
        v.begin(), compare_y );

    int t;
    for ( t = i; t <= j; t++ )
        p[ t ] = v[ t - i ];

    t = -1;
    for ( k = i; k <= j; k++ )
        if ( p[ k ].x > l - delta && p[ k ].x < l + delta )
            v[ ++t ] = p[ k ];
    /*finally check if there exists the minimum distance between the central line
      within current minimum distance(compare nearly 6 points each point)*/ 
    int s;
    float dtemp;
    for ( k = 0; k < t; k++ )
        for ( s = k + 1; s <= min( t, k + 7 ); s++ ) {
            dtemp = dist( v[ k ], v[ s ] );
            if ( dtemp < deltasq ) {
                deltasq = dtemp;
                close1 = v[ k ];
                close2 = v[ s ];
            }
        }
    return sqrt( deltasq );
}


/*

test data format
input file name: cl_pair.txt

3                 //there are 3 points on the plane
0 0               //the first point's infomation(left is x-coordinate value,right is y-coordinate value)
10000 10000       //    second
20000 20000       //    third
5                 //there are 5 points on the plane
0 2
6 67
43 71
39 107
189 140
0                 //end input


output file name: cl_pair_dist.txt

INFINITY          //because the minimum distance is greater than 10000
36.2215           //output distance ,4 digit followed by the integer part

*/
