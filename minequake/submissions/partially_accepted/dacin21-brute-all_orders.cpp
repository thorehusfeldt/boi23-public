/*
 *  brute force solution that enumerates all possible order. 
 *  runs in O(n! * poly(n))
 *  
 *  # @EXPECTED_GRADES@ TLE TLE AC TLE TLE
 */ 


#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;


int n;
vector<vector<int> > g;
vector<char> vis;
vector<int> pp;
ll out = 2.01e18;

void dfs(int u, int t, ll cost){
    if(u == -1){
        out = min(out, cost);
        return;
    }
    const int p = pp[u];
    bool did_vis = false;
    if(!vis[u]){
        cost += t;
        did_vis = true;
        vis[u] = 1;
    }
    ++t;
    bool any = false;
    for(auto const&e : g[u]) if(e != p) {
        if(!vis[e]) {
            pp[e] = u;
            dfs(e, t, cost);
            any = true;
        }
    }
    if(!any) dfs(p, t, cost);
    if(did_vis) vis[u] = false;
}


signed main(){
    int n;
    cin >> n;
    g.assign(n, {});
    pp.assign(n, -1);
    vis.assign(n, 0);
    for(int i=1; i<n; ++i){
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    ll ans = 2.01e18;
    for(int u=0; u<n; ++u){
        dfs(u, 0, 0);
    }
    cout << out << "\n";
}

