#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr ll inf = 1e18;
#define sz(x) (int)size(x)

// Seems to solve the problem for n <= 100. But I have no idea how to analyze the complexity...

// @EXPECTED_GRADES@ AC TLE TLE TLE TLE TLE

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<ll> w(n+1);
    for(int i = 1; i <= n; i++) cin >> w[i];
    map<vector<int>, int> mp;
    vector<vector<int>> uncomp;
    vector<ll> dist;
    auto comp = [&](const vector<int>& v){
        if(!mp.count(v)){
            mp.emplace(v, sz(mp));
            uncomp.push_back(v);
            dist.push_back(inf);
        }
        return mp[v];
    };

    priority_queue<pair<ll, int>> pq;
    pq.emplace(-w[1], comp({1}));
    dist[0] = w[1];
    int todo = n;
    vector<ll> ans(n+1, -1);
    while(todo){
        auto [d, id] = pq.top();
        pq.pop();
        d = -d;
        vector<int> v = uncomp[id];
        if(ans[v.back()] == -1){
            ans[v.back()] = d;
            todo--;
        }
        if(v.back() == n) continue;
        set<int> nxt;
        nxt.insert(v.back()+1);
        for(int i = 0; i < sz(v); i++){
            for(int j = i; j < sz(v); j++){
                int x = v[i]*v[j];
                if(x <= n && x > v.back()) nxt.insert(x);
            }
        }
        for(int x : nxt){
            ll d2 = d + w[x];
            int old_size = sz(mp);
            v.push_back(x);
            int id2 = comp(v);
            v.pop_back();
            if(id2 == old_size){ // new id
                pq.emplace(-d2, id2);
            }
        }
    }
    for(int i = 1; i <= n; i++) cout << ans[i] << "\n";
}
