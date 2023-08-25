#include <bits/stdc++.h>
#include <map>
#include <vector>
#include <time.h>
using namespace std;
using namespace chrono;

typedef vector<int> vi;
#define dbg(x) cout<<"("<<#x<<" = "<<x<<")"<<endl
#define f(i,a,b) for(int i = a; i < b; i++)
#define rf(i,a,b) for(int i = a; i > b; i--)
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vii;
typedef vector<vii> vvii;
typedef vector<pii> vpii;
#define vv vector
#define ln "\n"
#define pb push_back
#define f(i,a,b) for(ll i=a;i<b;i++)
#define fb(i,a,b) for(ll i=a;i>=b;i--)
#define fi(i,s) for(auto& i=s.begin();i!=s.end();i++)
#define fr(i,s) for(auto i=s.rbegin();i!=s.rend();i++)
#define fv(i,s) for( auto& i : s)
#define fp(k,v,s) for( auto& [k,v] : s)
#define ft(u,v,d,s) for( auto& [u,v,d] : s)
#define in insert
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())
#define isin(s,x) (s.find(x)!=s.end())
#define isinv(s,x) (find(all(s),x)!=s.end())
#define isins(s,x) (s.find(x)!=string::npos)
#define idx(s,x) (find(all(s),x)-s.begin())
#define rm(s,x) (s.erase(find(all(s),x)))
#define Start auto start=high_resolution_clock::now()
#define End(u) auto stop=high_resolution_clock::now();\
auto duration=duration_cast<u>(stop-start);\
cout<<"\nTime:"<<duration.count()<<" "<<#u<<endl;

struct point{ // point data structure
	int x;
	int y;
	float attribute = 0;
};

struct edge{ // graph data structure
	point p1;
	point p2;
};

typedef vector<point> vp;  // vector of points
typedef vector<edge> graph; // graph

ostream& operator<<(ostream& out,point&v){
    out<<"("<<v.x<<","<<v.y<<","<<v.attribute<<"),";
    return out;
}

inline bool operator<(const point& l, const point& r){
  return pair(l.x,l.y) < pair(r.x,r.y);
}
inline bool operator==(const point& l, const point& r){
  return (l.x==r.x)&&(l.y==r.y)&&(l.attribute==r.attribute);
}
void print_points(vp point_set){  // given a vector of points, it prints the coordinates
	int n = point_set.size();  // length of the vector
	f(i,0,n){
		cout<<"("<<point_set[i].x<<","<<point_set[i].y<<") ";
	}
// 	cout<<endl;
}

int flutely(graph edgeList){
	vv<point> ps,pt,p;
	fp(u,v,edgeList){
		if(u.attribute&&!isinv(ps,u))ps.pb(u);else if(!u.attribute&&!isinv(pt,u))pt.pb(u);
		if(v.attribute&&!isinv(ps,v))ps.pb(v);else if(!v.attribute&&!isinv(pt,v))pt.pb(v);
	}
	vpii pos;
	fv(i,pt)p.pb(i);
	fv(i,ps)p.pb(i);
	ft(x,y,a,p)pos.pb({x,y});
	int t=sz(pt),s=sz(ps),n=t+s;
    vvii adjList(t+s);
    fp(p1,p2,edgeList){
    	int u=idx(p,p1),v=idx(p,p2);
        adjList[u].pb(v);
        adjList[v].pb(u);
    }
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
int main(int argc, char* argv[]){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	cin>>n;
	graph tree;			
	// cout<<n<<endl;
	f(i,1,n+1){
		// Bar(i,n);
		f(j,0,k){
			cin>>p.x>>p.y;
		}
		// cout<<"Wirelength:"<<length;
		// print_edge_list(tree);
		int spts=flutely(tree);
	    // fprintf(file,"Num_Terminals = %d\nWirelength = %d\nNum Steiner Points = %d\nCPU Time = %lf sec\n",k,length,spts,time);
		// End(milliseconds);
	}	
	return 0;
}