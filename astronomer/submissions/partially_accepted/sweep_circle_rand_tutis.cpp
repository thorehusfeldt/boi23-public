/* 
 *  # @EXPECTED_GRADES@ AC AC AC AC AC AC AC
 */ 
#include <bits/stdc++.h>
using namespace std;
using ld = double;
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
bool operator==(point a, point b)
{
	return abs(a.x - b.x) + abs(a.y - b.y) <= 0.5;
}
mt19937_64 rng(813897123);
ld Err(ld a, ld b)
{
	ld d = abs(b - a);
	ld m = max(ld(1), max(abs(a), abs(b)));
	return d / m;
}
int main()
{
	int n, k;
	int s, t;
	cin >> k >> n >> s >> t;
	point A[n];
	ld st = ld(s) / ld(max(1, t));
	for (int i = 0; i < n; i++)
		cin >> A[i].x >> A[i].y;
	shuffle(A, A + n, rng);
	auto check = [&](int i, ld r, ld eps)->bool
	{
		if (r <= 0)
			return false;
		auto cost = [&](point x)->ld
		{
			return (x - A[i]).r() + x.r() * st;
		};
		if(cost(A[i]) > r)
			return false;
		int cnt = 0;
		vector<pair<ld, int>>E;
		for (int j = 0; j < n; j++)
		{
			if (A[j] == A[i])
				cnt++;
			else
			{
				point m = (A[i] + A[j]) * 0.5;
				point dir = (A[i] - A[j]) * point(0, 1);
				dir = dir * (1 / dir.r());
				ld mx = 2e9;

				ld lo = -mx;
				ld hi = mx;
				bool fnd = false;
				ld k;
				if (cost(m) <= r)
				{
					fnd = true;
					k = 0;
				}
				while (Err(lo, hi) > eps && fnd == false)
				{
					ld k0 = (lo * 2 + hi) / 3;
					ld k1 = (lo + hi * 2) / 3;
					point p0 = m + dir * k0;
					point p1 = m + dir * k1;
					ld d0 = cost(p0);
					ld d1 = cost(p1);
					if (d0 <= r)
					{
						fnd = true;
						k = k0;
					}
					else if (d1 <= r)
					{
						fnd = true;
						k = k1;
					}
					else
					{
						if (d0 < d1)
							hi = k1;
						else
							lo = k0;
					}
				}
				if (!fnd)
					continue;
				vector<point>X;
				for (ld hi1 : {lo, hi})
				{
					ld lo1 = k;
					while (Err(lo1, hi1) > eps)
					{
						ld mi = (lo1 + hi1) / 2;
						point p = m + dir * mi;
						if (cost(p) <= r)
							lo1 = mi;
						else
							hi1 = mi;
					}
					ld mi = (lo1 + hi1) / 2;
					X.push_back(m + dir * mi - A[i]);
				}

				ld l = atan2(X[0].y, X[0].x);
				ld r = atan2(X[1].y, X[1].x);
				if (l > r)
					swap(l, r);
				if (abs(l - r) <= acosl(-1))
				{
					E.push_back({l, 1});
					E.push_back({r, -1});
				}
				else
				{
					cnt++;
					E.push_back({l, -1});
					E.push_back({r, 1});
				}
			}
		}
		sort(E.begin(), E.end());
		if (cnt >= k)
			return true;
		for (auto i : E)
		{
			cnt += i.second;
			if (cnt >= k)
				return true;
		}
		return false;
	};
	if (t <= s)
	{
		vector<ld>D;
		for (int i = 0; i < n; i++)
			D.push_back(A[i].r());
		sort(D.begin(), D.end());
		cout << fixed << setprecision(15) << D[k - 1] * t << "\n";
		return 0;
	}
	const ld eps = 1e-10;
	const ld eps1 = 1e-15;
	ld best = 1e20;
	for (int i = 0; i < n; i++)
	{
		ld better = best > 1 ? best * (1 - eps) : best - eps;
		if (check(i, better, eps) == false)
			continue;
		if (check(i, better, eps1) == false)
			continue;
		ld lo = 0;
		ld hi = better;
		while (Err(lo, hi) > eps1)
		{
			ld m = (lo + hi) / 2;
			if (check(i, m, eps1))
				hi = m;
			else
				lo = m;
		}
		best = (lo + hi) / 2;
	}
	cout << fixed << setprecision(15) << best * t << "\n";
}
