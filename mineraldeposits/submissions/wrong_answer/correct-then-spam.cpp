// @EXPECTED_GRADES@ WA WA WA WA WA WA WA
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
#define vvvi vector<vvi>
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


int main() {
    cin >> b >> k >> w;

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
    int cp = pts.size();

    int s = 2*cp*cp;

    vvvi dep(cp,vvi(4));
    vvi dc(cp,vi(4));
    FOR(i,cp) FOR(j,cp) {
        if(dist(pts[i],pts[j]) > s) continue;
        if(abs(pts[j].F - pts[i].F) <= abs(pts[j].S - pts[i].S)) {
            if(pts[j].S > pts[i].S) {
                dc[i][0]++;
                dep[j][0].pb(i);
            } else if (pts[j].S < pts[i].S) {
                dc[i][1]++;
                dep[j][1].pb(i);
            }
        }
        if(abs(pts[j].F - pts[i].F) >= abs(pts[j].S - pts[i].S)) {
            if(pts[j].F > pts[i].F) {
                dc[i][2]++;
                dep[j][2].pb(i);
            } else if (pts[j].F < pts[i].F) {
                dc[i][3]++;
                dep[j][3].pb(i);
            }
        }
    }

    vector<queue<int>> qs(4);
    FOR(i,cp) FOR(j,4) if(!dc[i][j]) qs[j].push(i);

    vi vis(cp);
    int pc = 0;

    vii qps(cp);
    unordered_set<int> res;
    unordered_set<int> dd;

    vii dir = {{0,1},{0,-1},{1,0},{-1,0}};
    vi odr;
    int cc = 0;
    while(pc < cp) {
        FOR(dr,4) {
            if(qs[dr].size() == 0) continue;
            int idx = qs[dr].front();
            qs[dr].pop();
            if(vis[idx] == 1) {
                FORE(v,dep[idx][dr]) {
                    if(!(--dc[v][dr])) {
                        qs[dr].push(v);
                    }
                }
                continue;
            }
            ii qp;
            int f = 1;
            for(;;cc++) {
                qp = {pts[idx].F + dir[dr].F*cc, pts[idx].S + dir[dr].S*cc};
                if(qp.F < -lm || qp.F > lm || qp.S < -lm || qp.S > lm) {
                    goto total_fail;
                };
                if(dd.count(dist(qp,pts[idx]))) continue;
                FOR(i,cp){
                    if(res.count(dist(qp,pts[i]))) goto cc_fail;
                }
                break;
                cc_fail:
                cc = cc;
            }
            vis[idx] = 1;
            qps[idx] = qp;
            res.insert(dist(qp,pts[idx]));
            FOR(i,cp){
                dd.insert(dist(qp,pts[i]));
            }
            FORE(v,dep[idx][dr]) {
                if(!(--dc[v][dr])) {
                    qs[dr].push(v);
                }
            }
            odr.pb(idx);
            pc++;
            cc++;
            total_fail:
            cc = cc;
        }
    }
    vll ds = query(qps);

    map<ll,int> cnt;
    FORE(d,ds) cnt[d]++;
    vii sol;

    FOR(pmi,cp) {
        int pi = odr[pmi];
        ii p = pts[pi];
        if(cnt[dist(qps[pi],pts[pi])]) {
            sol.pb(p);
            FORE(q,qps) {
                cnt[dist(p,q)]--;
            }
        }
    }
    cout << "! ";
    FORE(s,sol) cout << s.F << " " << s.S << " ";
    cout << endl;
    cout << "spam" << endl;
}