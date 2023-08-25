/*
(Windows/DOS)cmd>wsl g++ -O3  -Ilp_solve_2.3  -Wall  -o demo2cpp demo2.cpp memory.o -L./ -lgeosteiner lp_solve_2.3/libLPS.a -lm &&wsl ./democpp 
(UNIX/Linus)bash>g++ -O3  -Ilp_solve_2.3  -Wall  -o demo2cpp demo2.cpp memory.o -L./ -lgeosteiner lp_solve_2.3/libLPS.a  -lm &&./democpp
*/
#include <bits/stdc++.h>
#include "geosteiner.h"
using namespace std;
using namespace chrono;

typedef long long ll;
typedef short unsigned su;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<ld> vld;
typedef pair<double,double> pdd;
typedef vector<ll> vll;
typedef vector<int> vii;
typedef vector<vii> vvii;
typedef vector<vll> vvll;
typedef vector<vld> vvld;
typedef vector<pll> vpll;
typedef vector<pii> vpii;
typedef vector<pdd> vpdd;
typedef vector<vpll> vvpll;
typedef vector<string> vss;
typedef vector<vector<string>> vvss;
typedef list<pdd>dlp;

const ll MOD=ll(104857601);
const double pi= 3.141592653589;
const double eps = 1e-12;
#define vv vector
#define pq priority_queue
#define us unordered_set 
#define ums unordered_multiset
#define um unordered_map 
#define umm unordered_multimap
#define f(i,a,b) for(ll i=a;i<b;i++)
#define fb(i,a,b) for(ll i=a;i>=b;i--)
#define fi(i,s) for(auto& i=s.begin();i!=s.end();i++)
#define fr(i,s) for(auto i=s.rbegin();i!=s.rend();i++)
#define fv(i,s) for( auto& i : s)
#define fp(k,v,s) for( auto& [k,v] : s)
#define ft(u,v,d,s) for( auto& [u,v,d] : s)
#define ln "\n"
#define dbg(x) cout<<"("<<#x<<" = "<<x<<")"<<ln
#define sp(x) <<fixed<<setprecision(x)
#define mp make_pair
#define mt make_tuple
#define ts tuple_size
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define reg register
#define ff first
#define ss second
#define in insert
#define ig ignore
#define popcount(x) __builtin_popcountll(x)
#define czr(x) __builtin_ctzll(x)
#define czl(x) __builtin_clzll(x)
#define pow2(n) (n & (~(n - 1)))
#define clrp(x,i) (x & (1 << i)-1)
#define clrs(x,i) (x & ~((1 <<i)-1))
#define isp2(x) (x && !(x & x-1))
#define LSB(i) ((i) & -(i))
#define rzb(x) ((x)&-(x))
#define INF int(2e8)
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define SET(name) freopen(name".txt", "r", stdin), freopen(name".txt", "w", stdout)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())
#define rez(s,n) s.clear(),s.resize(n)
#define rot(s,l,r,d) rotate(s.begin()+l,s.begin()+l+d,s.begin()+r+1)
#define eqr(s,x) equal_range(all(s),x)
#define ubd(s,x) upper_bound(all(s),x)-s.begin()
#define lbd(s,x) lower_bound(all(s),x)-s.begin()
#define idx(s,x) (find(all(s),x)-s.begin())
#define setv(s,x) memset(s,x,sizeof(s))
#define isin(s,x) (s.find(x)!=s.end())
#define isinv(s,x) (find(all(s),x)!=s.end())
#define isins(s,x) (s.find(x)!=string::npos)
#define rm(s,x) (s.erase(find(all(s),x)))
#define ad(i,k) advance(i,k)
#define pc putchar
// #define mat vv<vv<ld>>
#define Start auto start=high_resolution_clock::now()
#define End(u) auto stop=high_resolution_clock::now();\
auto duration=duration_cast<u>(stop-start);\
cout<<"\nTime:"<<duration.count()<<" "<<#u<<ln

inline int gc(){
  static char buf[1048576];
  static int s = 1048576;
  static int e = 1048576;
  if(s==e&&e==1048576){
    e=fread(buf, 1, 1048576, stdin);
    s=0;
  }
  if(s == e)return EOF;
  return buf[s++];
}
template<class T=int>
inline T read(){
    T c=gc(),t=1,n=0;
    if(c==' '||c=='\n'||c=='\r'||c=='\t'||c==EOF)c=gc();
    if(c=='-'){t=-1,c=gc();}
    while(isdigit(c)){n=n*10+c-'0',c=gc();}
    return n*t;
}
template<class T=int>
inline void write(T x){
    if (x<0){
        pc('-');
        x*=-1;
    }
    if(x<10)pc(x+'0');
    else{
        write(x/10);
        pc(x%10+'0');
    }
}
template<class T=int>
inline void print(T x,char c='\n'){
    write(x);
    pc(c);
}
template<class T>
ostream& operator<<(ostream& out,vv<T>&v){
    fv(i,v)out<<i<<" ";
    out<<ln;
    return out;
}
template<class T>
istream& operator>>(istream& inp,vv<T>&v){
    if(sz(v))fv(i,v)inp>>i;
    else{
        T t;
        string l;
        inp>>t;
        v.pb(t);
        getline(inp,l);
        istringstream iss(l);
        while(iss>>t)v.pb(t);
    }
    return inp;
}
template<class T>
istream& operator>>(istream& inp,vv<vv<T>>&A){
    fv(i,A)inp>>i;
    return inp;
}
template<class A,class B>
ostream& operator<<(ostream& out,pair<A,B>p){
    out<<"("<<p.ff<<","<<p.ss<<")";
    return out;
}
template<class A,class B>
istream& operator>>(istream& inp,pair<A,B>&p){
    inp>>p.ff>>p.ss;
    return inp;
}
template<class T>
ostream& operator<<(ostream& out,vv<vv<T>>A){
    fv(i,A)out<<i;
    return out;
}		
int len(ll n){
    int l=0;
    while(n>0)l++,n/=10;
    return l;
}
ll gcd(ll u,ll v){
    ll sft;
    if(u==0)return v;
    if(v==0)return u;
    sft=czr(u|v);
    u>>=czr(u);
    do{
        v>>=czr(v);
        if(u > v)swap(u, v);
        v-= u;
    }while(v!=0);
    return u<<sft;
}
ll lcm(ll u,ll v){return (u/gcd(u,v))*v;}
int sum(vvii aux,int i,int j,int a,int b){
    int res=aux[i+a-1][j+b-1];
    if(i>0)res-=aux[i-1][j+b-1];
    if(j>0)res-=aux[i+a-1][j-1];
    if(i>0&&j>0)res+=aux[i-1][j-1];
    return res;
}
vll vec(ll x){
    vll y;
    while(x){
        y.pb(x%10);
        x/=10;
    }
    return y;
} 
ll pow10(int n){
    ll t=1;
    f(i,0,n)t*=10;
    return t;
}
ll MSB(ll x){
    ll l=64-czl(x);
    return 1<<(l-1);
}
ll mpdt(ll a,ll b,ll mod=MOD){
    ll res=0;
    a%=mod;
    while(b){
        if(b&1)res=(res + a)%mod;
        a=(2*a)%mod;
        b>>=1;
    }
    return res;
}
ll egcd(ll a, ll b,ll&x,ll&y){
    if(a==0){
        x=0,y=1;
        return b;
    }
    ll x1,y1;
    ll gcd=egcd(b%a,a,x1,y1);
    x=y1-(b/a)*x1;
    y=x1;
    return gcd;
}
ll modi(ll b, ll m=MOD){
    ll x,y; 
    ll g=egcd(b,m,x,y);
    if (g!=1)return -1;
    return (x % m + m) % m;
}
ll mdiv(ll a, ll b,ll m=MOD){
    a=a%m;
    ll inv=modi(b,m);
    if(inv==-1)return 0;
    else return(inv*a)%m;
}
ll C(ll n,ll r,ll p){
    if(r>n)return 0;
    if(r>n-r)r=n-r;
    ll x=1;
    f(i,1,r+1){
        x=mpdt(x, (n + 1 - i), p);
        x=mdiv(x,i,p);
    }
    return x;
}
ll fmpow(ll b, ll p,ll m=MOD){
  if (p==0)return 1;
  ll t=fmpow(b,p/2);
  t=(t*t)%m;
  if (p%2==1)t*=b;
  return t%m;
}
ll fpow(ll b, ll p){
  if (p==0)return 1;
  ll t=fpow(b,p>>1);
  t*=t;
  if(p%2==1)t*=b;
  return t;
}
ll fpow2(ll p){
  if (p==0)return 1;
  ll t=fpow2(p>>1);
  t*=t;
  if (p&1)t<<=1;
  return t;
}
ll fmpow2(ll p,ll m=MOD){
  if (p==0)return 1;
  ll t=fmpow2(p>>1);
  t=(t*t)%m;
  if (p&1)t<<=1;
  return t%m;
}
ll fmod(const ll x,const ll M=MOD){
    return x>=M?x-M:x;
}
ll mod(ll a,ll b){return ((a%b)+b)%b; }
pll crt(ll a1,ll m1,ll a2,ll m2){
    ll s,t,g=egcd(m1,m2,s,t);
    if(a1%g!=a2% g)return pll(0,-1);
    s=mod(s*a2,m2);t=mod(t*a1,m1);
    ll r=mod(s*(m1/g)+t*(m2/g),m1/g*m2),M=m1/g*m2;
    return pll(r,M);
}
pll crt(const vll&a,const vll&m){
    if(sz(a)==1)return pll(a[0],m[0]);
    pll r=crt(a[0],m[0],a[1],m[1]);
    f(i,2,sz(a))r=crt(r.ff,r.ss,a[i],m[i]);
    return r;
}
template<class T>
set<T> operator+(set<T>s1,set<T>s2){
    set<T>si;
    auto itr=set_union(all(s1),all(s2),inserter(si,si.begin()));
    return si;
}
template<class T>
set<T> operator*(set<T>s1,set<T>s2){
    set<T>si;
    auto itr=set_intersection(all(s1),all(s2),inserter(si,si.begin()));
    return si;
}
template<class T>
set<T> operator-(set<T>s1,set<T>s2){
    set<T>si;
    auto itr=set_difference(all(s1),all(s2),inserter(si,si.begin()));
    return si;
}
template<class T>
set<T> operator^(set<T>s1,set<T>s2){
    set<T>si;
    auto itr=set_summetric_difference(all(s1),all(s2),inserter(si,si.begin()));
    return si;
}
template<class T>
struct Node{
    ll sum,lazy;
    bool mark;
    Node(){
        lazy=mark=sum=0;
    }
    Node(T x){
        sum=x;
    }
    Node operator+(const Node &Y)const{
        Node X;
        X.sum=sum+Y.sum;
        return X;
    }
};
#define MAX_EDGES int(1e5)
#define MAX_NSPS int(1e5)
int flutely(vpii pos,vpii edgeList, int t, int s){
    vvii adjList(t+s);
    fp(u,v,edgeList) {
        adjList[u].pb(v);
        adjList[v].pb(u);
    }
    int n = t + s;
    f(i,0,t)if(sz(adjList[i])>1){
        fv(j,adjList[i]){
            adjList[j].pb(n);
            rm(adjList[j],i);
        }
        adjList.pb(adjList[i]);
        adjList[n].pb(i);
        adjList[i]={n};
        pos.pb(pos[i]);
        n++;
    }
    vpii newList;
    set<int>seen;
    for(vvii::iterator adji=min_element(all(adjList),[](auto& l,auto& r){
        return sz(l)>0&&(sz(r)==0||sz(l)<sz(r));});adji!=adjList.end()&&adji->size()>0;
        adji=min_element(all(adjList),[](auto& l,auto& r){
        return sz(l)>0&&(sz(r)==0||sz(l)<sz(r));})){
	    	int i=distance(adjList.begin(),adji);
	    	int j = adjList[i][0];
	        adjList[i].erase(adjList[i].begin());
	        rm(adjList[j],i);
	        if(isin(seen,i))newList.pb({j,i}),seen.in(j);
	        else newList.pb({i,j}),seen.in(i);
    }
    sort(all(newList));
    fp(i,j,newList)
    	if(i<t)printf("%d %d %d %d\n",i,pos[i].ff,pos[i].ss,j);   
    	else printf("s%d %d %d %d\n",i,pos[i].ff,pos[i].ss,j); 
    printf("s%d %d %d %d\n",n-1,pos[n-1].ff,pos[n-1].ss,n-1); 
    return n-t;
}
int last_width=-1;
void Bar(int progress,int total,string txt="Status:",int width=50){
	float percent=float(progress)/total;
	int filledWidth=percent*width;
	if(filledWidth==last_width)return; 
	cerr<<ln<<txt;
    string progressBar(filledWidth,'#');
    string remainingSpace(width-filledWidth,'-');
    cerr<<"["<<progressBar<<remainingSpace<<"] "<<int(percent*100)<<"%\r";
    cerr.flush();
    last_width=filledWidth;
}
void solve(int u,FILE*file){
// void solve(int u){	
    clock_t start, end;
	int lambda = 1,n,nsps,status,nedges,edges[MAX_EDGES];
	cin>>n;
	double terms[2*n],spoints[MAX_NSPS],length,total_length=0.0,max_excess = 0.0,t;
	gst_metric_ptr metric;
	gst_param_ptr params;
	vpii v,e;
	fprintf(file,"////////////////////////////////////[Test Case %d]///////////////////////////////////\n",u);
	
	/* Set up metric */
	switch (lambda) {
	case 2: /* Euclidean metric */
		metric = gst_create_metric (GST_METRIC_L, 2, NULL); break;
	case 1: /* Rectilinear metric */
		metric = gst_create_metric (GST_METRIC_L, 1, NULL); break;
	default:/* General uniform metric */
		metric = gst_create_metric (GST_METRIC_UNIFORM, lambda, NULL);
	}

	/* Set up parameter set */
	params = gst_create_param (NULL);
	gst_set_dbl_param (params, GST_PARAM_GAP_TARGET, 1.0 + (max_excess/100.0));
	// dbg(n);

	/* Generate NUM_INSTANCES random instances with NUM_TERMS terminals */
	// srand48 (1);
	/* Generate random points with coordinates in range 0..9999 */
	for(int i=0;i<2*n;i+=2){
		cin>>terms[i]>>terms[i+1];
		v.pb(mp(terms[i],terms[i+1]));
	}
	/* Compute Steiner tree and print length */
    start = clock();
	// Start;
	gst_smt (n,terms,&length,&nsps,spoints,&nedges,edges,&status,metric, params);
	// End(milliseconds);
	end = clock();	
	// cout<<"Instance "<<u<<" has length "<<length<<ln;
	// total_length += length;
	// cout<<"Total length of all instances is "<<total_length<<ln;
	// switch (status) {
	// 	case GST_STATUS_OPTIMAL:
	// 		cout<<"GST_STATUS_OPTIMAL!\n"; break;
	// 	case GST_STATUS_FEASIBLE:
	// 		cout<<"GST_STATUS_FEASIBLE!\n"; break;
	// 	case GST_STATUS_INFEASIBLE:
	// 		cout<<"GST_STATUS_INFEASIBLE!\n"; break;
	// 	case GST_STATUS_NO_FEASIBLE:
	// 		cout<<"GST_STATUS_NO_FEASIBLE!\n"; break;

	// }
	// dbg(nsps);
	// dbg(nedges);

	// cout<<"Edges:";
	for(int i=0;i<2*nedges;i+=2){
		// printf("(%d,%d),",edges[i],edges[i+1]);
		e.pb(mp(edges[i],edges[i+1]));
	}
	// cout<<ln;
	// cout<<"Steiner Points:";
	for(int i=0;i<2*nsps;i+=2){
		// printf("(%d,%d),",int(spoints[i]),int(spoints[i+1]));
		v.pb(mp(int(spoints[i]),int(spoints[i+1])));
	}
	int s=flutely(v,e,n,nsps);
    double time= ((double)(end - start)) / CLOCKS_PER_SEC;
    fprintf(file,"Num_Terminals = %d\nWirelength = %d\nNum Steiner Points = %d\nCPU Time = %lf sec\n",n,int(length),s,time);
	cout<<ln;
	gst_free_metric (metric);
	gst_free_param (params);
}
int main(int argc, char* argv[]){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
	char *fin = argv[1],*fout=argv[2],*flog=argv[3]; 
    freopen(fin,"r",stdin);
    freopen(fout,"w",stdout);
	FILE* file = fopen(flog,"w");	
    if (file == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }
    /* Open GeoSteiner environment */
	if (gst_open_geosteiner () != 0) {
		cout<<"Could not open GeoSteiner.\n";
		return 0;
	}
    int u;//=read();
    cin>>u;
    f(i,0,u){
		Bar(i,u);
    	solve(i+1,file);
    	// solve(i+1);
	}
	gst_close_geosteiner ();
    fclose(file);		
    // cout<<0?sizeof(ll)*8-czl(0)-1:0;
    // f(i,1,u+1){cout<<"Case #"<<i<<":\n";solve();}
    return 0;
}