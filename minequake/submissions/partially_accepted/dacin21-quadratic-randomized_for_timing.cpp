/* @EXPECTED_GRADES@ AC TLE AC AC TLE
 *
 * O(n^2) solution, with clever randomization.
 * This version uses a copy of the O(n) solution to give TLE instead of WA.
 *
 * This allows us to gauge how close the actual randomized solution
 * is to getting AC instead of WA.
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

namespace fast{

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

ll main(int n){
    ans.assign(n, -1);
    up.assign(n, 0);
    siz.assign(n, 1);
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
    return ret;
}
} // namespace fast


mt19937 rng(241421421452150291ull);

signed main(){
    int n;
    cin >> n;
    g.assign(n, {});
    vector<char> vis(n, 0);
    for(int i=1; i<n; ++i){
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    const ll solution = fast::main(n);
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    shuffle(ord.begin(), ord.end(), rng);
    int it = 0;
    ll ans = 2.01e18;
    for(int u : ord){
        if(it++){
            if(g[u].size() > 1) continue;
            if(vis[g[u][0]]) continue;
            vis[g[u][0]] = 1;
        }
        t = 0;
        cost = 0;
        dfs(u);
        ans = min<ll>(ans, cost);
        if(ans == solution) break;
    }
    if(ans != solution) return 0;
    cout << ans << "\n";
}

