#include <iostream>
#include <cstring>
using namespace std;

char inF[101]; // 입력 첫 번째
char inS[101]; // 입력 두 번째

char frontF[101]; // 입력 첫 번째 소수점 앞
char frontS[101]; // 입력 두 번째 소수점 앞

char backF[101]; // 입력 첫 번째 소수점 뒤
char backS[101]; // 입력 두 번째 소수점 뒤

int outF[101]; // 결과 소수점 앞
int outB[101]; // 결과 소수점 뒤

int main()
{
	cin.getline(inF, 100);
	cin.getline(inS, 100);

	int lenF = strlen(inF),
		lenS = strlen(inS);

	int dotF = 0, // 입력 첫 번째의 소수점 위치
		dotS = 0; // 입력 두 번째의 소수점 위치

				  // 소수점이 나올 때까지 넣기
	for (int i = 0; i < lenF; ++i) {
		if (inF[i] == '.') {
			dotF = i;
			break;
		}
		frontF[i] = inF[i];
	}

	for (int i = 0; i < lenS; ++i) {
		if (inS[i] == '.') {
			dotS = i;
			break;
		}
		frontS[i] = inS[i];
	}

	// 소수점이 있다면
	if (dotF != 0) {
		for (int i = dotF + 1; i < lenF; ++i) {
			backF[i - (dotF + 1)] = inF[i];
		}
	}

	if (dotS != 0) {
		for (int i = dotS + 1; i < lenS; ++i) {
			backS[i - (dotS + 1)] = inS[i];
		}
	}

	int lenF_front = strlen(frontF),
		lenS_front = strlen(frontS);

	int lenF_back = strlen(backF),
		lenS_back = strlen(backS);

	int big_front = 0,
		big_back = 0;

	// 111
	//   0.1
	if (lenF_back == 0 && lenS_back != 0) {
		big_back = lenS_back;
		for (int i = 0; i < lenS_back; ++i) {
			outB[i] = backS[i] - '0';
		}
	}
	//   0.1
	// 111
	else if (lenF_back != 0 && lenS_back == 0) {
		big_back = lenF_back;
		for (int i = 0; i < lenF_back; ++i) {
			outB[i] = backF[i] - '0';
		}
	}
	// 0.123
	// 0.12
	else if (lenF_back != 0 && lenS_back != 0) {
		big_back = (lenF_back >= lenS_back ? lenF_back : lenS_back);
		// 소수점 뒤쪽 0으로 채우기
		for (int i = 0; i < big_back; ++i) {
			if (backF[i] == NULL) backF[i] = '0';
			if (backS[i] == NULL) backS[i] = '0';
		}
	}

	big_front = (lenF_front >= lenS_front ? lenF_front : lenS_front);

	// 앞자리 덧셈
	int value = 0,
		each = 0,
		plus = 0;
	for (int i = 0; i < big_front; ++i) {
		if (lenS_front - 1 - i < 0) value = frontF[lenF_front - 1 - i] - '0';
		else if (lenF_front - 1 - i < 0) value = frontS[lenS_front - 1 - i] - '0';
		else value = (frontF[lenF_front - 1 - i] - '0') + (frontS[lenS_front - 1 - i] - '0');

		each = (value + plus) % 10;
		plus = (value + plus) / 10;
		outF[i] = each;
	}

	if (plus != 0) {
		outF[big_front] = plus;
		big_front++;
	}

	// 뒷자리 덧셈
	value = each = plus = 0;
	if (backF[0] != NULL && backS[0] != NULL) {
		for (int i = 0; i < big_back; ++i) {
			if (big_back - 1 - i < 0) value = backF[big_back - 1 - i] - '0';
			else if (big_back - 1 - i < 0) value = backS[big_back - 1 - i] - '0';
			else value = (backF[big_back - 1 - i] - '0') + (backS[big_back - 1 - i] - '0');

			each = (value + plus) % 10;
			plus = (value + plus) / 10;
			outB[i] = each;
		}
	}


	if (plus != 0) {
		for (int i = 0; i < big_front; ++i) {
			each = (outF[i] + plus) % 10;
			plus = (outF[i] + plus) / 10;
			outF[i] = each;
		}
	}

	if (plus != 0) {
		outF[big_front] = plus;
		big_front++;
	}

	for (int i = big_front - 1; i >= 0; --i) {
		cout << outF[i];
	}
	if (dotF != 0 || dotS != 0) {
		bool flag = false;
		for (int i = 0; i < big_back; ++i) {
			if (outB[i] != 0) {
				flag = true;
				break;
			}
		}

		if (!flag) return 0;

		cout << '.';
		for (int i = big_back - 1; i >= 0; --i) {
			cout << outB[i];
		}
	}

	return 0;
}