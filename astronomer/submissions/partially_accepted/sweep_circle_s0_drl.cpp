/*
 *  runs in O(n^3 lg n)
 *  
 *  # @EXPECTED_GRADES@ WA AC AC WA WA WA WA
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

double eps = 1e-12;

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
vector<Pd> circleLine(Pd c, double r, Pd a, Pd b) {
	Pd ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	Pd h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}


vector<Pd> ps;
ll k,n,t,s;

bool sweep(int u, double r) {
    vector<pair<double,int>> e; // Events (Angle,change) where change is whether a new point was added or removed.
    FOR(v,n) {
        if(v == u) continue;
        Pd md = (ps[u] + ps[v]) / 2; // Point on bisector
        Pd dir = (ps[v]-ps[u]).perp(); // Direction vector
        Pd f1,f2;
        vector<Pd> ip = circleLine(ps[u],r,md,md+dir);
        if(sz(ip) < 2) continue;
        else {
            f1 = ip[0];
            f2  = ip[1];
        }
        double langle = (f1-ps[u]).angle();
        double rangle = (f2-ps[u]).angle();

        if(rangle + (langle > rangle ?  2*M_PI : 0)-langle >= M_PI+eps) swap(rangle,langle);

        e.pb({langle,1});
        e.pb({rangle,-1});

        if(langle > rangle) { // Crosses starting point
            e.pb({-M_PI,1});
            e.pb({M_PI,-1});
        }
    }
    //cout << sz(e) << endl;
    sort(ALL(e));
    int cr = 1;
    if(cr >= k) return true;
    FORE(v,e) {
        cr += v.S;
        //cout << cr << endl;
        if(cr >= k) return true;
    }
    return false;
}

bool construct(double r) {
    FOR(i,n) if(sweep(i,r)) return true;
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

    double mic = 0, mac = 2e18;

    while(mic + abs(mic*eps) < mac && mic + eps < mac) {
        double md = (mic + mac) / 2;

        if (construct(md)) {
            mac = md;
        } else {
            mic = md;
        }
    }
    cout << mic*t << endl;
}
