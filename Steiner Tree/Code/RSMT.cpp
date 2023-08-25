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

vp merge(vp seq1, vp seq2, int n1, int n2){ // given two sorted sets, merges them so that the combined set is also sorted
	vp merged(n1 + n2);
	int i1,i2;
	i1 = i2 = 0;

	// cout<<"seq1";
	// print_points(seq1);
	// cout<<"seq2";
	// print_points(seq2);

	while(i1 < n1 || i2 < n2){   // there are still points that have not been processed
		// cout<<i1<<" "<<i2<<endl;
		if(i1 == n1){  // all points in set 1 have been processed
			merged[i1 + i2].x = seq2[i2].x;
			merged[i1 + i2].y = seq2[i2].y;
			merged[i1 + i2].attribute = seq2[i2].attribute;

			i2++;
		}
		else if(i2 == n2){  // all points in set 2 have been processed
			merged[i1 + i2].x = seq1[i1].x;
			merged[i1 + i2].y = seq1[i1].y;
			merged[i1 + i2].attribute = seq1[i1].attribute;

			i1++;
		}
		else{  // there are unprocessed points in both sets 1 and 2
			if(seq1[i1].attribute <= seq2[i2].attribute){
				merged[i1 + i2].x = seq1[i1].x;
				merged[i1 + i2].y = seq1[i1].y;
				merged[i1 + i2].attribute = seq1[i1].attribute;

				i1++;
			} // nested if ends here
			else{
				merged[i1 + i2].x = seq2[i2].x;
				merged[i1 + i2].y = seq2[i2].y;
				merged[i1 + i2].attribute = seq2[i2].attribute;

				i2++;
			} // nested else ends here
			// cout<<"check"<<merged[i1+i2-1]<<endl;
		}// else ends here
		// cout<<merged[i1 + i2-1]<<endl;
	}// while loop ends here
	// cout<<"check!"<<endl;
	// f(i,0,n1+n2){
	// 	cout<<merged[i]<<" ";
	// }
	// cout<<endl;

	return merged;  // the merged, sorted vector of points

}

vp merge_sort(vp unsorted, int size){
	vp sorted(size);
	// cout<<"size"<<size<<endl;
	// print_points(unsorted);
	// cout<<"unsorted"<<endl;
	// f(i,0,size){
	// 	cout<<unsorted[i]<<" ";
	// }
	// cout<<endl;

	if(size == 1)
		return unsorted;
	else{
		int m = size / 2;  // take a middle point
		vp sort1(m);    // first m points
		vp sort2(size-m);  // remaining points

		f(i,0,m){
			sort1[i].x = unsorted[i].x;
			sort1[i].y = unsorted[i].y;
			sort1[i].attribute = unsorted[i].attribute;
		}

		f(i,m,size){
			sort2[i-m].x = unsorted[i].x;
			sort2[i-m].y = unsorted[i].y;
			sort2[i-m].attribute = unsorted[i].attribute;
		}

		sort1 = merge_sort(sort1, m);        // recursion
		sort2 = merge_sort(sort2, size-m);

		sorted = merge(sort1, sort2, m, size-m);
		// cout<<"merge sort";
		// print_points(sorted);
		// cout<<"sorted"<<endl;
		// f(i,0,size){
		// 	cout<<sorted[i]<<" ";
		// }
		// cout<<endl;

		return sorted; // sorted vector of points
	}
}

double full_set_wt(vp set, int k, int type){  // returns weight of steiner tree
	// cout<<"\n"<<set.size();
	for(int i = 0; i < k; i++)
	{
		set[i].attribute = set[i].x;
	}
	// cout<<"\nFULL SET WT \n";

	vp sortx_set = merge_sort(set, k);

	f(i,0,k){
		set[i].attribute = set[i].y;
	}

	vp sorty_set = merge_sort(set, k);
	// print_points(sorty_set);

	double wt = 0;  // weight of steiner tree

	if(type == 1 | type == 2){
		wt += sortx_set[k-1].x - sortx_set[0].x;
		if(type == 1){
			f(i,1,k){
				wt += abs(sortx_set[i].y - sortx_set[0].y);
			}
		}
		else if(type == 2){
			f(i,0,k-1){
				wt += abs(sortx_set[i].y - sortx_set[k-1].y);
			}
		}
	}
	else if(type == 3 | type == 4){
		wt += sorty_set[k-1].y - sorty_set[0].y;
		if(type == 3){
			f(i,1,k){
				wt += abs(sorty_set[i].x - sorty_set[0].x);
			}
		}
		else if(type == 4){
			f(i,0,k-1){
				wt += abs(sorty_set[i].x - sorty_set[k-1].x);
			}
		}
	}
	else if(type == 5 | type == 6){
		wt += sortx_set[k-1].x - sortx_set[0].x;
		if(type == 5){
			f(i,1,k-1){
				wt += abs(sortx_set[i].y - sortx_set[0].y);
			}
		}
		else if(type == 6){
			f(i,1,k-1){
				wt += abs(sortx_set[i].y - sortx_set[k-1].y);
			}
		}
	}
	else if(type == 7 | type == 8){
		wt += sorty_set[k-1].y - sorty_set[0].y;
		if(type == 7){
			f(i,1,k-1){
				wt += abs(sorty_set[i].x - sorty_set[0].x);
			}
		}
		else if(type == 8){
			f(i,1,k-1){
				wt += abs(sorty_set[i].x - sorty_set[k-1].x);
				// cout<<"line 190 "<<i<<" "<<wt<<endl;
			}
		}
	}
	// cout<<"line 195 "<<"type="<<type<<" wt="<<wt<<endl;

	if(k==1) 
		wt = 0;
	// if(k==2)
	// 	wt = abs(set[1].x-set[0].x)+abs(set[1].y-set[0].y);


	return wt;
}

int net_type(vp pts, int k){
	f(i,0,k){
		pts[i].attribute = pts[i].x;
	}

	vp sortx_pts = merge_sort(pts, k);

	f(i,0,k){
		pts[i].attribute = pts[i].y;
	}

	vp sorty_pts = merge_sort(pts, k);

	int a = sortx_pts[0].y;
	int b = sortx_pts[k-1].y;
	
	int p = sorty_pts[0].x;
	int q = sorty_pts[k-1].x;
	
	// cout<<"line 146\n";

	int type1 = 1;          // horizontal type 1 with extreme terminal on the left
	int type2 = 1;			// horizontal type 1 with extreme terminal on the right
	int type3 = 1;			// vertical type 1 with extreme terminal in the bottom
	int type4 = 1;			// vertical type 1 with extreme terminal at the top

	int type5 = (k>3)&(sortx_pts[k-2].x!=sortx_pts[k-1].x)?1:0;    // horizontal type 2 with extreme terminal on the left
	int type6 = (k>3)&(sortx_pts[0].x!=sortx_pts[1].x)?1:0;	// horizontal type 2 with extreme terminal on the right
	int type7 = (k>3)&(sorty_pts[k-2].y!=sorty_pts[k-1].y)?1:0;	// vertical type 2 with extreme terminal in the bottom
	int type8 = (k>3)&(sorty_pts[0].y!=sorty_pts[1].y)?1:0;	// vertical type 2 with extreme terminal at the top

	// horizontal circuits
	f(i,1,(k-1)){
		if((sortx_pts[i].y-a)*(sortx_pts[i+1].y-a)>0)
			type1 = 0;
		// cout<<type1<<"line 162\n";
	}

	f(i,0,(k-2)){
		if((sortx_pts[i].y-b)*(sortx_pts[i+1].y-b)>0)
			type2 = 0;
		// cout<<type2<<"line 168\n";
	}

	f(i,1,(k-2)){
		if((sortx_pts[i].y-a)*(sortx_pts[i+1].y-a)>0)
			type5 = 0;
		// cout<<type5<<"line 174\n";
	}
	if((sortx_pts[k-2].y-a)*(sortx_pts[k-1].y-a)<0 | abs(sortx_pts[k-2].y-a)<abs(sortx_pts[k-1].y-a))
		type5 = 0;
	// cout<<type5<<"line 177\n";

	f(i,1,(k-2)){
		if((sortx_pts[i].y-b)*(sortx_pts[i+1].y-b)>0)
			type6 = 0;
		// cout<<type6<<"line 183\n";
	}
	if((sortx_pts[0].y-b)*(sortx_pts[1].y-b)<0 | abs(sortx_pts[0].y-b)>abs(sortx_pts[1].y-b))
		type6 = 0;
	// cout<<type6<<"line 187\n";

	// vertical circuits
	f(i,1,(k-1)){
		if((sorty_pts[i].x-p)*(sorty_pts[i+1].x-p)>0)
			type3 = 0;
		// cout<<type3<<"line 193\n";
	}

	f(i,0,(k-2)){
		if((sorty_pts[i].x-q)*(sorty_pts[i+1].x-q)>0)
			type4 = 0;
		// cout<<type4<<"line 199\n";
	}

	f(i,1,(k-2)){
		if((sorty_pts[i].x-p)*(sorty_pts[i+1].x-p)>0)
			type7 = 0;
		// cout<<type7<<"line 205\n";
	}
	if((sorty_pts[k-2].x-p)*(sorty_pts[k-1].x-p)<0 | abs(sorty_pts[k-2].x-p)<abs(sorty_pts[k-1].x-p))
		type7 = 0;
	// cout<<type7<<"line 209\n";

	f(i,1,(k-2)){
		if((sorty_pts[i].x-q)*(sorty_pts[i+1].x-q)>0)
			type8 = 0;
		// cout<<type8<<"line 214\n";
	}
	if((sorty_pts[0].x-q)*(sorty_pts[1].x-q)<0 | abs(sorty_pts[0].x-q)>abs(sorty_pts[1].x-q))
		type8 = 0;
	// cout<<type8<<"line 218\n";

	int type = 0;
	double wt = DBL_MAX;

	// cout<<"TOT "<<type1+type2+type3+type4+type5+type6+type7+type8<<"\n";

	if(type1 == 1){
		// cout<<"TYPE 1"<<endl;
		if(wt>full_set_wt(pts,k,1)){
			wt = full_set_wt(pts,k,1);
			type = 1;
			// cout<<"TYPE 1 "<<wt<<endl;
		}
	}
	if(type2 == 1){
		// cout<<"TYPE 2"<<endl;
		if(wt>full_set_wt(pts,k,2)){
			wt = full_set_wt(pts,k,2);
			type = 2;
			// cout<<"TYPE 2 "<<wt<<endl;
		}
	}
	if(type3 == 1){
		// cout<<"TYPE 3"<<endl;
		if(wt>full_set_wt(pts,k,3)){
			wt = full_set_wt(pts,k,3);
			type = 3;
			// cout<<"TYPE 3 "<<wt<<endl;
		}
	}
	if(type4 == 1){
		// cout<<"TYPE 4"<<endl;
		if(wt>full_set_wt(pts,k,4)){
			wt = full_set_wt(pts,k,4);
			type = 4;
			// cout<<"TYPE 4 "<<wt<<endl;
		}
	}
	if(type5 == 1){
		// cout<<"TYPE 5"<<endl;
		if(wt>full_set_wt(pts,k,5)){
			wt = full_set_wt(pts,k,5);
			type = 5;
			// cout<<"TYPE 5 "<<wt<<endl;
		}
	}
	if(type6 == 1){
		// cout<<"TYPE 6"<<endl;
		if(wt>full_set_wt(pts,k,6)){
			wt = full_set_wt(pts,k,6);
			type = 6;
			// cout<<"TYPE 6 "<<wt<<endl;
		}
	}
	if(type7 == 1){
		// cout<<"TYPE 7"<<endl;
		if(wt>full_set_wt(pts,k,7)){
			wt = full_set_wt(pts,k,7);
			type = 7;
			// cout<<"TYPE 7 "<<wt<<endl;
		}
	}
	if(type8 == 1){
		// cout<<"TYPE 8"<<endl;
		if(wt>full_set_wt(pts,k,8)){
			wt = full_set_wt(pts,k,8);
			type = 8;
			// cout<<"TYPE 8 "<<wt<<endl;
		}
	}

	return type;
}

vp toSubset(vp pts, int n, int k){
	vp subset;
	f(i,0,k){
		if(n%2 == 1)
			subset.push_back(pts[i]);
		n = n/2;
		// cout<<"iter "<<i<<", n = "<<n<<endl;
	}

	return subset;
}

vi candidateFull(vp pins, int k){
	int n = (int)pow(2,k);
	int size;
	vp subset;
	vi full;
	// cout<<n<<"\n";

	f(i,1,n){
	  // try{	
		// cout<<"line 381 "<<i<<"\n";
		subset = toSubset(pins, i, k);
		// cout<<"line 382\n";
		// print_points(subset);
		// cout<<"line 383\n";
		size = subset.size();
		full.push_back(net_type(subset, size));
		// cout<<"line 377 "<<i<<" "<<subset.size()<<"\n";

	  // }
	  // catch(...){cout<<"error!!!!!!\n";}

	
	}
	// cout<<"FULL\n";
	// f(i,0,full.size()){
	// 	cout<<full[i]<<" ";
	// }
	// cout<<"\n";
	return full;
}

vi all_subsets(int n, int k){
	vi subsets;
	vi ones;
	f(i,0,k){
		if(n%2==1)
			ones.push_back(i);
		n = n/2;
	}

	int l = ones.size();
	vi coeff;
	int num,sum;
	f(i,1,pow(2,l)){
		num = i;
		sum = 0;
		f(j,0,l){
			sum += (num%2)*pow(2,ones[j]);
			num = num/2;
		}
		subsets.push_back(sum);
	}

	return subsets;
}

vi steinerTreeValues(vp pins, int k){
	int n = (int)pow(2,k)-1;
	vi values;
	// cout<<"line 421\n";
	vi F = candidateFull(pins,k);
	// cout<<"F HEREEEE "<<F.size()<<"\n";
	// f(i,0,n){
	// 	cout<<F[i]<<" ";
	// }
	// cout<<"\nline 433 HEREEEEEEE\n";
	vi subsets;
	vi subsubsets;
	vp pts;
	int a,b;
	int num;
	int l;
	double min;
    vp dummy;
    double dummy2;

	f(i,1,(n+1)){
			dummy = toSubset(pins,i,k);
			if(F[i-1]>0){
				min = full_set_wt(dummy, dummy.size(), F[i-1]);
				// cout<<min<<endl;
			}
			else
				min = DBL_MAX;
			num = i;
			subsets = all_subsets(i,k);
			
			f(j,0,(subsets.size()-1)){
				// cout<<"\nF = "<<F[subsets[j]-1]<<endl;
				if(F[subsets[j]-1]==0)
					continue;

				// pts = toSubset(pins,	 subsets[j], k);
				a = subsets[j];

				// cout<<"a = "<<a<<endl;
				b = i - a;
				// cout<<"b = "<<b<<endl;

				// cout<<"A";
				// print_points(toSubset(pins, a, k));

				// cout<<"B";
				// print_points(toSubset(pins, b, k));

				subsubsets = all_subsets(a,k);
				// cout<<"SUBSUBSETS\n";
				// f(x,0,subsubsets.size()){
				// 	cout<<subsubsets[x]<<" ";
				// }
				// cout<<endl;

				l = floor(log2(subsubsets.size()+1));

				// cout<<"l = "<<l<<endl;

				if(l==1)
					continue;

				// f(x,0,l){
				// 	print_points(toSubset(pins, subsubsets[pow(2,x)-1], k));
				// }
				f(x,0,l){
					if(min>values[a-1] + values[b-1+subsubsets[pow(2,x)-1]]){
						// if(i==n){
						// 	cout<<"\n"<<values[a-1]<<" "<<values[b-1+subsubsets[pow(2,x)-1]];
						// 	cout<<"\n"<<min<<">"<<values[a-1] + values[b-1+subsubsets[pow(2,x)-1]];
						// }
						// cout<<endl;
						min = values[a-1] + values[b-1+subsubsets[pow(2,x)-1]];
					}
					
					// cout<<"\nMIN = "<<min<<endl;
				}
			}
			values.push_back(min);
		
	}

	return values;
}

void print_edge_list(graph tree){
	int k = tree.size();
	// cout<<endl;
	f(i,0,k){
		cout<<"("<<tree[i].p1.x<<" "<<tree[i].p1.y<<") ("<<tree[i].p2.x<<" "<<tree[i].p2.y<<")  ";
		cout<<tree[i].p1.attribute<<" "<<tree[i].p2.attribute<<endl;
	}
}

graph full_tree(vp pins, int type){
	graph full;
	edge e1;

	int k = pins.size();

	f(i,0,k){
		pins[i].attribute = pins[i].x;
	}

	vp sortx_pts = merge_sort(pins, k);

	f(i,0,k){
		pins[i].attribute = pins[i].y;
	}

	vp sorty_pts = merge_sort(pins, k);

	if(k==2){
		e1.p1 = pins[0];
		e1.p1.attribute = 0;
		e1.p2 = pins[1];
		e1.p2.attribute = 0;
		full.push_back(e1);
	}
	else if(type==1 || type == 2){ // horizontal type 1
		e1.p1 = sortx_pts[0];
		e1.p1.attribute = 0;
		e1.p2.x = sortx_pts[1].x;
		e1.p2.y = type==1?sortx_pts[0].y:sortx_pts[k-1].y;
		e1.p2.attribute = 1;
		full.push_back(e1);

		f(i,1,k-1){
			e1.p1 = sortx_pts[i];
			e1.p1.attribute = 0;

			e1.p2.x = sortx_pts[i].x;
			e1.p2.y = type==1?sortx_pts[0].y:sortx_pts[k-1].y; 
			e1.p2.attribute = 1;

			full.push_back(e1);
		}

		e1.p1.x = sortx_pts[k-2].x;
		e1.p1.y = type==1?sortx_pts[0].y:sortx_pts[k-1].y;
		e1.p1.attribute = 1;
		e1.p2 = sortx_pts[k-1];
		e1.p2.attribute = 0;
		full.push_back(e1);

		f(i,1,k-2){
			e1.p1.x = sortx_pts[i].x;
			e1.p1.y = type==1?sortx_pts[0].y:sortx_pts[k-1].y;
			e1.p1.attribute = 1;

			e1.p2.x = sortx_pts[i+1].x;
			e1.p2.y = type==1?sortx_pts[0].y:sortx_pts[k-1].y;
			e1.p2.attribute = 1;

			full.push_back(e1);
		}
	}
	else if(type==3 || type==4){ // vertical type 1
		e1.p1 = sorty_pts[0];
		e1.p1.attribute = 0;
		e1.p2.y = sorty_pts[1].y;
		e1.p2.x = type==3?sorty_pts[0].x:sorty_pts[k-1].x;
		e1.p2.attribute = 1;
		full.push_back(e1);

		f(i,1,k-1){
			e1.p1 = sorty_pts[i];
			e1.p1.attribute = 0;

			e1.p2.y = sorty_pts[i].y;
			e1.p2.x = type==3?sorty_pts[0].x:sorty_pts[k-1].x; 
			e1.p2.attribute = 1;

			full.push_back(e1);
		}

		e1.p1.y = sorty_pts[k-2].y;
		e1.p1.x = type==3?sorty_pts[0].x:sorty_pts[k-1].x;
		e1.p1.attribute = 1;
		e1.p2 = sorty_pts[k-1];
		e1.p2.attribute = 0;
		full.push_back(e1);

		f(i,1,k-2){
			e1.p1.y = sorty_pts[i].y;
			e1.p1.x = type==3?sorty_pts[0].x:sorty_pts[k-1].x;
			e1.p1.attribute = 1;

			e1.p2.y = sorty_pts[i+1].y;
			e1.p2.x = type==3?sorty_pts[0].x:sorty_pts[k-1].x;
			e1.p2.attribute = 1;

			full.push_back(e1);
		}
	}
	else if(type==5 || type==6){ // horizontal type 2
		e1.p1 = sortx_pts[0];
		e1.p1.attribute = 0;
		e1.p2.x = sortx_pts[1].x;
		e1.p2.y = sortx_pts[0].y;
		e1.p2.attribute = 1;
		full.push_back(e1);

		f(i,1,k-1){
			e1.p1 = sortx_pts[i];
			e1.p1.attribute = 0;

			e1.p2.x = sortx_pts[i].x;
			e1.p2.y = type==5?sortx_pts[0].y:sortx_pts[k-1].y; 
			e1.p2.attribute = 1;

			if(type==5 && i==k-2)
				e1.p2.y = sortx_pts[k-1].y;
			else if(type==6 && i==1)
				e1.p2.y = sortx_pts[0].y;

			full.push_back(e1);
		}

		e1.p1.x = sortx_pts[k-2].x;
		e1.p1.y = sortx_pts[k-1].y;
		e1.p1.attribute = 1;
		e1.p2 = sortx_pts[k-1];
		e1.p2.attribute = 0;
		full.push_back(e1);

		f(i,1,k-2){
			e1.p1.x = sortx_pts[i].x;
			e1.p1.y = type==5?sortx_pts[0].y:sortx_pts[k-1].y;
			e1.p1.attribute = 1;

			e1.p2.x = sortx_pts[i+1].x;
			e1.p2.y = type==5?sortx_pts[0].y:sortx_pts[k-1].y;
			e1.p2.attribute = 1;

			if(type==5 && i==k-3)
				e1.p2.y = sortx_pts[k-1].y;
			else if(type==6 && i==1)
				e1.p1.y = sortx_pts[0].y;

			full.push_back(e1);
		}
	}
	else if(type==7 || type==8){ // vertical type 2
		e1.p1 = sorty_pts[0];
		e1.p1.attribute = 0;
		e1.p2.y = sorty_pts[1].y;
		e1.p2.x = sorty_pts[0].x;
		e1.p2.attribute = 1;
		full.push_back(e1);

		f(i,1,k-1){
			e1.p1 = sorty_pts[i];
			e1.p1.attribute = 0;

			e1.p2.y = sorty_pts[i].y;
			e1.p2.x = type==7?sorty_pts[0].x:sorty_pts[k-1].x; 
			e1.p2.attribute = 1;

			if(type==7 && i==k-2)
				e1.p2.x = sorty_pts[k-1].x;
			else if(type==8 && i==1)
				e1.p2.x = sorty_pts[0].x;

			full.push_back(e1);
		}

		e1.p1.y = sorty_pts[k-2].y;
		e1.p1.x = sorty_pts[k-1].x;
		e1.p1.attribute = 1;
		e1.p2 = sorty_pts[k-1];
		e1.p2.attribute = 0;
		full.push_back(e1);

		f(i,1,k-2){
			e1.p1.y = sorty_pts[i].y;
			e1.p1.x = type==7?sorty_pts[0].x:sorty_pts[k-1].x;
			e1.p1.attribute = 1;

			e1.p2.y = sorty_pts[i+1].y;
			e1.p2.x = type==7?sorty_pts[0].x:sorty_pts[k-1].x;
			e1.p2.attribute = 1;

			if(type==7 && i==k-3)
				e1.p2.x = sortx_pts[k-1].x;
			else if(type==8 && i==1)
				e1.p1.x = sortx_pts[0].x;

			full.push_back(e1);
		}
	}

	return full;
}

graph steinerTree(vp pins, int k, vi F, vi values){
	vi subsets;
	vi subsubsets;
	vi Fs;
	vi val;
	vp pts;
	vp common_pts;
	point p;
	int a,b;
	int num;
	int l;
	double min;

    int min_a, min_b;
    int common;

    graph tree;
    graph fullTree;
    edge e;
	
	int n = values.size();
	


	if(F[n-1]>0 && full_set_wt(pins, k, F[n-1]) == values[n-1]){
		tree = full_tree(pins, F[n-1]);
	}
	else{
			min = values[n-1];
			// subsets = all_subsets(n,k);
			f(i,1,pow(2,k)){
				if(F[i-1]==0)
					continue;

				// cout<<"ITERATION "<<subsets[i]<<endl;

				a = i;
				b = n-a;
				// cout<<"a = "<<a<<" b = "<<b<<endl;

				subsets = all_subsets(a,k);
				l = floor(log2(subsets.size()+1));
				// cout<<"l = "<<l<<endl;

				if(l==1)
					continue;

				f(x,0,l){

					if(min >= values[a-1] + values[b-1+subsets[pow(2,x)-1]]){
						min_b = b + subsets[pow(2,x)-1];
						min_a = a;
						common = subsets[pow(2,x)-1];
						// cout<<"F[b] = "<<F[min_b-1]<<" F[a] = "<<F[min_a-1]<<endl;
						goto jump;
					}
				}
			}


			jump:
			
			common_pts.push_back(toSubset(pins, common, k)[0]);
			// cout<<"COMMON\n";
			// print_points(common_pt1);
			pts = toSubset(pins, min_a, k);
			subsets = all_subsets(min_a, k);
			f(i,0,subsets.size()){
				Fs.push_back(F[subsets[i]-1]);
				val.push_back(values[subsets[i]-1]);
			}

			fullTree = steinerTree(pts, pts.size(), Fs, val);

			Fs.clear();
			val.clear();

			f(i,0,fullTree.size()){
				tree.push_back(fullTree[i]);
			}

			pts = toSubset(pins, min_b, k);
			subsets = all_subsets(min_b, k);
			f(i,0,subsets.size()){
				Fs.push_back(F[subsets[i]-1]);
				val.push_back(values[subsets[i]-1]);
			}

			fullTree = steinerTree(pts, pts.size(), Fs, val);

			// f(i,0,fullTree.size()){
			// 	e = fullTree[i];
			// 	if(e.p1.x == common_pts[0].x && e.p1.y == common_pts[0].y){
			// 		fullTree[i].p1.attribute = 1;
			// 	}
			// 	if(e.p2.x == common_pts[0].x && e.p2.y == common_pts[0].y){
			// 		fullTree[i].p2.attribute = 1;
			// 	}
			// }
			f(i,0,fullTree.size()){
				tree.push_back(fullTree[i]);
			}	    
	}
	// wirelength=values[values.size()-1];
	return tree;
}
int flutely(graph edgeList){
	vv<point> ps,pt,p;
	fp(u,v,edgeList){
		if(u.attribute&&!isinv(ps,u))ps.pb(u);
		else if(!u.attribute&&!isinv(pt,u))pt.pb(u);
		if(v.attribute&&!isinv(ps,v))ps.pb(v);
		else if(!v.attribute&&!isinv(pt,v))pt.pb(v);
	}
	vpii pos;
	fv(i,pt)p.pb(i);
	fv(i,ps)p.pb(i);
	ft(x,y,a,p)pos.pb({x,y});
	int t=sz(pt),s=sz(ps),n=t+s;
    vvii adjList(n);
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
	// #ifndef ONLINE_JUDGE  
    //     freopen("input.txt","r",stdin);
    //     freopen("output.txt","w",stdout);
    // #endif
    char *fin = argv[1],*fout=argv[2],*flog=argv[3]; 
    freopen(fin,"r",stdin);
    freopen(fout,"w",stdout);
	FILE* file = fopen(flog,"w");	
    if (file == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }
    clock_t start, end;
	int n,k,length;
	cin>>n;
	// cout<<n<<endl;
	f(i,1,n+1){
		Bar(i,n);
		point p;
		vp pins;
		graph tree;	
		vi F;
		vi values;
    	fprintf(file,"////////////////////////////////////[Test Case %d]///////////////////////////////////\n",i);
		cin>>k;
		// dbg(k);
		// dbg(i);
		f(j,0,k){
			cin>>p.x>>p.y;
			// cout<<p.x<<" "<<p.y<<endl;
			pins.push_back(p);
			// print_points(pins);
		}
		// Start;
	    start = clock();
	    F = candidateFull(pins,k);
	    values = steinerTreeValues(pins,k);
	    length = values[values.size()-1];
		tree = steinerTree(pins, k, F, values);
		// cout<<"Main/pins.size at i = "<<i<<" is "<<pins.size()<<endl;
		// cout<<"Main/tree.size at i = "<<i<<" is "<<tree.size()<<endl;
		// cout<<"Wirelength:"<<length;

		// print_edge_list(tree);
		int spts=flutely(tree);
	    end = clock();
		cout<<endl;
	    double time= ((double)(end - start)) / CLOCKS_PER_SEC;
	    fprintf(file,"Num_Terminals = %d\nWirelength = %d\nNum Steiner Points = %d\nCPU Time = %lf sec\n",k,length,spts,time);

		// End(milliseconds);
	}
    fclose(file);		
	return 0;
}