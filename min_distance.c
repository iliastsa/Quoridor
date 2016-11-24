#include "data_structs.h"
#include "utility.h"

struct posi{
    int a,b;
};

void min_distance2(int x,int y,int siz,char A[100][100],int D[100][100]){
	int i,j,K,iQ[100][100],mind,mx,my;
 
	for (i=0; i<siz; i++)
	    for (j=0; j<siz; j++){
		    D[i][j]=1000;
		    iQ[i][j]=1;
	    }
	K=(siz/2+1)*(siz/2+1);
	D[x][y]=0;
 
	while (K>0){
		mind=1000;
		for (i=0; i<siz; i++)
		    for (j=0; j<siz; j++)
			    if (D[i][j]<mind && iQ[i][j]==1){
				    mind=D[i][j];
				    mx=i;
				    my=j;
			    }
		printf("-> %d %d\n",mx,my);
		K--;
		iQ[mx][my]=0;
		if (mx-2>=0 && A[mx-1][my]!='=' && iQ[mx-2][my]==1)
		    if (D[mx][my]+1<D[mx-2][my])
			    D[mx-2][my]=D[mx][my]+1;
		if (mx+2<siz && A[mx+1][my]!='=' && iQ[mx+2][my]==1)
		    if (D[mx][my]+1<D[mx+2][my])
			    D[mx+2][my]=D[mx][my]+1;
		if (my-2>=0 && A[mx][my-1]!='V' && iQ[mx][my-2]==1)
		    if (D[mx][my]+1<D[mx][my-2])
			    D[mx][my-2]=D[mx][my]+1;
		if (my+2<siz && A[mx][my+1]!='V' && iQ[mx][my+2]==1)
		    if (D[mx][my]+1<D[mx][my+2])
			    D[mx][my+2]=D[mx][my]+1;
	}
}


void min_distance(int x,int y,int siz,char A[100][100],int D[100][100]){
        int i,j,mx,my,bq=0,eq=0;
        struct posi ab,iQ[100];

        for (i=0; i<siz; i++)
                for (j=0; j<siz; j++)
                        D[i][j]=1000;

        ab.a=x;
        ab.b=y;
        iQ[0]=ab;
        D[x][y]=0;

        while (eq<=bq){
            mx=iQ[eq].a;
            my=iQ[eq].b;
            eq++;

            if (mx-2>=0 && A[mx-1][my]!='=')
                    if (D[mx-2][my]>=1000){
                            D[mx-2][my]=D[mx][my]+1;
                            bq++;
                            ab.a=mx-2;
                            ab.b=my;
                            iQ[bq]=ab;
                    }
            if (mx+2<siz && A[mx+1][my]!='=')
                    if (D[mx+2][my]>=1000){
                            D[mx+2][my]=D[mx][my]+1;
                            bq++;
                            ab.a=mx+2;
                            ab.b=my;
                            iQ[bq]=ab;
                    }
            if (my-2>=0 && A[mx][my-1]!='H')
                    if (D[mx][my-2]>=1000){
                            D[mx][my-2]=D[mx][my]+1;
                            bq++;
                            ab.a=mx;
                            ab.b=my-2;
                            iQ[bq]=ab;
                    }
            if (my+2<siz && A[mx][my+1]!='H')
                    if (D[mx][my+2]>=1000){
                            D[mx][my+2]=D[mx][my]+1;
                            bq++;
                            ab.a=mx;
                            ab.b=my+2;
                            iQ[bq]=ab;
                    }
        }
}
