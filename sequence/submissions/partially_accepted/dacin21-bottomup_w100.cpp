// @EXPECTED_GRADES@ WA AC AC TLE WA WA

// assumes all weights are similar, i.e. 100...108,
// so that the optimal sequence is always a shortests one.
//
// Formally, we need (Xmax - Xmin) * (ans-2) <= Xmin.
// We get * (ans-2) because every sequence starts with 1 2 ...

#include <bits/stdc++.h>
using namespace std;

const int inf = 1.01e9;
int n;

struct Push_Guard{
    Push_Guard(vector<int> &v_, int x) : v(v_){
        v.push_back(x);
    }
    ~Push_Guard(){
        v.pop_back();
    }

    vector<int> &v;
};

vector<int> ans, w;
vector<char> hit;

void cand(vector<int> const&v){
    int cost = 0;
    for(auto &e : v) cost += w[e];
    const int k = v.back();
    ans[k] = min(ans[k], cost);
}

uint64_t steps = 0;

void brute(vector<int> &v, int d){
    ++steps;
    const int k = v.back();
    if(!hit[k]) cand(v);
    if(d == 0) return;
    // try k -> k+1
    if(k < n) {
        Push_Guard p{v, k+1};
        brute(v, d-1);
    }
    // try products
    for(int i = 0; i < (int)v.size(); ++i){
        for(int j = i; j < (int)v.size(); ++j){
            const int x = v[i]*v[j];
            if(x > k && x <= n){
                Push_Guard p{v, x};
                brute(v, d-1);
            }
        }
    }
}

signed main(){
    cin >> n;
    w.resize(n);
    for(auto &e : w) cin >> e;
    w.insert(w.begin(), -1);
    ans.assign(n+1, inf);
    hit.assign(n+1, 0);
    ans[0] = 0;
    hit[0] = 1;

    auto done = [&](){ return !count(ans.begin(), ans.end(), inf); };
    for(int d=1; !done(); ++d){
        vector<int> v{1};
        brute(v, d-1);
        for(int i=1; i<=n; ++i){
            if(!hit[i] && ans[i] != inf) hit[i] = 1;
        }
    }

    for(int i=1; i<=n; ++i){
        cout << ans[i] << "\n";
    }
}
