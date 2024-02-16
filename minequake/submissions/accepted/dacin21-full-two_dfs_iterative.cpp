/*
 * O(n) solution with O(1) stack space
 *
 */ 
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;


int n;
vector<vector<int> > g;
vector<ll> up, ans;
vector<int> siz;


template<typename S, typename T>
void iterative_dfs(int root, S pre, T post){
    vector<pair<int, int> > s;
    s.reserve(n);
    s.push_back({root, -1});
    while(!s.empty()){
        auto [u, p] = s.back();
        s.pop_back();
        if(u >= 0){
            if(p != -1) pre(u, p);
            s.push_back({-1-u, p});
            for(int const e : g[u]) if(e != p){
                s.push_back({e, u});
            }
        } else {
            u = -1-u;
            if(p != -1) post(u, p);
        }
    }
}

auto pass = [](auto&&args...) {};

signed main(){
    int n;
    cin >> n;
    ans.assign(n, -1);
    up.assign(n, 0);
    siz.assign(n, 1);
    g.assign(n, {});
    for(int i=1; i<n; ++i){
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    iterative_dfs(0, pass, [&](int u, int p){
        up[p] += siz[u] * (ll)(2*siz[p] - 1);
        up[p] += up[u];
        siz[p] += siz[u];
    });
    ans[0] = up[0];
    iterative_dfs(0, [&](int u, int p){
        ans[u] = ans[p] - (n-siz[u]) + siz[u];
    }, pass);
    auto ret = *min_element(ans.begin(), ans.end());
    cout << ret << "\n";
}

