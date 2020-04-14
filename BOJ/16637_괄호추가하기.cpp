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
int numSize, operSize;	// ���ڿ� ������ ����
int result = -INF;		
int num[MAX];			// ���� ����
char oper[MAX];			// ���� ����
int group[MAX];			// ��ȣ�� ���� �� �ִ� ��� ������ ����� ����
bool visited[MAX];		// ��ȣ�� ����Ͽ����� üũ

// ��Ģ����
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

// �ִ밪 ã��
void mxresult()
{
	// �ش� ������ ���� ����
	int sum = 0;
	for (int i = 0; i < operSize; i++)
	{
		// i��° ���꿡 ��ȣ�� ������
		if (visited[i])
			sum += group[i];

		// i���� ���꿡��ȣ�� ���� ��
		else
		{
			// ù��° �����̶��
			if (i == 0)
				sum = num[0];

			// ���� ������ ��ȣ�� ������ �̹� ���Ǿ��ִٸ�
			if (visited[i + 1])
			{
				sum = cal(oper[i], sum, group[i + 1]);
				i += 1;
			}
			else
				sum = cal(oper[i], sum, num[i + 1]);
		}
	}
	// �ִ밪 ��
	result = max(result, sum);
}

// ��ȣ�� ����� ���� ��� ����
void dfs(int idx)
{
	// �ִ밪 ã��
	mxresult();

	for (int i = idx; i < operSize; i++)
	{
		// �̹� �湮�� �迭 üũ
		if (visited[i])
			continue;

		// ���� ��ȣ üũ
		if (visited[i - 1] && i != 0)
			continue;
		
		// ��ȣ ���
		visited[i] = true;

		dfs(i + 1);

		// ��ȣ ��� ���
		visited[i] = false;
	}
}

// �Է�
void input()
{
	cin >> n;
	numSize = n / 2 + 1;
	operSize = n / 2;

	// ���� �Է�
	string s; cin >> s;
	
	// ���ڸ� num�� ����
	int idx = 0;
	for (int i = 0; i < numSize; i++)
	{
		num[i] = (s[idx] - '0');
		idx += 2;
	}

	// ���길 oper�� ����
	idx = 1;
	for (int i = 0; i < operSize; i++)
	{
		oper[i] = s[idx];
		idx += 2;
	}

	// ��ȣ�� ���� �� �ִ� ��� ���� ������ group�� ����
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
