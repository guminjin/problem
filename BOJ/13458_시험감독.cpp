#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int EXAM = 1000000;
const int PERSON = 1000000;

int person[PERSON];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	// 시험장의 수 입력
	int n; cin >> n;
	
	// 시험장마다 응시자의 수 입력
	for (int i = 0; i < n; i++)
		cin >> person[i];
	
	// 총감독관과 부감독관의 감시할 수 있는 응시자 수
	int b, c; cin >> b >> c;

	// 최소 n명의 총감독관은 있어야한다.
	ll result = n;
	for (int i = 0; i < n; i++)
	{
		// 총감독관이 감시할 수 있는 응시자의 수를 제외
		int num = person[i] - b;

		// 제외했을 때 음수나 0이 된다면 총감독관으로만 감시 가능
		// 양수라면 부감독관이 필요
		if (num > 0)
		{
			int mod = num % c;
			int div = num / c;

			// 부감독관의 수를 더함
			result += div;

			// 나머지가 0이 아니라면 감시해야할 인원이 남았기에
			// 부감독관 한명을 더 추가
			if (mod)
				result++;
		}
	}

	cout << result << '\n';
	return 0;
}
