// @EXPECTED_GRADES@ TLE AC AC AC TLE TLE TLE

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 2e18;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll z, m, c;
    int n;
    cin >> z >> m >> c >> n;
    n++; // add imaginary hiding spot at 0 to make implementation easier
    vector<ll> a(n);
    for(int i = 1; i < n; i++) cin >> a[i];

    // dp[i] = minimum cost when we are at the i-th hiding spot when the 
    //         time passed since we started walking is divisible by t.
    // This can be calculated by iterating over all possible j < i assuming
    // that j was the last hiding spot we visited at time divisible by t.
    // Then, it's optimal to not stand still between a[j] and a[i].
    vector<ll> dp(n, inf);
    dp[0] = 0;
    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            ll d = a[i]-a[j];
            ll place = c * ((d-1)/m);
            ll t = ((d+m-1)/m)*m;
            ll cost = dp[j]+place+t;
            dp[i] = min(dp[i], cost);
        }
    }
    // The calculation for the gaol is a bit different, since we don't need to wait
    // there until the time is divisible by t.
    ll ans = inf;
    for(int i = 0; i < n; i++){
        ll d = z-a[i];
        ll place = c * ((d-1)/m);
        ans = min(ans, dp[i]+place+d);
    }
    cout << ans << "\n";
}
