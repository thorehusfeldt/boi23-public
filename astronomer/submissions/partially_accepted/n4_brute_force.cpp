// @EXPECTED_GRADES@ AC AC TLE AC TLE TLE TLE TLE
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
#define vvld vector<vld>
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

double ccRadius(const Pd& A, const Pd& B, const Pd& C) {
	return (B-A).dist()*(C-B).dist()*(A-C).dist()/
			abs((B-A).cross(C-A))/2;
}

Pd ccCenter(const Pd& A, const Pd& B, const Pd& C) {
	Pd b = C-A, c = B-A;
    if(abs(b.cross(c)) <= 1e-8) return Pd(0,0);
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
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
    if (t <= s || k == 1) {
        vd d(n);
        FOR(i, n) d[i] = ps[i].dist();
        sort(ALL(d));
        cout << d[k - 1] * min(ot,os) << endl;
        return 0;
    }
    ld best = 1e22;
    ld eps = 1e-15;
    FOR(i,n) FOR(j,i) {
        if(i == j) continue;
        Pd mp = (ps[i]+ps[j])/2;
        Pd dir = (ps[j]-ps[i]).perp().unit();
        ld mi = -1e10, ma = 1e10;
        while(err(mi,ma) > eps) {
            ld md1 = (2*mi + ma)/3;
            ld md2 = (mi + 2*ma)/3;
            ld c1 = (mp + dir*md1).dist()*s + (mp + dir*md1 - ps[i]).dist()*t;
            ld c2 = (mp + dir*md2).dist()*s + (mp + dir*md2 - ps[i]).dist()*t;
            if(c1 <= c2) {
                ma = md2;
            } else {
                mi = md1;
            }
        }
        Pd c = mp + dir*(mi + ma)/2;
        ld r = (c-ps[i]).dist();
        int d = 0;
        FOR(l,n) if((ps[l]-c).dist() <= r*(1+1e-7)) d++;
        if(d >= k) {
            best = min(best,c.dist()*s + r*t);
        }
    }

    FOR(i,n) FOR(j,n) FOR(l,n) {
        Pd c = ccCenter(ps[i],ps[j],ps[l]);
        double r = ccRadius(ps[i],ps[j],ps[l]);
        int d = 0;
        FOR(m,n) if((ps[m]-c).dist() <= r*(1+1e-7)) d++;
        if(d >= k) {
            best = min(best,c.dist()*s + r*t);
        }
    }
    cout << best * ot << endl;
}
