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

// ��Ÿ, 2��Ÿ, 3��Ÿ�� �� ���� ���
int run(int how)
{
	int sum = 0;
	for (int i = 2; i >= 0; i--)
	{
		// �翡 ������ �ִ��� Ȯ��
		if (!land[i])
			continue;

		// Ȩ���� �� ��� ������ ���� �� �ش� ��ġ�� false
		if (i + how >= 3)
		{
			sum++;
			land[i] = false;
		}
		// ��� �̵��� ��� 
		// �̵��� �翡 true, ���� ��ġ�� fasle
		else
		{
			land[i + how] = true;
			land[i] = false;
		}
	}

	// ���� Ÿ���� �̵� ��ġ ǥ��
	land[how - 1] = true;
	return sum;
}

// ������ ����
void game()
{
	int orderIdx = 0;	// order�� �ε���
	int score = 0;		// �̹� ������ ����

	// �̴� �� ��ŭ ���� ����
	for (int i = 0; i < inning; i++)
	{
		// �� �̴� �ƿ�ī��Ʈ�� �ʱ�ȭ
		int outCnt = 0;

		// �����Ҷ��� 1,2,3��� ��� ������ִ�.
		for (int i = 0; i < 3; i++)
			land[i] = false;

		// �ƿ� ī��Ʈ�� 3�� �� ������ ���� ����
		while (outCnt != 3)
		{
			// �� �̴��� Ÿ���� ����� üũ
			switch (person[i][order[orderIdx++]])
			{
			// 0�� �ƿ�
			case 0:
				outCnt++;
				break;

			// ��Ÿ
			case 1:
				score += run(1);
				break;
			
			// 2��Ÿ
			case 2:
				score += run(2);
				break;

			// 3��Ÿ
			case 3:
				score += run(3);
				break;
			
			// Ȩ��
			case 4:
				score++;

				// �� �翡 �ִ� �������� ��� Ȩ���� ���� ������
				// ������ �ִٸ� ���� ���� �� �ش� ��ġ�� false���ش�.
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
			
			// ���� Ÿ�ڸ� ����
			orderIdx = orderIdx % 9;
		}
	}

	result = max(result, score);
}

// Ÿ���� ���� ���ϱ�
void dfs(int cnt)
{
	// ������ ��� ���������� ������ �����Ѵ�.
	if (cnt == 9)
	{
		game();
		return;
	}
	
	// 4��°Ÿ�ڴ� �̹� ������ �����Ƿ� ���� Ÿ�ڸ� ���Ѵ�.
	// �ε��� 0 -> ù��° Ÿ��, �ε��� 1 -> �ι�° Ÿ��, ...
	if (cnt == 3)
	{
		dfs(cnt + 1);
		return;
	}
	for (int i = 0; i < 9; i++)
	{
		// �̹� ������ ������ Ÿ�� üũ
		if (visited[i])
			continue;	
		
		visited[i] = true;
		order[cnt] = i;

		// ���� ������ Ÿ�ڸ� ���Ѵ�.
		dfs(cnt + 1);

		visited[i] = false;

	}
}

// �Է�
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

	// �Է�
	input();

	// Ÿ���� ���� ���ϱ�
	dfs(0);

	// ���
	cout << result << '\n';
	return 0;
}
