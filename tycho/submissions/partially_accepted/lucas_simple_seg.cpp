// @EXPECTED_GRADES@ AC AC AC AC AC AC TLE
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 2e18;

int cap;
vector<ll> seg;
void build(int m){
    for(cap = 1; cap < m; cap *= 2);
    seg.assign(2*cap, inf);
}
void upd(int i, ll v){
    seg[i += cap] = v;
    for(i /= 2; i >= 1; i /= 2) seg[i] = min(seg[2*i], seg[2*i+1]);
}
ll qry(int l, int r, int a, int b, int i){
    if(l <= a && b <= r) return seg[i];
    if(b < l || r < a) return inf;
    int m = (a+b)/2;
    return min(qry(l, r, a, m, 2*i), qry(l, r, m+1, b, 2*i+1));
}
ll qry(int l, int r){return qry(l, r, 0, cap-1, 1);}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll b; int m, d, n;
    cin >> b >> m >> d >> n;
    vector<ll> a(++n);
    vector<ll> dp(n);
    for(int i = 1; i < n; i++) cin >> a[i];
    build(m);
    upd(0, 0);
    for(int i = 1; i < n; i++){
        int p = int(a[i]%m);
        ll x = a[i]/m*(d+m);
        dp[i] = x + min(qry(0, p-1)+d+m, qry(p, m-1)) - d;
        upd(p, dp[i] - x);
    }
    ll ans = inf;
    for(int i = 0; i < n; i++){
        ll dist = b-a[i];
        ll total = dp[i] + dist + d * ((dist+m-1)/m - 1);
        ans = min(ans, total);
    }
    cout << ans << "\n";
}