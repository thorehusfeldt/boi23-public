/* @EXPECTED_GRADES@ AC WA AC AC WA
 *
 * O(n^2) solution with dumb randomization.
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

mt19937 rng(241421421452150291ull);

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
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    shuffle(ord.begin(), ord.end(), rng);
    auto begin = clock();
    int it = 0;
    ll ans = 2.01e18;
    for(int u : ord){
        if(it && g[u].size() > 1) continue;
        t = 0;
        cost = 0;
        dfs(u);
        ans = min<ll>(ans, cost);
        if((++it)%1 == 0){
            if((clock() - begin) * 1.0 / CLOCKS_PER_SEC >= 0.9) break;
        }
    }
    cout << ans << "\n";
}

