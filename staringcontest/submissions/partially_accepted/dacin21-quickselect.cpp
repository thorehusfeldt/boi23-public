#include <bits/stdc++.h>
using namespace std;

map<pair<int, int>, int> cache;
int cnt = 0;
int ask(int i, int j){
	if(i > j) swap(i, j);
	auto key = make_pair(i, j);
	if(!cache.count(key)){
		cout << "? " << i+1 << " " << j+1 << "\n";
		int ans;
		cin >> ans;
		cache[key] = ans;
	}
	return cache[key];
}
int n;
vector<int> out;

pair<int, int> solve_2n(vector<int> cands){
	int a = cands[0], b = cands[1];
	int cur = ask(a, b);
	for(int i=2; i<(int)cands.size(); ++i){
		const int c = cands[i];
		const int x = ask(a, c), y = ask(b, c);
		if(x == cur){
			out[a] = x;
			cur = y;
			a = c;
		} else if(y == cur){
			out[b] = y;
			cur = x;
			b = c;
		} else {
			assert(x == y);
			out[c] = x;
		}
	}
	return {a, b};
}
mt19937 rng(53253290432532ll);
pair<int, int> solve(vector<int> cands){
	shuffle(cands.begin(), cands.end(), rng);
	const int BLOCK = 60;
	const int m = min<int>(BLOCK, cands.size());
	// get pivots
	auto [a, b] = solve_2n(vector<int>(cands.begin(), cands.begin()+m));
	cands.erase(cands.begin(), cands.begin()+m);
	if(cands.empty()) return {a, b};
	// do partition step
	vector<int> new_cands = {a, b};
	const int z = ask(a, b);
	for(int c : cands){
		const int x = ask(a, c);
		if(x < z){
			out[c] = x;
		} else {
			new_cands.push_back(c);
		}
		swap(a, b);
	}
	// recurse on values larger than pivots
	return solve(new_cands);	
}



signed main(){
	int n;
	cin >> n;
	out.assign(n, -1);
	vector<int> ord(n);
	iota(ord.begin(), ord.end(), 0);
	auto [a, b] = solve(ord);
	out[a] = out[b] = ask(a, b);
	cout << "! ";
	for(auto const&e : out) cout << e << " ";
	cout << "\n";

}
