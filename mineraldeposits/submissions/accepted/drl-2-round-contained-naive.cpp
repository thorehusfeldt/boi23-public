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
int b, k, w;
int lm = 1e8;

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

set<int> dd;
vii qps;
vi ccl;
vii cpq;
int cc = 0;
vii pts;
int cp;

bool try_cc(int idx, int dx, int dy){
    ii qp = {pts[idx].F + dx,pts[idx].S + dy};
    if(qp.F < -lm || qp.F > lm || qp.S < -lm || qp.S > lm) return false;
    FOR(j,cp) {
        ll dj = dist(qp,pts[j]);
        if(j == idx) continue;
        if(ccl[j] < 0 && dj <= abs(dx) + abs(dy)) return false;
        if(dj <= ccl[j]) return false;
    }
    //cout << "sb" << endl;
    FOR(j,cp) {
        dd.insert(dist(qp,pts[j]));
    }
    qps.pb(qp);
    cpq[idx] = qp;
    return true;
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
        //cout << " " << x << " " << y << endl;
        if(y < -b || y > b || x < -b || x > b) continue;
        init.insert({x,y});
    }

    pts = vii(ALL(init));

    cp = pts.size();
    cpq.resize(cp);
    ccl.resize(cp,-1);
    int idx = 0;
    int fd = 0;
    int cc = 0;

    vi nxt(cp);
    iota(ALL(nxt),1);
    nxt[cp-1] = 0;
    int pr = cp-1;
    int hic = 1;
    while(fd < cp) {
        if(idx <= pr){
            if(!hic) cc++;
            hic = 0;
        } 
        
        //cout << cc << " " << idx << " " << pr << endl;
        if(try_cc(idx,cc,0) || try_cc(idx,-cc,0) || try_cc(idx,0,cc) || try_cc(idx,0,-cc)) {
            ccl[idx] = cc;
            fd++;
            nxt[pr] = nxt[idx];
        } else {
            pr = idx;
        }
        while(dd.count(cc)) {
            cc++;
            hic = 1;
        }

        idx = nxt[idx];
    }

    vll ds = query(qps);

    map<ll,int> cnt;
    FORE(d,ds) cnt[d]++;

    vii pem(cp);
    FOR(i,cp) {
        pem[i] = {ccl[i],i};
    }
    sort(ALL(pem));

    vii sol;

    FOR(pmi,cp) {
        int pi = pem[pmi].S;
        ii p = pts[pi];
        if(cnt[ccl[pi]]) {
            sol.pb(p);
            FORE(q,qps) cnt[dist(p,q)]--;
        }
    }
    cout << "! ";
    FORE(s,sol) cout << s.F << " " << s.S << " ";
    cout << endl;
}
