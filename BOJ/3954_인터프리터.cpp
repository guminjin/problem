#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_M = 100000 + 1;	// �޸��� �ִ� ũ��
const int MOD = 256;			// �޸𸮿� ������ �� �ִ� ���� �ִ밪 + 1
const int INF = 987654321;

int t;
int sm, sc, si;
int mem[MAX_M];
string code, input;

void solve()
{
	int time;
	int memIdx, codeIdx, inputIdx;			// �޸�, �ڵ�, �Է��� �ε���
	time = memIdx = codeIdx = inputIdx = 0;

	int loopStart, loopEnd = 0;

	// ��ɾ 5õ���� ���Ϸ� ����
	while (time <= 50000000)
	{
		// codeIdx�� sc�� ������ �ڵ带 ��� ���������Ƿ� ����
		if (codeIdx >= sc)
			break;
		
		// ��ɾ� �� ����
		time++;

		// �ڵ�Ȯ��
		switch (code[codeIdx])
		{
		case '-':
			// �޸��� �ش� �ε����� �ִ� ���� ����
			mem[memIdx]--;

			// ���� 0���� �۾����� 255�� ����
			if (mem[memIdx] < 0)
				mem[memIdx] = 255;

			// ���� �ڵ�� ����
			codeIdx++;
			break;
		case '+':
			// �޸��� �ش� �ε����� �ִ� ���� ���� �� 256���� ������ ����
			mem[memIdx] = (mem[memIdx] + 1) % MOD;

			// ���� �ڵ�� ����
			codeIdx++;
			break;
		case '<':
			// mem�� �ε����� �ϳ� ����
			memIdx--;

			// mem�� �ε��� ��ġ�� 0���� ������ �޸��� ���� ������ �ε����� ����
			if (memIdx < 0)
				memIdx = sm - 1;

			// ���� �ڵ�� ����
			codeIdx++;
			break;
		case '>':
			// �޸��� �ε����� ���� �� �޸� ũ��� ������ ����
			memIdx = (memIdx + 1) % sm;

			// ���� �ڵ�� ����
			codeIdx++;
			break;
		case '[':
			// �޸��� �ش� �ε��� ���� 0�̶��
			if (mem[memIdx] == 0)
			{
				// ��ȣ�� ���� ã��
				int ch = 1;
				while (1)
				{
					if (code[++codeIdx] == '[')
						ch++;
					else if (code[codeIdx] == ']')
						ch--;
					else
						continue;

					if (ch == 0)
						break;
				}
			}
			// �޸��� �ش� �ε����� ���� 0�� �ƴ϶��
			else
				codeIdx++;	// ���� �ڵ�� ����
			break;
		case ']':
			// �޸��� �ش� �ε����� ���� 0�� �ƴ϶��
			if (mem[memIdx] != 0)
			{
				// loopEnd�� ���� ']'�� �ε������� ������
				// ������ ��ȣ�� �������Ա� ������
				// ���ο� �� ����
				if(loopEnd < codeIdx)
					loopEnd = codeIdx;

				// ��ȣ�� ���� ã��
				int ch = -1;
				while (1)
				{
					if (code[--codeIdx] == '[')
						ch++;
					else if (code[codeIdx] == ']')
						ch--;
					else
						continue;

					if (ch == 0)
						break;
				}
			}
			// �޸��� �ش� �ε����� ���� 0�̶��
			else
				codeIdx++;	// ���� �ڵ�� ����
			break;
		case '.':
			codeIdx++;
			break;
		case ',':
			if (inputIdx < si)
				mem[memIdx] = input[inputIdx++];
			else
				mem[memIdx] = 255;
			codeIdx++;
			break;
		}
	}

	// ��ɾ 5õ�������Ϸ� ���� �� ���α׷� ����
	if (time <= 50000000)
		cout << "Terminates\n";
	// ��ɾ 5õ���� �̻� �����ϰ� �Ǹ� ���� ����
	else
	{
		// loopStart�� ã�´�.
		loopStart = loopEnd;

		int ch = -1;
		while (1)
		{
			if (code[--loopStart] == '[')
				ch++;
			else if (code[loopStart] == ']')
				ch--;
			else
				continue;

			// ch �� 0�� �Ǹ� �ش� ���� ã��
			if (ch == 0)
				break;
		}
		cout << "Loops " << loopStart << ' ' << loopEnd << '\n';
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin >> t;
	for (int tc = 0; tc < t; tc++)
	{
		memset(mem, 0, sizeof(mem));
		cin >> sm >> sc >> si;
		cin >> code;
		cin >> input;


		solve();
	}
	return 0;
}
