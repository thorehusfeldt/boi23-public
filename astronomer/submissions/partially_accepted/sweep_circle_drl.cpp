/*
 *  runs in O(n^3 lg n)
 *  
 *  # @EXPECTED_GRADES@ AC AC TLE AC AC TLE TLE
 */ 
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define com complex<double>
#define ld long double;
#define ii pair<ll,ll>
#define vi vector<int>
#define vii vector<ii>
#define vc vector<char>
#define vs vector<string>
#define vd vector<double>
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

double eps = 1e-10;
double eps1 = 1e-5;

// kactl geometry
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } 
	P normal() const { return perp().unit(); }
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
typedef Point<double> Pd;
vector<Pd> ps;
ll k,n,t,s;

bool sweep(int u, double cst) {
    if(s*ps[u].dist() > cst) return false;
    //cout << "Testing " << u << " " << cst << endl;
    vector<pair<double,int>> e; // Events (Angle,change) where change is whether a new point was added or removed.
    FOR(v,n) {
        if(v == u) continue;
        Pd md = (ps[u] + ps[v]) / 2; // Point on bisector
        Pd dir = (ps[v]-ps[u]).perp().unit(); // Direction vector

        // We can now ternary search on the magnitude of dir
        double lmn = -1e9, lmx = 1e9;
        double rmn = lmn, rmx = 1e9;
        double mcost = 1e19;
        double d = 1;
        int x = 0;
        while(d > eps1 || x < 40) {
        //while (lmn + abs(lmn*eps1) < lmx && lmn + eps1 < lmx) {
            double lmd1 = (2*lmn + lmx) / 3;
            double lmd2 = (lmn + 2*lmx) / 3;

            double cs1 = (md + dir*lmd1-ps[u]).dist()*t + (md+dir*lmd1).dist()*s;
            double cs2 = (md + dir*lmd2-ps[u]).dist()*t + (md+dir*lmd2).dist()*s; 
            double dcst = cs2-cs1;
            mcost = min(mcost,cs1);
            if(cs1 <= cst || dcst > 0) {
                d = fabs(lmx-lmd2);
                lmx = lmd2;
                if(cs2 > cst) rmx = lmd2;
            } else {
                d = fabs(lmn-lmd1);
                lmn = lmd1;
            }
            x++;
        }
        rmn = lmn;
        d = 1;
        x = 0;
        while(d > eps1 || x < 40) {
        //while(rmn + abs(rmn*eps1) < rmx && rmn + eps1 < rmx) {
            double rmd1 = (2*rmn + rmx) / 3;
            double rmd2 = (rmn + 2*rmx) / 3;

            double cs1 = (md + dir*rmd1-ps[u]).dist()*t + (md+dir*rmd1).dist()*s;
            double cs2 = (md + dir*rmd2-ps[u]).dist()*t + (md+dir*rmd2).dist()*s; 
            double dcst = cs2-cs1;
            mcost = min(mcost,cs1);
            //cout << rmx << " " << rmn  << " " << dcst << endl;

            if(cs2 <= cst || dcst < 0) {
                d = fabs(rmn-rmd1);
                rmn = rmd1;
            } else {
                d = fabs(rmx-rmd2);
                rmx = rmd2;
            }
            x++;
        }
        if(mcost > cst) continue;
        //assert(abs(rmx-rmn) < epsilon);

        double langle = (md + dir*lmn-ps[u]).angle();
        double rangle = (md + dir*rmn-ps[u]).angle();

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

bool construct(double cst) {
    FOR(i,n) if(sweep(i,cst)) return true;
    return false;
}

int main() {
    cin >> k >> n >> s >> t ;
    FOR(i,n) {
        int x,y;
        cin >> x >> y;
        ps.pb(Pd(x,y));
    }

    cout << setprecision(8) << fixed;
    if(t <= s) {
        vd d(n);
        FOR(i,n) d[i] = ps[i].dist();
        sort(ALL(d));
        cout << d[k-1] * t << endl;
        return 0;
    }

    double mic = 0, mac = 2e18;

    while(mic + abs(mic*eps) < mac && mic + eps < mac) {
        double md = (mic + mac) / 2;

        if (construct(md)) {
            mac = md;
        } else {
            mic = md;
        }
    }
    cout << mic << endl;
}
