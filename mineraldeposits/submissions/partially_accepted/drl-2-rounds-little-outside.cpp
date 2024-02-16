// # @EXPECTED_GRADES@ WA WA WA WA AC AC WA
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define com complex<double>
#define ld long double;
#define ii pair<ll,ll>
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vi>
#define vvll vector<vll>
#define vii vector<ii>
#define FOR(x,n) for(int x=0;x<(int)(n);x++)
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

ll dist(ii x, ii y) {
    return abs(x.F - y.F) + abs(x.S - y.S);
}

vll query(vii qs) {
    cout << "? "; 
    FORE(q,qs) {
        cout << q.F << " " << q.S << " ";
    }
    cout << endl;

    vll res(k*qs.size());
    FOR(i,(k*qs.size())) {
        cin >> res[i];
    }

    return res;
}

int main() {
    cin >> b >> k >> w;
    // Assumptions

    vll tt;
    vll a = query({{-b,-b},{-b,b}});

    set<ii> init;
    FORE(p,a) FORE(q,a) {
        if((p+q-2*b)%2) continue;
        ll x = (p + q - 2*b)/2-b;
        ll y = p - (b + x) - b;
        if(y < -b || y > b || x < -b || x > b) continue;
        init.insert({x,y});
    }

    vii pts(ALL(init));

    set<int> dd;
    vii qp(sz(pts));
    int cc = 0;
    FOR(i,sz(pts)) {
        while(dd.count(b+cc+pts[i].F)) cc++;
        qp[i] = {-b-cc,pts[i].S};
        FOR(j,sz(pts)) {
            dd.insert(dist(pts[j],qp[i]));
        }
    }

    vll ds = query(qp);

    map<ll,int> mp;
    FORE(d,ds) mp[d]++;

    vii sol;
    FOR(i,sz(pts)) {
        ii p = pts[i];
        if(mp[dist(pts[i],qp[i])]) {
            sol.pb(p);
            FOR(j,sz(pts)) {
                mp[dist(pts[i],qp[j])]--;
            }
        } 
    }
    cout << "! ";
    FORE(s,sol) cout << s.F << " " << s.S << " ";
    cout << endl;
}