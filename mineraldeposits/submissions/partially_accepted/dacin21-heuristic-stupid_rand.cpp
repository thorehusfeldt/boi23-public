/*
 *  An even more stupid heuristic solution:
 *   - get k^2 candidate points.
 *   - repetedly select an *arbitrary* candidate, query it,
 *     and remove all candidates that are too close to this candidate.
 *
 *  # @EXPECTED_GRADES@ AC AC AC AC WA WA WA
 */

#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

template<typename T>
int64_t ssize(T const&v){ return (int64_t) v.size(); }

struct Point{
    ll x, y;
    friend bool operator<(Point const&a, Point const&b){
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    }
    friend bool operator==(Point const&a, Point const&b){
        return !((a < b) || (b < a));
    }
};
ll dist(Point const&a, Point const&b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

ll X, Y;
int k, Q;
vector<ll> query(vector<Point> const&v){
    for(auto const&p : v){
        assert(-X <= p.x && p.x <= X);
        assert(-X <= p.y && p.y <= Y);
    }
    cout << "? " << " ";
    for(auto const&p : v){
        cout << p.x << " " << p.y << " ";
    }
    cout << endl;
    vector<ll> ret(ssize(v) * k);
    for(auto &e : ret){
        cin >> e;
    }
    return ret;
}
ll query_min(Point const& p){
    auto tmp = query({p});
    return *min_element(tmp.begin(), tmp.end());
}

signed main(){
    cin >> X >> k >> Q;
    Y = X;
    auto A = query({Point{-X, -Y}});
    auto B = query({Point{X, -Y}});
    vector<Point> pool;
    for(int a : A){
        for(int b : B){
            ll u  = (a-b), v = (a+b-2*X-2*Y);
            if(!(u%2 == 0 && v%2 == 0)) continue;
            u/=2, v/=2;
            if(u < -X || u > X) continue;
            if(v < -Y || v > Y) continue;
            pool.push_back(Point{u, v});
        }
    }
    sort(pool.begin(), pool.end());
    pool.erase(unique(pool.begin(), pool.end()), pool.end());
    mt19937 rng(5315189052189ll);
    shuffle(pool.begin(), pool.end(), rng);

    vector<Point> ans;
    while(ssize(ans) < k){
        const Point p = pool.back();
        pool.pop_back();
        const ll D = query_min(p);
        if(D == 0){
            ans.push_back(p);
        }
        pool.erase(remove_if(pool.begin(), pool.end(), [&](Point const&q){
            return dist(p, q) < D;
        }), pool.end());
    }


    cout << "!";
    for(auto &e : ans){
        cout << " " << e.x << " " << e.y;
    }
    cout << endl;
}

