#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <string>
#include <cmath>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <functional>
#include <limits>
#include <random>
#include <chrono>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> pii;
typedef pair<int,ll> pil;
typedef vector<vector<int> > graph;

const double pi = acos(-1.0);

#define oned(a, x1, x2) { cout << #a << ":"; for(int _i = (x1); _i < (x2); _i++){ cout << " " << a[_i]; } cout << endl; }
#define twod(a, x1, x2, y1, y2) { cout << #a << ":" << endl; for(int _i = (x1); _i < (x2); _i++){ for(int _j = (y1); _j < (y2); _j++){ cout << (_j > y1 ? " " : "") << a[_i][_j]; } cout << endl; } }

#define mp make_pair
#define pb push_back
#define fst first
#define snd second

const int MAXN = 100005;

int a[MAXN];

int query(int i, int j) {
	cout << "? " << i << " " << j << endl;
	int val; cin >> val;
	return val;
}

pair<pii,int> solve(vector<int> x) {
	int n = x.size();
	int id1 = x[0];
	int id2 = x[1];
	int mx = query(id1,id2);
	for(int i = 2; i < n; i++) {
		int val1 = query(id1,x[i]);
		int val2 = query(id2,x[i]);
		if(mx == val1) {
			a[id1] = mx;
			id1 = x[i];
			mx = val2;
		} else if(mx == val2) {
			a[id2] = mx;
			id2 = x[i];
			mx = val1;
		} else {
			a[x[i]] = val1;
		}
	}
	return mp(mp(id1,id2),mx);
}

int main() {
	mt19937 rng(0);
	
	int n; cin >> n;
	for(int i = 1; i <= n; i++) {
		a[i] = 0;
	}
	
	vector<int> x;
	for(int i = 1; i <= n; i++) {
		x.pb(i);
	}
	shuffle(x.begin(), x.end(), rng);
	
	int t = min(n,int(3*sqrt(n)));

	vector<int> z(x.begin(),x.begin()+t);
	pair<pii,int> pid = solve(z);
	int id1 = pid.fst.fst;
	int id2 = pid.fst.snd;
	int mx = pid.snd;
	
	vector<int> y;
	y.pb(id1);
	y.pb(id2);
	for(int i = t; i < n; i++) {
		int val = query(id1,x[i]);
		if(val < mx) {
			a[x[i]] = val;
		} else {
			y.pb(x[i]);
		}
	}
	
	pair<pii,int> p = solve(y);
	
	a[p.fst.fst] = a[p.fst.snd] = p.snd;
	
	cout << "!";
	for(int i = 1; i <= n; i++) {
		cout << " " << a[i];
	}
	cout << endl;
}