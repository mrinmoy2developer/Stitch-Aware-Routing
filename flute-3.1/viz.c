// #include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bookshelf_IO.h"
#include "memAlloc.h"
#include "flute.h"

#define f(i,a,b) for(reg ll i=a;i<b;i++)
#define fb(i,a,b) for(reg ll i=a;i>=b;i--)
#define fi(i,s) for(auto& i=s.begin();i!=s.end();i++)
#define fr(i,s) for(auto i=s.rbegin();i!=s.rend();i++)
#define fv(i,s) for( auto& i : s)
#define fp(k,v,s) for( auto& [k,v] : s)
#define ft(u,v,d,s) for( auto& [u,v,d] : s)
// using namespace std;

typedef long long ll;
typedef short unsigned su;
typedef unsigned long long ull;
typedef long double ld;

int main(){
    char benchmarkPath[BUFFERSIZE]="ibm01", auxFile[BUFFERSIZE]="ibm01.aux", placefile[BUFFERSIZE]="ibm01/ibm01.pl";
    readAuxFile(benchmarkPath, auxFile);
    createHash(benchmarkPath, nodesFile);
    readNodesFile(benchmarkPath, nodesFile);
    readNetsFile(benchmarkPath, netsFile);
    readPlFile(".", placefile);
    freeHash();
    printf("%d\n",numNets);
    printf("%d\n",numPins);
    for(int i=0; i<numNets; i++)printf("%d\n",netlist[i]);
    // readLUT();
    return 0;
}