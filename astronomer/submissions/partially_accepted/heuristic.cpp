// # @EXPECTED_GRADES@ AC WA WA WA WA WA WA
#include <bits/stdc++.h>
int n, k, s, t;
std::vector <std::pair <int, int>> a;

// object for profiling
struct Bes {
	double radius;
	double x, y;
	double walking_dist;
	double cost;
	bool operator < (const Bes& b) const {
		return cost < b.cost;
	}
	Bes& operator = (const Bes& b) {
		radius = b.radius;
		x = b.x;
		y = b.y;
		walking_dist = b.walking_dist;
		cost = b.cost;
		return *this;
	}
} bes = { 0, 0, 0, 0, 1e18 };

constexpr long long dist(const std::pair <int, int>& p) {
	return (long long) p.first * p.first + (long long) p.second * p.second;
}

constexpr double distd(const std::pair <double, double>& p) {
	return p.first * p.first + p.second * p.second;
}

double cost(double x, double y) {
	std::vector <double> d(n);
	for (int i = 0; i < n; ++i) {
		d[i] = distd({ a[i].first - x, a[i].second - y });
	}
	std::sort(d.begin(), d.end());
	double cst = std::sqrt(d[k - 1]) * t + std::sqrt(distd({ x, y })) * s;
	bes = std::min(bes, { std::sqrt(d[k - 1]), x, y, std::sqrt(distd({ x, y })), cst });
	return cst;
}

double search(double x, double y, double epsx, double epsy, int its_left) {
	if (its_left <= 0) {
		return cost(x, y);
	}
	std::pair <double, std::pair <double, double>> best = { cost(x, y), { x, y } };
	static std::random_device dev;
	static std::mt19937 gen(dev());
	static std::uniform_real_distribution <double> dis(-1, 1);
	for (int i = 0; i < 35; i++) {
		double nx = x + epsx * dis(gen);
		double ny = y + epsy * dis(gen);
		best = std::min(best, { cost(nx, ny), { nx, ny } });
	}
	return search(best.second.first, best.second.second, epsx / 1.7, epsy / 1.7, its_left - 1);
}

int main() {
	std::ios::sync_with_stdio(0); std::cin.tie(0);
	std::cin >> k >> n >> s >> t;
	a.resize(n);
	int mnx = 2e9, mxx = -2e9, mny = 2e9, mxy = -2e9;
	for (auto& p : a) {
		std::cin >> p.first >> p.second;
		mnx = std::min(mnx, p.first);
		mxx = std::max(mxx, p.first);
		mny = std::min(mny, p.second);
		mxy = std::max(mxy, p.second);
	}
	if (t <= s) {
		std::sort(a.begin(), a.end(), [] (const std::pair <int, int>& p, const std::pair <int, int>& q) {
			return dist(p) < dist(q);
		});
		std::cout << std::fixed << std::setprecision(10) << std::sqrt(dist(a[k - 1])) * t << "\n";
		return 0;
	}
	constexpr const int max_depth = 50;
	constexpr const int max_ops = 3e6;
	int grid_size = std::sqrt(max_ops / max_depth / n);
	double gapx = (double) (mxx - mnx) / grid_size;
	double gapy = (double) (mxy - mny) / grid_size;
	std::random_device dev;
	std::mt19937 gen(dev());
	std::uniform_real_distribution <double> disx(-gapx, gapx);
	std::uniform_real_distribution <double> disy(-gapy, gapy);
	double ans = 1e18;
	for (double x = mnx; x <= mxx + 2e-9; x += gapx + 1e-9) {
		for (double y = mny; y <= mxy + 2e-9; y += gapy + 1e-9) {
			ans = std::min(ans, search(x + disx(gen), y + disy(gen), gapx, gapy, max_depth));
		}
	}
	std::cout << std::fixed << std::setprecision(10) << ans << "\n";
	std::cerr << std::fixed << std::setprecision(10) << "cost: " << bes.cost << " point: (" << bes.x << ", " << bes.y <<
	") walking distance: " << bes.walking_dist << " circle radius: " << bes.radius << "\n";
}
