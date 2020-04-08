#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 15 + 1;

// queue
struct INFO
{
	int y, x;
	int dis;
};

int garo, sero, dis;
int map[MAX][MAX];		
int visited[MAX][MAX];
int origin[MAX][MAX];	// 초기 map
bool archer[MAX];		// 궁수의 위치
int result;

int X[3] = { -1, 0, 1 };
int Y[3] = { 0, -1, 0 };

bool checkTarget()
{
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			if (map[y][x])
				return false;
		}
	}
	return true;
}
void moveTarget()
{
	for (int y = sero - 1; y >= 0; y--)
	{
		for (int x = 0; x < garo; x++)
		{
			if (!map[y][x])
				continue;
			else
			{
				if (y + 1 == sero)
				{
					map[y][x] = 0;
					continue;
				}

				map[y][x] = 0;
				map[y + 1][x] = 1;
			}
		}
	}
}

// 한번의 공격에 잡을 수 있는 적의 수 구하기
int findTarget()
{
	int targetX[3];	// 총 세명의 궁수가 잡을 수 있는 적의 위치를 저장
	int targetY[3];
	for (int i = 0; i < 3; i++)
		targetX[i] = targetY[i] = -1;
	
	int targetIdx = 0;

	// archer[i]가 true라면 i번째 위치에 궁수가 있다.
	for (int i = 0; i < garo; i++)
	{
		// 해당 위치에 궁수가 있는지 확인
		if (!archer[i])
			continue;

		memset(visited, 0, sizeof(visited));
		queue<INFO> q;
		q.push({ sero, i, 0 });
		
		bool flg = false;	// 궁수가 적을 잡았는지 확인
		int distance = 0;	// 거리가 dis이하일 때 까지 탐색

		// 적을 잡으면 반복을 종료
		while (!flg)
		{
			INFO now = q.front(); q.pop();	
			INFO next;						
			
			// 공격 거리 제한보다 크면 종료
			if (now.dis == dis)
				break;

			// 왼쪽, 위, 오른쪽 방향 순서로 적이 있는지 확인
			for (int j = 0; j < 3; j++)
			{
				next.y = now.y + Y[j];
				next.x = now.x + X[j];
				next.dis = now.dis + 1;

				// 범위체크
				if (next.x < 0 || next.y < 0 || next.x >= garo || next.y >= sero)
					continue;
				//이미 방문한 위치인지 체크
				if (visited[next.y][next.x])
					continue;

				// 해당 위치에 적이 있다면, 
				// target에 위치를 저장 후 적을 잡았다고 flg를 true로 변경
				// while문 종료
				if (map[next.y][next.x])
				{
					flg = true;
					targetX[targetIdx] = next.x;
					targetY[targetIdx] = next.y;
					break;
				}

				// 해당 위치에 적이 없다면,
				// q에 push
				visited[next.y][next.x] = true;
				q.push(next);
			}
		}
		// 다음 궁수
		targetIdx++;
	}

	int findCnt = 0;
	for (int i = 0; i < 3; i++) 
	{
		if (targetX[i] == -1 || targetY[i] == -1)
			continue;
		if (!map[targetY[i]][targetX[i]])
			continue;

		map[targetY[i]][targetX[i]] = 0;
		findCnt++;
	}

	return findCnt;
}

// 궁수의 위치를 정한다.
void selectArcherLocation(int idx, int cnt)
{
	// 세명의 궁수의 위치가 정해졌다면
	if (cnt == 3) 
	{
		// 처음 상태를 복구시켜준다.
		for (int y = 0; y < sero; y++)
		{
			for (int x = 0; x < garo; x++)
			{
				map[y][x] = origin[y][x];
			}
		}

		// 잡은 적의 수
		int sum = 0;
		// map에 적들이 모두 사라질 때까지 반복
		while (!checkTarget())
		{
			// 한번의 공격에 잡을 수 있는 적의 수 구하기
			sum += findTarget();
			moveTarget();
		}

		// 많은 적을 잡았을 경우 갱신
		result = max(result, sum);

		return;
	}

	for (int i = 0; i < garo; i++)
	{
		// 이미 선택된 궁수의 위치인지 체크
		if (archer[i])
			continue;

		// 선택되었다고 표시
		archer[i] = true;
		
		// 다음 궁수의 위치를 찾는다.
		selectArcherLocation(i + 1, cnt + 1);

		// 선택취소
		archer[i] = false;

	}
}

// 입력
void input()
{
	cin >> sero >> garo >> dis;
	for (int y = 0; y < sero; y++)
	{
		for (int x = 0; x < garo; x++)
		{
			cin >> map[y][x];
			origin[y][x] = map[y][x];
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	selectArcherLocation(0, 0);
	cout << result << '\n';
	return 0;
}
