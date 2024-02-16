/* @EXPECTED_GRADES@ TLE TLE AC AC TLE
 * 
 * O(n^2) solution, no heuristics
 *
 */ 
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;


int n;
vector<vector<int> > g;

int t;
ll cost;

void dfs(int u, int p = -1){
    cost += t++;
    for(auto &e : g[u]) if(e != p){
        dfs(e, u);
    }
    ++t;
}


signed main(){
    int n;
    cin >> n;
    g.assign(n, {});
    for(int i=1; i<n; ++i){
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    ll ans = 2.01e18;
    for(int u=0; u<n; ++u){
        t = 0;
        cost = 0;
        dfs(u);
        ans = min<ll>(ans, cost);
    }
    cout << ans << "\n";
}

