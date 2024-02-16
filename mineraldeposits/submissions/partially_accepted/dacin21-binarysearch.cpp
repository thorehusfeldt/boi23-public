//# @EXPECTED_GRADES@ AC AC AC WA WA WA WA
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
    int L = 0, R = ssize(pool);
    while(ssize(ans) < k){
        assert(L < R);
        int l = L, r = R;
        while(l+1 < r){
            const int m = l + (r-l)/2;
            if(count_in_range(l, m)) r = m;
            else l=m;
        }
        ans.push_back(l);
        L = r;
    }

    cout << "!";
    for(auto &i : ans){
        auto const e = pool[i];
        cout << " " << e.x << " " << e.y;
    }
    cout << endl;
}

