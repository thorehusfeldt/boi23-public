// @EXPECTED_GRADES@ WA AC WA TLE WA WA

// assumes all weights are = 1
// uses an additional optimization where we try +1 first at every depth
//
//  n     depth        time
//  300      11        0.1s
//  479      11+       0.1s
//  500      11+       0.1s
//  700      11+       0.1s
//  718      12        1.6s
//  719      12+       1.6s
// 1400      12+       2.3s
// 1438      13+      32.5s

#include <bits/stdc++.h>
using namespace std;

const int inf = 1.01e9;
int n;

struct Push_Guard{
    Push_Guard(vector<int> &v_, int x) : v(v_){
        v.push_back(x);
    }
    ~Push_Guard(){
        v.pop_back();
    }

    vector<int> &v;
};

vector<char> hit;

uint64_t steps = 0;

void brute(vector<int> &v, int d){
    ++steps;
    const int k = v.back();
    hit[k] = 1;
    if(d == 0) return;
    // try k -> k+1
    if(k < n) {
        Push_Guard p{v, k+1};
        brute(v, d-1);
    }
    // try products
    for(int i = 0; i < (int)v.size(); ++i){
        for(int j = i; j < (int)v.size(); ++j){
            const int x = v[i]*v[j];
            if(x > k && x <= n){
                Push_Guard p{v, x};
                brute(v, d-1);
            }
        }
    }
}

signed main(){
    cin >> n;
    vector<int> ans(n+1, -1);
    hit.assign(n+1, 0);
    ans[0] = 0;
    hit[0] = 1;

    auto done = [&](){ return !count(ans.begin(), ans.end(), -1); };
    for(int d=1; !done(); ++d){
        // try +1 first
        for(int i = n; i > 0; --i){
            if(hit[i-1] && !hit[i]){
                hit[i] = 1;
                ans[i] = ans[i-1] + 1;
            }
        }
        cerr << " fast: " << setw(2) << d-1 << "+, found: " << setw(5) << count(hit.begin(), hit.end(), 1) << ", missing: " << setw(5) << count(hit.begin(), hit.end(), 0) << ", steps: " << steps << "\n";
        if(!done()){
            vector<int> v{1};
            brute(v, d-1);
            for(int i=1; i<=n; ++i){
                if(ans[i] == -1 && hit[i]) ans[i] = d;
            }
            cerr << "depth: " << setw(3) << d << ", found: " << setw(5) << count(hit.begin(), hit.end(), 1) << ", missing: " << setw(5) << count(hit.begin(), hit.end(), 0) << ", steps: " << steps << "\n";
        }
    }

    for(int i=1; i<=n; ++i){
        cout << ans[i] << "\n";
    }

}
