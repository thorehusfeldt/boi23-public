/*
 *  runs in O(n^3 lg n)
 *  
 *  # @EXPECTED_GRADES@ TLE AC TLE AC AC TLE TLE
 */ 
#include <bits/stdc++.h>
using namespace std;
using ld = long double;
struct point
{
	ld x, y;
	point() {}
	point(ld x, ld y): x(x), y(y) {}
	ld r()
	{
		return sqrtl(x * x + y * y);
	}
};
point operator+(point a, point b)
{
	return point(a.x + b.x, a.y + b.y);
}
point operator-(point a, point b)
{
	return point(a.x - b.x, a.y - b.y);
}
point operator*(point a, point b)
{
	return point(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}
point operator*(point a, ld k)
{
	return point(a.x * k, a.y * k);
}
point operator*(ld k, point a)
{
	return point(a.x * k, a.y * k);
}
const ld eps = 1e-9;
bool operator!=(point a, point b)
{
	return abs(a.x - b.x) + abs(a.y - b.y) > eps;
}
bool operator==(point a, point b)
{
	return abs(a.x - b.x) + abs(a.y - b.y) <= eps;
}
ld cross(point a, point b)
{
	return a.x * b.y - a.y * b.x;
}
ld t0(point a, point x, point b, point y)
{
	//a+xk=b+yl
	//ay+xyk=by
	//k = (b-a)y/xy
	return cross(b - a, y) / cross(x, y);
}
int main()
{
	int n, k;
	int s, t;
	cin >> k >> n >> s >> t;
	if(s == 0 && t == 0)  {
		cout << 0 << endl;
		return 0;
	}
	point A[n];
	for (int i = 0; i < n; i++)
		cin >> A[i].x >> A[i].y;
	ld ret = 1e20;
	auto check = [&](point a, point b)
	{
		if (a == b && a == point(0, 0))
			return;
		point p0 = (a + b) * 0.5;
		point d = (a != b) ? ((b - a) * point(0, 1)) : a;
		ld lo = -1e12;
		ld hi = 1e12;
		auto cost = [&](ld k)->ld
		{
			point x = p0 + k * d;
			return (x - a).r() * t + x.r() * s;
		};
		while (abs(hi - lo) > 1e-12)
		{
			ld k1 = (lo * 2 + hi) / 3;
			ld k2 = (lo + hi * 2) / 3;
			if (cost(k1) < cost(k2))
				hi = k2;
			else
				lo = k1;
		}
		vector<pair<ld, int>>E = {{(lo + hi) / 2, 0}};
		ld cnt = 0;
		for (int j = 0; j < n; j++)
		{
			if (abs(cross(A[j] - a, b - a)) < 0.1)
			{
				if ((A[j] - p0).r() <= (p0 - a).r() + 0.1)
					cnt++;
			}
			else
			{
				ld k = t0(p0, d, (A[j] + a) * 0.5, (A[j] - a) * point(0, 1));
				if (t0(p0, d, A[j], d * point(0, 1)) < 0)
				{
					cnt++;
					E.push_back({k + eps, -1});
				}
				else
					E.push_back({k - eps, 1});
			}
		}
		sort(E.begin(), E.end());
		for (auto i : E)
		{
			if (cnt >= k || cnt + i.second >= k)
				ret = min(ret, cost(i.first));
			cnt += i.second;
		}
	};
	vector<ld>D;
	for (int i = 0; i < n; i++)
		D.push_back(A[i].r());
	if (k == 1)
		for (int i = 0; i < n; i++)
			ret = min(ret,A[i].r()*s);
	sort(D.begin(), D.end());
	ret = min(ret, D[k - 1] * t);
	cout << fixed << setprecision(10);
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= i; j++)
			check(A[i], A[j]);
	cout << ret << "\n";
}