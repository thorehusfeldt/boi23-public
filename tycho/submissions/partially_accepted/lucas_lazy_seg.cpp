// @EXPECTED_GRADES@ AC AC AC AC AC AC TLE
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 2e18;

int cap;
vector<ll> seg, lazy;

void build(int m){
    for(cap = 1; cap < m; cap *= 2);
    seg.assign(2*cap, inf);
    lazy.assign(2*cap, 0);
}
void apply(ll v, int i){
    seg[i] += v;
    lazy[i] += v;
}
void push(int i){
    apply(lazy[i], 2*i);
    apply(lazy[i], 2*i+1);
    lazy[i] = 0;
}
void upd(int p, ll v, int a, int b, int i){
    if(a == b) seg[i] = v;
    else{
        push(i);
        int m = (a+b)/2;
        if(p <= m) upd(p, v, a, m, 2*i);
        else upd(p, v, m+1, b, 2*i+1);
        seg[i] = min(seg[2*i], seg[2*i+1]);
    }
}
void upd(int p, ll v){upd(p, v, 0, cap-1, 1);}

void add(int l, int r, ll v, int a, int b, int i){
    if(l <= a && b <= r) apply(v, i);
    else if(l <= b && a <= r){
        push(i);
        int m = (a+b)/2;
        add(l, r, v, a, m, 2*i);
        add(l, r, v, m+1, b, 2*i+1);
        seg[i] = min(seg[2*i], seg[2*i+1]);
    }
}
void add(int l, int r, ll v){add(l, r, v, 0, cap-1, 1);}
void circ_add(int l, int r, ll v){
    if(l <= r) add(l, r, v);
    else add(l, cap-1, v), add(0, r, v);
}

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
        add(0, cap-1, (a[i]-a[i-1])/m*(d+m));
        if(a[i-1]%m != a[i]%m){
            int l = (int)(a[i-1] % m);
            int r = (int)((a[i]-1+m)%m);
            circ_add(l, r, d+m);
        }
        dp[i] = seg[1]-d;
        upd(int(a[i]%m), dp[i]);
    }
    ll ans = inf;
    for(int i = 0; i < n; i++){
        ll dist = b-a[i];
        ll total = dp[i] + dist + d * ((dist+m-1)/m - 1);
        ans = min(ans, total);
    }
    cout << ans << "\n";
}