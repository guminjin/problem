#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define endl '\n'

typedef long long ll;

struct XY {
	double x, y;
};

double calDistance(XY a, XY b) {
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	
	XY a, b, c, d;
	cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
	
	double min = calDistance(a, c);

	int interval = 1000000;

	XY aInter, cInter;
	aInter.x = (b.x - a.x) / interval;
	aInter.y = (b.y - a.y) / interval;
	cInter.x = (d.x - c.x) / interval;
	cInter.y = (d.y - c.y) / interval;

	for (int i = 1; i <= interval; i++) {
		double t = calDistance({ a.x + aInter.x * i, a.y + aInter.y * i },
					{ c.x + cInter.x * i, c.y + cInter.y * i });
		if (t < min)
			min = t;
	}
	cout << min << '\n';
	return 0;
}
