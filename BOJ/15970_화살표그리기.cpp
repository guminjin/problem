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

typedef long long ll;

const int MAX_COLOR = 5000 + 5;

// 색깔별 돌의 위치
vector<int> color[MAX_COLOR];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	// 돌의 개수 입력
	int n; cin >> n;
	for(int i = 0; i<n; i++)
	{
		int p, c; cin >> p >> c;
		
		// c컬러에 돌의 위치를 푸시
		color[c].push_back(p);
	}

	ll result = 0;	// 결과
	
	// 모든 색에 대한 돌을 확인
	for (int i = 0; i < MAX_COLOR; i++)
	{
		// 비어있거나 해당 색의 돌의 개수가 0이라면
		if (color[i].empty())
			continue;
		else if (color[i].size() == 1)
			continue;

		// 해당 색의 돌의 위치를 오름차순으로 정렬
		sort(color[i].begin(), color[i].end());
		int idxSize = color[i].size();	// 해당 색의 돌의 개수
		for (int j = 0; j < idxSize; j++)
		{
			// 위치가 가장 작은 돌
			if (j == 0)
				result += color[i][j + 1] - color[i][j];
			// 위치가 제일 큰 돌
			else if (j == idxSize - 1)
				result += color[i][j] - color[i][j - 1];
			else
			{
				int a = color[i][j + 1] - color[i][j];
				int b = color[i][j] - color[i][j - 1];
				result += min(a, b);
			}
		}
	}

	// 출력
	cout << result << '\n';
	return 0;
}
