// @EXPECTED_GRADES@ AC TLE TLE TLE TLE TLE
#include <bits/stdc++.h>
using namespace std;

const int inf = 1.01e9;
int n;
vector<int> w;

template<typename S, typename T>
void xmin(S&a, T const&b){
    if(b < a) a = b;
}

int rec(set<int> nums){
    if(nums.size() == 1) return w[1];
    const int k = *nums.rbegin();
    nums.erase(k);
    int ret = inf;
    // try (k-1) -> k
    {
        auto nums2 = nums;
        nums2.insert(k-1);
        xmin(ret, rec(std::move(nums2)));
    }
    // try (k/d), (d) -> k
    {
        for(int d=2; d*d <= k; ++d) if(k%d == 0){
            auto nums2 = nums;
            nums2.insert(d);
            nums2.insert(k/d);
            xmin(ret, rec(std::move(nums2)));
        }
    }
    return ret + w[k];
}


signed main(){
    cin >> n;
    w.resize(n);
    for(auto &e : w) cin >> e;
    w.insert(w.begin(), -1);

    for(int i=1; i<=n; ++i){
        cout << rec({1, i}) << "\n";
    }

}
