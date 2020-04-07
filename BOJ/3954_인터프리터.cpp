#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAX_M = 100000 + 1;	// 메모리의 최대 크기
const int MOD = 256;			// 메모리에 저장할 수 있는 수의 최대값 + 1
const int INF = 987654321;

int t;
int sm, sc, si;
int mem[MAX_M];
string code, input;

void solve()
{
	int time;
	int memIdx, codeIdx, inputIdx;			// 메모리, 코드, 입력의 인덱스
	time = memIdx = codeIdx = inputIdx = 0;

	int loopStart, loopEnd = 0;

	// 명령어를 5천만번 이하로 실행
	while (time <= 50000000)
	{
		// codeIdx가 sc와 같으면 코드를 모두 실행했으므로 종료
		if (codeIdx >= sc)
			break;
		
		// 명령어 수 증가
		time++;

		// 코드확인
		switch (code[codeIdx])
		{
		case '-':
			// 메모리의 해당 인덱스에 있는 값을 감소
			mem[memIdx]--;

			// 값이 0보다 작아지면 255를 저장
			if (mem[memIdx] < 0)
				mem[memIdx] = 255;

			// 다음 코드로 진행
			codeIdx++;
			break;
		case '+':
			// 메모리의 해당 인덱스에 있는 값을 증가 후 256으로 나머지 연산
			mem[memIdx] = (mem[memIdx] + 1) % MOD;

			// 다음 코드로 진행
			codeIdx++;
			break;
		case '<':
			// mem의 인덱스를 하나 감소
			memIdx--;

			// mem의 인덱스 위치가 0보다 작으면 메모리의 제일 마지막 인덱스로 변경
			if (memIdx < 0)
				memIdx = sm - 1;

			// 다음 코드로 진행
			codeIdx++;
			break;
		case '>':
			// 메모리의 인덱스를 증가 후 메모리 크기로 나머지 연산
			memIdx = (memIdx + 1) % sm;

			// 다음 코드로 진행
			codeIdx++;
			break;
		case '[':
			// 메모리의 해당 인덱스 값이 0이라면
			if (mem[memIdx] == 0)
			{
				// 괄호의 쌍을 찾음
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
			// 메모리의 해당 인덱스의 값이 0이 아니라면
			else
				codeIdx++;	// 다음 코드로 진행
			break;
		case ']':
			// 메모리의 해당 인덱스의 값이 0이 아니라면
			if (mem[memIdx] != 0)
			{
				// loopEnd의 값이 ']'의 인덱스보다 작으면
				// 이전의 괄호를 빠져나왔기 때문에
				// 새로운 값 갱신
				if(loopEnd < codeIdx)
					loopEnd = codeIdx;

				// 괄호의 쌍을 찾음
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
			// 메모리의 해당 인덱스의 값이 0이라면
			else
				codeIdx++;	// 다음 코드로 진행
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

	// 명령어를 5천만번이하로 실행 시 프로그램 종료
	if (time <= 50000000)
		cout << "Terminates\n";
	// 명령어를 5천만번 이상 실행하게 되면 무한 루프
	else
	{
		// loopStart를 찾는다.
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

			// ch 가 0이 되면 해당 쌍을 찾음
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
