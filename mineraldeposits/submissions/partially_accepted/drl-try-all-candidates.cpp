// # @EXPECTED_GRADES@ AC AC WA WA WA WA WA
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define com complex<double>
#define ld long double;
#define ii pair<ll,ll>
#define vi vector<int>
#define vll vector<ll>
#define vii vector<ii>
#define FOR(x,n) for(int x=0;x<(n);x++)
#define FORS(x,n) for(int x=1;x<=(n);x++)
#define FORE(x,a) for(auto &x: a)
#define FORT(x,a,b) for(int x=(a);x<(b);x++)
#define FORD(x,a,b) for(int x=(a);x>=(b);x--)
#define ALL(x) x.begin(),x.end()
#define REP(n) for(int _ = 0; _ < n; _++)
#define MT make_tuple
#define MP make_pair
#define pb push_back
#define F first
#define S second
#define vvvll vector<vvll>
#define sz(x) ((int)x.size())
int b,k,w;

int dist(ii x, ii y) {
    return abs(x.F - y.F) + abs(x.S - y.S);
}

vll query(vii qs) {
    cout << "? "; 
    FORE(q,qs) {
        cout << q.F << " " << q.S << " ";
    }
    cout << endl;

    vll res(k*qs.size());
    FOR(i,(k*sz(qs))) {
        cin >> res[i];
    }

    return res;
}


int main() {
    cin >> b >> k >> w;
    vll s = query({{-b,-b}});
    vll t = query({{-b,b}});
    set<ii> init;
    FORE(p,s) FORE(q,t) {
        if((p+q-2*b)%2) continue;
        ll x = (p + q - 2*b)/2-b;
        ll y = p - (b + x) - b;
        if(y < -b || y > b || x < -b || x > b) continue;
        init.insert({x,y});
    }
    vii pts(ALL(init));

    vii sol;
    FORE(p,pts) {
        vll r = query({p});
        if(find(ALL(r),0) != r.end()) sol.pb(p);
    }
    cout << "! ";
    FORE(s,sol) cout << s.F << " " << s.S << " ";
    cout << endl;
}