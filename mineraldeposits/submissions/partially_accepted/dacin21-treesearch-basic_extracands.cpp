/*
 *   Very basic solution based on finding k^2 candidates + recursive yes/no tree search
 *
 *   This implementation doesn't check for parity when finding candidates.
 *   On good test data, this should not effect the number of points we score.
 * # @EXPECTED_GRADES@ AC AC AC WA WA WA WA
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
int query_zeros(vector<Point> const&v){
    auto tmp = query(v);
    return count(tmp.begin(), tmp.end(), 0);
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
            // if(!(u%2 == 0 && v%2 == 0)) continue;
            u/=2, v/=2;
            if(u < -X || u > X) continue;
            if(v < -Y || v > Y) continue;
            pool.push_back(Point{u, v});
        }
    }
    sort(pool.begin(), pool.end());
    pool.erase(unique(pool.begin(), pool.end()), pool.end());

    auto count_in_range = [&](int l, int r){
        return query_zeros(vector<Point>(pool.begin()+l, pool.begin()+r));
    };
    vector<int> ans;
    auto rec = [&](auto& rec, int l, int r){
        const int cnt = count_in_range(l, r);
        if(!cnt) return;
        if(r-l == 1){
            ans.push_back(l);
            return;
        }
        const int m = l + (r-l)/2;
        rec(rec, l, m);
        rec(rec, m, r);
    };
    rec(rec, 0, ssize(pool));

    cout << "!";
    for(auto &i : ans){
        auto const e = pool[i];
        cout << " " << e.x << " " << e.y;
    }
    cout << endl;
}

