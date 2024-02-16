// SEQ
// solves n <= 1400 with unit weight in 10 minutes (going up to even 1440 will take more than hour)
// Author: Wojciech Nadara

#include <bits/stdc++.h>
using namespace std;

int best;
vector<int> best_c;
int n;
void bt(vector<int>& ciag) {
	if (ciag.back() == n) {
		best = ciag.size();
		best_c = ciag;
	}
	if (ciag.size() >= best - 1) { return; }
	if (ciag.back() * 2 > n && best <= ciag.size() + n - ciag.back()) { return; }
	set<int> cands{ciag.back() + 1};
	for (auto x : ciag) {
		for (auto y : ciag) {
			cands.insert(x * y);
		}
	}
	vector<int> cands_v(cands.begin(), cands.end());
	reverse(cands_v.begin(), cands_v.end());
	for (auto c : cands_v) {
		if (c > n || c <= ciag.back()) { continue; }
		ciag.push_back(c);
		bt(ciag);
		ciag.pop_back();
	}
}

int main() {
	long double ts = 0;
  for (int i = 1; i <= 1400; i++) {
		n = i;
		for (int b = 9; ; b++) {
			best = b;
			best_c = {};
			vector<int> ciag{1};
			bt(ciag);
			if (best < b) { break; }
		}
		long double nts = clock() * 1. / CLOCKS_PER_SEC;
    cerr<<i<<"\n";
		cout<<best<<"\n";
    //debug(nts - ts, i);//"<<nts-ts<<" "<<endl;
    ts = nts;
// 		for (auto x : best_c) {
// 			cout<<x<<" ";
// 		}
		//cout<<endl;
	}
	return 0;
}
