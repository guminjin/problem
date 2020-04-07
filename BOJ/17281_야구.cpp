#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 50 + 1;

int inning;
int person[MAX][9];
bool visited[9];
int order[9];
bool land[3];
int result;

// 안타, 2루타, 3루타일 때 점수 계산
int run(int how)
{
	int sum = 0;
	for (int i = 2; i >= 0; i--)
	{
		// 루에 선수가 있는지 확인
		if (!land[i])
			continue;

		// 홈으로 올 경우 점수를 증가 후 해당 위치는 false
		if (i + how >= 3)
		{
			sum++;
			land[i] = false;
		}
		// 루로 이동할 경우 
		// 이동한 루에 true, 원래 위치는 fasle
		else
		{
			land[i + how] = true;
			land[i] = false;
		}
	}

	// 현재 타자의 이동 위치 표시
	land[how - 1] = true;
	return sum;
}

// 게임을 시작
void game()
{
	int orderIdx = 0;	// order의 인덱스
	int score = 0;		// 이번 게임의 점수

	// 이닝 수 만큼 게임 진행
	for (int i = 0; i < inning; i++)
	{
		// 매 이닝 아웃카운트는 초기화
		int outCnt = 0;

		// 시작할때는 1,2,3루는 모두 비어져있다.
		for (int i = 0; i < 3; i++)
			land[i] = false;

		// 아웃 카운트가 3이 될 때까지 무한 루프
		while (outCnt != 3)
		{
			// 각 이닝의 타자의 결과를 체크
			switch (person[i][order[orderIdx++]])
			{
			// 0은 아웃
			case 0:
				outCnt++;
				break;

			// 안타
			case 1:
				score += run(1);
				break;
			
			// 2루타
			case 2:
				score += run(2);
				break;

			// 3루타
			case 3:
				score += run(3);
				break;
			
			// 홈런
			case 4:
				score++;

				// 각 루에 있는 선수들이 모두 홈으로 오기 때문에
				// 선수가 있다면 점수 증가 후 해당 위치를 false해준다.
				for (int j = 0; j < 3; j++)
				{
					if (land[j])
					{
						score++;
						land[j] = false;
					}
				}
				break;
			}
			
			// 다음 타자를 결정
			orderIdx = orderIdx % 9;
		}
	}

	result = max(result, score);
}

// 타자의 순서 정하기
void dfs(int cnt)
{
	// 순서가 모두 정해졌으면 게임을 시작한다.
	if (cnt == 9)
	{
		game();
		return;
	}
	
	// 4번째타자는 이미 정해져 있으므로 다음 타자를 정한다.
	// 인덱스 0 -> 첫번째 타자, 인덱스 1 -> 두번째 타자, ...
	if (cnt == 3)
	{
		dfs(cnt + 1);
		return;
	}
	for (int i = 0; i < 9; i++)
	{
		// 이미 순서가 정해진 타자 체크
		if (visited[i])
			continue;	
		
		visited[i] = true;
		order[cnt] = i;

		// 다음 순서의 타자를 정한다.
		dfs(cnt + 1);

		visited[i] = false;

	}
}

// 입력
void input()
{
	cin >> inning;
	for (int i = 0; i < inning; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cin >> person[i][j];
		}
	}

	order[3] = 0;
	visited[0] = true;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	// 입력
	input();

	// 타자의 순서 정하기
	dfs(0);

	// 결과
	cout << result << '\n';
	return 0;
}
