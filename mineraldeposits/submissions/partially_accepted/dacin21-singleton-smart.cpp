/*
 *   A solution that only queries a single point at a time.
 *   Starts by querying two points to get a (k x k) grid of candidates.
 *   Then processes the candidates row by row via binary search by querying points
 *   that are far enough away.
 *
 *   Note: Queries points outside the grid, except for k=1
 *
 *   # @EXPECTED_GRADES@ AC WA WA WA WA WA WA
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
ll dist(Point const&p, Point const&q){
    return abs(p.x-q.x) + abs(p.y-q.y);
}

ll X, Y;
int k, Q;
map<ll, int> query(vector<Point> const&v){
    cout << "? " << " ";
    for(auto const&p : v){
        cout << p.x << " " << p.y << " ";
    }
    cout << endl;
    map<ll, int> ret;
    for(int it=0; it < ssize(v) * k; ++it){
        ll e;
        cin >> e;
        ++ret[e];
    }
    return ret;
}
map<ll, int> subtract_known(map<ll, int> ret, vector<Point> const&query, vector<Point> const&known){
    for(Point const &p : query){
        for(Point const &q : known){
            ll d = dist(p, q);
            assert(ret[d] > 0);
            --ret[d];
        }
    }
    for(auto it = ret.begin(); it != ret.end();){
        if(!it->second){
            it = ret.erase(it);
        } else {
            ++it;
        }
    }
    return ret;
}

const ll STEP = 2.01e8;

signed main(){
    cin >> X >> k >> Q;
    Y = X;
    vector<Point> q_A = {Point{-X, -Y}}, q_B = {Point{X, -Y}};
    auto A_orig = query(q_A);
    auto B_orig = query(q_B);
    vector<Point> ans;
    while(ssize(ans) < k){
        auto A = subtract_known(A_orig, q_A, ans);
        auto B = subtract_known(B_orig, q_B, ans);
        const ll a = A.begin()->first;
        vector<Point> pool;
        for(auto [b, _] : B){
            ll u  = (a-b), v = (a+b-2*X-2*Y);
            if(!(u%2 == 0 && v%2 == 0)) continue;
            u/=2, v/=2;
            if(u < -X || u > X) continue;
            if(v < -Y || v > Y) continue;
            pool.push_back(Point{u, v});
        }
        int l = 0, r = ssize(pool);
        while(l+1 < r){
            const int m = l + (r-l)/2;
            vector<Point> q  = {Point{pool[m-1].x, pool[m-1].y - STEP}};
            auto res = subtract_known(query(q), q, ans);
            if(res[STEP]){
                r = m;
            } else {
                l = m;
            }
        }
        ans.push_back(pool[l]);
    } 

    cout << "!";
    for(auto &e : ans){
        cout << " " << e.x << " " << e.y;
    }
    cout << endl;
}

