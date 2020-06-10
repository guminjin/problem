#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
#include <set>
#include <queue>

using namespace std;

#define endl '\n'

typedef long long ll;\

int a, b, c, num;

bool check()
{
	// a, b, c의 방으로 학생의 수가 나눠지는지 확인
	if (num%a == 0 || num % b == 0 || num % c == 0)
		return true;
	else
	{
		// c로 나눌 때 가장 큰 몫
		int divC = num / c;		

		// c의 최대 방 개수부터 0까지 확인
		for (int i = divC; i >= 0; i--)
		{
			// c의 방이 i개 사용했을 때 남은 학생 수
			int modC = num - (c*i);

			// b로 나눌 때 가장 큰 몫
			int divB = modC / b;	

			// b의 최대 방 개수부터 0까지 확인
			for (int j = divB; j >= 0; j--)
			{
				int modB;

				// b로 나누어지지 않을 경우
				if (divB == 0)
					modB = modC;
				else
					modB = modC - (b*j);

				if (modB%a == 0)
					return true;
			}
		}
	}
	return false;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> a >> b >> c >> num;	

	cout << check() << '\n';
	return 0;
}
