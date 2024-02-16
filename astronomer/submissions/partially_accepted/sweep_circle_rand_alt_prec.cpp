/* 
*  # @EXPECTED_GRADES@ AC AC AC AC AC AC AC
*/ 
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define com complex<ld>
#define ld long double
#define ii pair<ll,ll>
#define vi vector<int>
#define vii vector<ii>
#define vc vector<char>
#define vs vector<string>
#define vd vector<ld>
#define vcom vector<com>
#define vld vector<ld>
#define vll vector<ll>
#define vvi vector<vi>
#define vvii vector<vii>
#define vvc vector<vc>
#define vvs vector<vs>
#define vvll vector<vll>
#define vvd vector<vd>
#define vvcom vector<vcom>
#define vvld vector<vld>
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

#ifndef M_PI
#define M_PI (acosl(-1))
#endif

ld err(ld a, ld b)
{
	ld d = abs(b - a);
	ld m = max((ld)(1), max(abs(a),abs(b)));
	return d / m;
}



// kactl geometry
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    ld dist() const { return sqrt((ld)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    ld angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }
    P normal() const { return perp().unit(); }
    P rotate(ld a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
typedef Point<ld> Pd;
vector<Pd> ps;
ll k, n;
ld s,t;

bool sweep(int u, ld cst, ld eps) {
    if(s*ps[u].dist() > cst) return false;
    vector<pair<ld,int>> e; // Events (Angle,change) where change is whether a new point was added or removed.
    FOR(v,n) {
        if(v == u) continue;
        Pd md = (ps[u] + ps[v]) / 2; // Point on bisector
        Pd dir = (ps[v]-ps[u]).perp().unit(); // Direction vector

        // We can now ternary search on the magnitude of dir
        ld lmn = -1e9, lmx = 1e9;
        ld rmn = lmn, rmx = 1e9;
        ld mcost = 1e19;
        //REP(80){
        while(err(lmn,lmx) > eps || err((md + dir*lmn-ps[u]).dist()*t + (md+dir*lmn).dist()*s,(md + dir*lmx-ps[u]).dist()*t + (md+dir*lmx).dist()*s) > eps) {
            ld lmd1 = (2*lmn + lmx) / 3;
            ld lmd2 = (lmn + 2*lmx) / 3;

            ld cs1 = (md + dir*lmd1-ps[u]).dist()*t + (md+dir*lmd1).dist()*s;
            ld cs2 = (md + dir*lmd2-ps[u]).dist()*t + (md+dir*lmd2).dist()*s; 
            ld dcst = cs2-cs1;
            //cout <<   << " " << (md + dir*lmx-ps[u]).dist()*t + (md+dir*lmx).dist()*s << " " << cost(lmn) << " " << cost(lmx) << endl;
            mcost = min(mcost,cs1);
            mcost = min(mcost,cs2);
            if(cs1 <= cst || dcst > 0) {
                lmx = lmd2;
                if(cs2 > cst) rmx = lmd2;
            } else {
                lmn = lmd1;
            }
        }
        rmn = lmn;
        //REP(80){
        while(err(rmn,rmx) > eps || err((md + dir*rmn-ps[u]).dist()*t + (md+dir*rmn).dist()*s,(md + dir*rmx-ps[u]).dist()*t + (md+dir*rmx).dist()*s) > eps) {
            ld rmd1 = (2*rmn + rmx) / 3;
            ld rmd2 = (rmn + 2*rmx) / 3;

            ld cs1 = (md + dir*rmd1-ps[u]).dist()*t + (md+dir*rmd1).dist()*s;
            ld cs2 = (md + dir*rmd2-ps[u]).dist()*t + (md+dir*rmd2).dist()*s; 
            ld dcst = cs2-cs1;
            mcost = min(mcost,cs1);
            mcost = min(mcost,cs2);
            //cout << rmx << " " << rmn  << " " << dcst << endl;

            if(cs2 <= cst || dcst < 0) {
                rmn = rmd1;
            } else {
                rmx = rmd2;
            }
        }
        if(mcost > cst) continue;

        ld langle = (md + dir*(lmn+lmx)/2-ps[u]).angle();
        ld rangle = (md + dir*(rmn+rmx)/2-ps[u]).angle();

        e.pb({langle,1});
        e.pb({rangle,-1});

        if(langle > rangle) { // Crosses starting point
            e.pb({-M_PI,1});
            e.pb({M_PI,-1});
        }
    }
    sort(ALL(e));
    int cr = 1;
    if(cr >= k) return true;
    //cout << e.size() << endl;
    FORE(v,e) {
        cr += v.S;
        if(cr >= k) return true;
    }
    return false;
}

int main() {
    ll os, ot;
    cin >> k >> n >> os >> ot;
    
    s = os;
    t = ot;
    s /= t;
    t = 1;

    FOR(i, n) {
        int x, y;
        cin >> x >> y;
        ps.pb(Pd(x, y));
    }

    cout << setprecision(12) << fixed;
    if (t <= s) {
        vd d(n);
        FOR(i, n) d[i] = ps[i].dist();
        sort(ALL(d));
        cout << d[k - 1] * ot << endl;
        return 0;
    }
    ld best = 2e18;
    mt19937_64 rng(0);
    //shuffle(ps.begin(), ps.end(), rng);
    ld eps1 = 1e-8;
    ld eps2 = 1e-8;
    FOR(i, n){
        ld better = best * (1 - eps1);
		//ld better = best - eps2;
        if (!sweep(i, better, eps1)) continue;
        //if (!sweep(i, better,eps2)) continue;
        ld mic = 0, mac = better;
        while(err(mic,mac) > eps2) {
            ld md = (mic + mac) / 2;
            if (sweep(i, md, eps2)) {
                mac = md;
            } else {
                //cout << 0 << endl;
                mic = md;
            }
        }
        best = (mic + mac) / 2;
    }
    cout << best * ot << endl;
}
