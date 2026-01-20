/* longest common subsequence (cost by editor operations) */
/* (cost by insertion, deletion, replace, copy, twiddle) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 50
#define SIZE_N MAXLENGTH+1
#define INF 99999
#define COST_COPY 0
#define COST_DELETE 1
#define COST_INSERT 1
#define COST_REPLACE 1
#define COST_TWIDDLE 1

int MinValue(int a,int b,int c,int d,int e) {
	if( e < a && e < b && e < c && e < d )
		return e;
	else if( d < a && d < b && d < c )
		return d;
	else if( c < a && c < b )
		return c;
	else if( b < a )
		return b;
	else
		return a;
}

int CalCost(char src[],char dest[],int c[SIZE_N][SIZE_N],int i,int j) {
	int cn,dn,in,rn,tn;

	in = c[i][j-1] + COST_INSERT;
	dn = c[i-1][j] + COST_DELETE;
	if( src[i] == dest[j] )
		cn = c[i-1][j-1] + COST_COPY;
	else
		cn = INF;
	rn = c[i-1][j-1] + COST_REPLACE;
	if( i > 1 && j > 1 ) {
		if( src[i-1] == dest[j] && src[i] == dest[j-1] )
			tn = c[i-2][j-2] + COST_TWIDDLE;
		else
			tn = INF;
	}
	else
		tn = INF;
	return MinValue(cn,dn,in,rn,tn);
}

int GetTable(char src[SIZE_N],char dest[SIZE_N],int a[SIZE_N][SIZE_N]) {
	char srctemp[SIZE_N+1],desttemp[SIZE_N+1];
	int i,j,ibound,jbound;

	srctemp[0] = desttemp[0] = 0;
	strcpy(&srctemp[1],src);
	strcpy(&desttemp[1],dest);
	ibound = strlen(src);
	jbound = strlen(dest);
	a[0][0] = 0;
	for( i = 1 ; i <= ibound ; i++ )
		a[i][0] = a[i-1][0] + COST_DELETE;
	for( j = 1 ; j <= jbound ; j++ )
		a[0][j] = a[0][j-1] + COST_INSERT;
	for( i = 1 ; i < ibound ; i++ )
		for( j = 1 ; j < jbound ; j++ )
			a[i][j] = INF;
	for( j = 1 ; j <= jbound ; j++ )
		for( i = 1 ; i <= ibound ; i++ )
			a[i][j] = CalCost(srctemp,desttemp,a,i,j);
	return a[ibound][jbound];
}

int TraceStep(char src[SIZE_N],char dest[SIZE_N],int c[SIZE_N][SIZE_N],
		int i,int j,FILE *fp) {
	if( i == 0 && j == 0 )
		return 1;
	else if( i == 0 ) {
		TraceStep(src,dest,c,i,j-1,fp);
		fprintf(fp,"Insert %c\n",dest[j-1]);
		return 1;
	}
	else if( j == 0 ) {
		TraceStep(src,dest,c,i-1,j,fp);
		fprintf(fp,"Delete %c\n",src[i-1]);
		return 1;
	}
	if( i > 1 && j > 1 ) {
		if( src[i-2] == dest[j-1] && src[i-1] == dest[j-2] )
			if( c[i][j] == c[i-2][j-2] + COST_TWIDDLE ) {
				TraceStep(src,dest,c,i-2,j-2,fp);
				fprintf(fp,"Twiddle %c %c \n",src[i-2],src[i-1]);
				return 1;
			}
	}
	if( src[i-1] == dest[j-1] && c[i][j] == (c[i-1][j-1]+COST_COPY) ) {
		TraceStep(src,dest,c,i-1,j-1,fp);
		fprintf(fp,"Copy %c\n",src[i-1]);
		return 1;
	}
	else if( c[i][j] == (c[i-1][j-1]+COST_REPLACE) ) {
		TraceStep(src,dest,c,i-1,j-1,fp);
		fprintf(fp,"Replace %c with %c\n",src[i-1],dest[j-1]);
		return 1;
	}
	if( c[i][j] == (c[i-1][j]+COST_DELETE) ) {
		TraceStep(src,dest,c,i-1,j,fp);
		fprintf(fp,"Delete %c\n",src[i-1]);
		return 1;
	}
	if( c[i][j] == (c[i][j-1]+COST_INSERT) ) {
		TraceStep(src,dest,c,i,j-1,fp);
		fprintf(fp,"Insert %c\n",dest[j-1]);
		return 1;
	}
	return 0;
}

main() {
	char src[SIZE_N],dest[SIZE_N];
	int table[SIZE_N][SIZE_N];
	int ans,ibound,jbound;
	FILE *infp,*outfp;

	infp = fopen("lcs1.in","r");
	outfp = fopen("lcs1.out","w");
	fscanf(infp,"%s",src);
	fscanf(infp,"%s",dest);
	fclose(infp);
	ibound = strlen(src);
	jbound = strlen(dest);
	ans = GetTable(src,dest,table);
	fprintf(outfp,"From %s to %s need minimun cost %d\n",src,dest,ans);
	TraceStep(src,dest,table,ibound,jbound,outfp);
	fclose(outfp);
	return 0;
}

 /* test data format:
    input file name: lcs1.in
	Input just two lines, first line is original string,
	Second line is the string tended to transfer to be.
    input sample:
	abccdeefffhggk
	aaabcddefghlk

    output filename: lcs1.out
    sample output:
	From abccdeefffhggk to aaabcddefghlk need minimun cost 8
	Insert a
	Copy a
	Replace b with a
	Replace c with b
	Copy c
	Copy d
	Replace e with d
	Copy e
	Delete f
	Delete f
	Copy f
	Twiddle h g 
	Replace g with l
	Copy k
 */

