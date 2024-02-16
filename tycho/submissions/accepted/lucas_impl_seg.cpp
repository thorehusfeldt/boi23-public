#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 2e18;

const ll MAX = (1ll<<40)-1;

vector<ll> seg, lazy;
vector<int> L, R;
void push(int i){
    if(L[i] != -1){
        seg[L[i]] += lazy[i];
        lazy[L[i]] += lazy[i];
    }
    if(R[i] != -1){
        seg[R[i]] += lazy[i];
        lazy[R[i]] += lazy[i];
    }
    lazy[i] = 0;
}
void upd(ll p, ll v, ll a=0, ll b=MAX, int i=0){
    if(a == b) seg[i] = v;
    else{
        push(i);
        ll m = (a+b)/2;
        if(p <= m){
            if(L[i] == -1){
                L[i] = (int)seg.size();
                seg.push_back(inf);
                lazy.push_back(0);
                L.push_back(-1);
                R.push_back(-1);
            }
            upd(p, v, a, m, L[i]);
        }
        else{
            if(R[i] == -1){
                R[i] = (int)seg.size();
                seg.push_back(inf);
                lazy.push_back(0);
                L.push_back(-1);
                R.push_back(-1);
            }
            upd(p, v, m+1, b, R[i]);

        }
        seg[i] = inf;
        if(L[i] != -1) seg[i] = min(seg[i], seg[L[i]]);
        if(R[i] != -1) seg[i] = min(seg[i], seg[R[i]]);
    }
}
void add(ll l, ll r, ll v, ll a=0, ll b=MAX, int i=0){
    if(l <= a && b <= r){
        seg[i] += v;
        lazy[i] += v;
    }
    else if(b < l || r < a) return;
    else{
        push(i);
        ll m = (a+b)/2;
        if(L[i] != -1) add(l, r, v, a, m, L[i]);
        if(R[i] != -1) add(l, r, v, m+1, b, R[i]);
        seg[i] = inf;
        if(L[i] != -1) seg[i] = min(seg[i], seg[L[i]]);
        if(R[i] != -1) seg[i] = min(seg[i], seg[R[i]]);
    }
}
void circ_add(ll l, ll r, ll v){
    if(l <= r) add(l, r, v);
    else add(l, MAX, v), add(0, r, v);
}
ll qry(ll p, ll a=0, ll b=MAX, int i=0){
    if(a == b) return seg[i];
    else{
        push(i);
        ll m = (a+b)/2;
        if(p <= m) return qry(p, a, m, L[i]);
        else return qry(p, m+1, b, R[i]);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll z, m, c;
    int n;
    cin >> z >> m >> c >> n;
    n++; // add imaginary hiding spot at 0 to make implementation easier
    vector<ll> a(n);
    for(int i = 1; i < n; i++) cin >> a[i];

    seg = {inf};
    L = {-1};
    R = {-1};
    lazy = {0};
    upd(0, -c-m);
    ll to_add = 0;
    ll last = 0;
    for(int i = 1; i < n; i++){
        ll d = a[i]-last;
        to_add += (c+m)*((d-1)/m);
        ll l = last%m, r = (a[i]-1)%m;
        circ_add(l, r, c+m);
        ll dp = seg[0]+m;
        upd(a[i]%m, dp-c-m);
        last = a[i];
    }
    ll d = z-last;
    to_add += (c+m)*((d-1)/m);
    ll l = last%m, r = (z-1)%m;
    circ_add(l, r, c+m);
    ll ans = inf;
    for(int i = 0; i < n; i++){
        ll x = qry(a[i]%m);
        x += (z-a[i])%m;
        if((z-a[i])%m == 0) x += m;
        ans = min(ans, x);
    }
    ans += to_add;
    cout << ans << "\n";
}