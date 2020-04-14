#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX = 10;
const int INF = 987654321;

int n;
int numSize, operSize;	// 숫자와 연산의 개수
int result = -INF;		
int num[MAX];			// 숫자 저장
char oper[MAX];			// 연산 저장
int group[MAX];			// 괄호를 만들 수 있는 모든 연산의 결과값 저장
bool visited[MAX];		// 괄호를 사용하였는지 체크

// 사칙연산
int cal(char oper, int n1, int n2)
{
	switch (oper)
	{
	case '+':
		return n1 + n2;
	case '-':
		return n1 - n2;
	case '*':
		return n1 * n2;
	case '/':
		return n1 / n2;
	}
}

// 최대값 찾기
void mxresult()
{
	// 해당 연산의 값을 저장
	int sum = 0;
	for (int i = 0; i < operSize; i++)
	{
		// i번째 연산에 괄호가 있으면
		if (visited[i])
			sum += group[i];

		// i번쩨 연산에괄호가 없을 때
		else
		{
			// 첫번째 연산이라면
			if (i == 0)
				sum = num[0];

			// 다음 연산이 괄호로 묶여서 이미 계산되어있다면
			if (visited[i + 1])
			{
				sum = cal(oper[i], sum, group[i + 1]);
				i += 1;
			}
			else
				sum = cal(oper[i], sum, num[i + 1]);
		}
	}
	// 최대값 비교
	result = max(result, sum);
}

// 괄호의 경우의 수를 모두 수행
void dfs(int idx)
{
	// 최대값 찾기
	mxresult();

	for (int i = idx; i < operSize; i++)
	{
		// 이미 방문한 배열 체크
		if (visited[i])
			continue;

		// 이중 괄호 체크
		if (visited[i - 1] && i != 0)
			continue;
		
		// 괄호 사용
		visited[i] = true;

		dfs(i + 1);

		// 괄호 사용 취소
		visited[i] = false;
	}
}

// 입력
void input()
{
	cin >> n;
	numSize = n / 2 + 1;
	operSize = n / 2;

	// 수식 입력
	string s; cin >> s;
	
	// 숫자만 num에 저장
	int idx = 0;
	for (int i = 0; i < numSize; i++)
	{
		num[i] = (s[idx] - '0');
		idx += 2;
	}

	// 연산만 oper에 저장
	idx = 1;
	for (int i = 0; i < operSize; i++)
	{
		oper[i] = s[idx];
		idx += 2;
	}

	// 괄호를 만들 수 있는 모든 수의 연산을 group에 저장
	int numIdx = 0;
	for (int i = 0; i < operSize; i++)
	{
		group[i] = cal(oper[i], num[numIdx], num[numIdx + 1]);
		numIdx++;
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	input();
	if (n == 1)
		cout << num[0] << '\n';
	else
	{
		dfs(0);
		cout << result << '\n';
	}
	return 0;
}
