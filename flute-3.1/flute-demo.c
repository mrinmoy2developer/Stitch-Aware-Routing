#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "flute.h"

void solve(int u,FILE*file){
    clock_t start, end;
	int d=0;
    int x[MAXD], y[MAXD];
    Tree flutetree;
    int flutewl;
    // printf("Enter the no. of terminals:");
    scanf("%d",&d);
    // printf("Enter the terminals:-\n");
    for (int i=0;i<d;i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    // printf("The Terminals are:");
    // for (int i=0;i<d;i++)printf("(%d,%d),",x[i],y[i]);
    start = clock();
    fprintf(file,"////////////////////////////////////[Test Case %d]///////////////////////////////////\n",u);
    flutetree = flute(d, x, y, ACCURACY);
    end = clock();
    double time= ((double)(end - start)) / CLOCKS_PER_SEC;
    int nspts=printtree(flutetree);
    fprintf(file,"Num_Terminals = %d\nWirelength = %d\nNum Steiner Points = %d\nCPU Time = %lf sec\n",d,flutetree.length,nspts,time);
    // printf("%d ",flutetree.length);
    // printf("\n");
    // flutewl = flute_wl(d, x, y, ACCURACY);
    // printf("FLUTE wirelength (without RSMT construction) = %d\n", flutewl);
}
int main(int argc, char* argv[]){
    char *fin = argv[1],*fout=argv[2],*flog=argv[3]; 
    freopen(fin,"r",stdin);
    freopen(fout,"w",stdout);
	FILE* file = fopen(flog,"w");	
    if (file == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }
    readLUT();
    int u;
    scanf("%d",&u);
    for (int i=0;i<u;i++)solve(i+1,file);
    fclose(file);
    return 0;
}
