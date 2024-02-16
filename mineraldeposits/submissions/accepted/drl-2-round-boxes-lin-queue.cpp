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
#define vvii vector<vii>
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

struct Event {
    int u, v, d;
    int tp; 
    Event(int _u, int _v, int _d, int _tp) : u(_u), v(_v), d(_d), tp(_tp) {}
    bool operator<(const Event other) const {
        return tp > other.tp;
    }
    // 1 add dependency
    // 2 set inactive
    // 3 set active
};

vi vis;
vvi iac;
vvii adep;
int acc = 0;
int cc = -1;
void handle_event(Event e) {
    if(e.tp == 1) {
        if(!vis[e.v]) {
            adep[e.v].pb({e.u,e.d});
            if(iac[e.u][e.d] == 0) acc--;
            iac[e.u][e.d]++;
        }
    } else if (e.tp == 2) {
        if(iac[e.u][e.d] == 0) acc--;
        iac[e.u][e.d]++;
    } else if (e.tp == 3) {
        --iac[e.u][e.d];
        if(iac[e.u][e.d] == 0) acc++;
    } else {
        assert(false);
    }
}

vector<vector<Event>> eq;

void push_event(int t, Event e) {
    if(t <= cc) return handle_event(e);
    if(t >= sz(eq)) return; // Won't ever be relevant
    eq[t].pb(e);
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
    vi dd(2*cp*cp);
    adep = vvii(cp);
    vvi dc(cp,vi(4));
    eq.resize(2*cp*cp);
    acc = 4*cp;
    FOR(i,cp) FOR(j,cp) {
        if(i == j) continue;
        if(dist(pts[i],pts[j]) > cp*cp*2) continue;
        int dx = abs(pts[j].F - pts[i].F), dy = abs(pts[j].S - pts[i].S);
        if(dx <= dy) {
            if(pts[j].S > pts[i].S) {
                push_event(dy/2,Event(i,j,0,1));
            } else if (pts[j].S < pts[i].S) {
                push_event(dy/2,Event(i,j,1,1));
            }
        }
        if(dx >= dy) {
            if(pts[j].F > pts[i].F) {
                push_event(dx/2,Event(i,j,2,1));
            } else if (pts[j].F < pts[i].F) {
                push_event(dx/2,Event(i,j,3,1));
            }
        }
    }

    FOR(i,cp) {
        vll r = {lm-pts[i].S, pts[i].S+lm, lm-pts[i].F, pts[i].F+lm};
        FOR(j,4) push_event(r[j],Event(i,-10,j,2));
    }
    iac = vvi(cp, vi(4));
    vis = vi(cp);

    vii qps(cp);

    vii dir = {{0,1},{0,-1},{1,0},{-1,0}};
    vi odr;
    int ss = 0;
    //int cnter = 0;
    while(ss < cp) {
        cc++;
        FORE(e,eq[cc]) handle_event(e);
        if(acc == 0) continue;
        if(dd[cc]) continue;
        int u = -1, d = -1;
        FOR(i,cp) FOR(j,4) if(iac[i][j] == 0) {
            u = i;
            d = j;
            break;
        }
        assert(u != -1);
        vis[u] = true;
        qps[u] = {pts[u].F + dir[d].F*cc, pts[u].S + dir[d].S*cc};
        odr.pb(u);
        //cout << " found: " << u << endl; 
        FOR(j,4) {
            if(iac[u][j] == 0) {
                acc--;
            }
            iac[u][j]++;
        } 
        FORE(vp,adep[u]) {
            if(vis[vp.F]) continue;
            --iac[vp.F][vp.S];
            if(iac[vp.F][vp.S] == 0) acc++;
        }
        ss++;
        FOR(i,cp) {
            int r = dist(qps[u],pts[i]);
            if(r < sz(dd)) dd[r] = 1;
            if(i == u || vis[i]) continue;
            if(abs(pts[u].F-pts[i].F) <= cc+1) 
            {
                if(pts[u].S-pts[i].S > 0) {
                    push_event(pts[u].S-pts[i].S-cc,Event(i,-1,0,2));
                    push_event(pts[u].S-pts[i].S+cc,Event(i,-1,0,3));
                } else {
                    push_event(pts[i].S-pts[u].S-cc,Event(i,-1,1,2));
                    push_event(pts[i].S-pts[u].S+cc,Event(i,-1,1,3));
                }
            }
            if(abs(pts[u].S-pts[i].S) <= cc+1) {
                if(pts[u].F-pts[i].F > 0) {
                    push_event(pts[u].F-pts[i].F-cc,Event(i,-1,2,2));
                    push_event(pts[u].F-pts[i].F+cc,Event(i,-1,2,3));
                } else {
                    push_event(pts[i].F-pts[u].F-cc,Event(i,-1,3,2));
                    push_event(pts[i].F-pts[u].F+cc,Event(i,-1,3,3));
                }
            }
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
}