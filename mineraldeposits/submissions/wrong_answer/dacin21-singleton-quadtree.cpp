/*
 * @EXPECTED_GRADES@ WA WA WA WA WA WA WA
 *   A solution that only queries a single point at a time.
 *   This solution does not use candidates. Instead, a quad-tree like descent
 *   is used to search the entire plane.
 *
 *   Note: This solution is really bad and uses O(k log nm) queries, with large constant.
 *   It also needs to query points outside the grid.
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
map<ll, int> query_reduced(vector<Point> const&v, set<Point> const&known){
    auto ret = query(v);
    for(auto const&p : known){
        for(auto const&q : v){
            --ret[dist(p, q)];
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
bool is_square_nonempty(Point const&center, ll radius, set<Point> const&known){
    return query({center}).begin()->first <= radius;
}
signed main(){
    cin >> X >> k >> Q;
    Y = X;
    set<Point> ans;
    auto rec = [&](auto &rec, Point center, ll r){
        if(!is_square_nonempty(center, r, ans)) return;
        if(r == 0){
            ans.insert(center);
            return;
        }
        const int R = r - r/2;
        r /= 2;
        rec(rec, Point{center.x + R, center.y}, r);
        rec(rec, Point{center.x - R, center.y}, r);
        rec(rec, Point{center.x, center.y + R}, r);
        rec(rec, Point{center.x, center.y - R}, r);
        if(r == 0){
            rec(rec, Point{center.x, center.y}, r);
        }
    };
    rec(rec, Point{0, 0}, 2ull << __lg(X + Y + 4));

    cout << "!";
    for(auto &e : ans){
        cout << " " << e.x << " " << e.y;
    }
    cout << endl;
}

