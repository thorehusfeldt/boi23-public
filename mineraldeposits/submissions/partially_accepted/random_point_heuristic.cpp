// # @EXPECTED_GRADES@ AC AC AC AC WA WA WA
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

    // Attempting to get somewhat random behaviour wihtout the issues with reproducibility at first.
    srand(42); 

    vll s = query({{-b,-b}});
    vll t = query({{-b,b}});
    set<ii> init;
    FORE(p,s) FORE(q,t) {
        if((p+q-2*b)%2) continue;
        ll x = (p + q - 2*b)/2-b;
        ll y = p - (b + x) - b;
        //cout << " " << x << " " << y << endl;
        if(y < -b || y > b || x < -b || x > b) continue;
        //cout << x << " " << y << endl;
        init.insert({x,y});
    }
    vii pts(ALL(init));

    vii sol;
    while(sz(pts) > 0) {
        int ri = rand() % pts.size();

        vll qr = query({pts[ri]});
        set<int> st(ALL(qr));
        
        vii nc;
        FORE(p,pts) {
            if(st.count(dist(p,pts[ri]))) {
                if(p == pts[ri]) {
                    sol.pb(p);
                } else {
                    nc.pb(p);
                }
            }
        }
        pts = nc;
    }
    cout << "! ";
    FORE(s,sol) cout << s.F << " " << s.S << " ";
    cout << endl;
}