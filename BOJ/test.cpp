#include <iostream>
using namespace std;

struct A {
	int map[10][10];

	void print() {
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				cout << map[y][x] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	void init(int val) {
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				map[y][x] = val;
			}
		}
	}

};
int main() {

	A a;
	a.init(5);

	a.print();
	A b = a;
	b.print();

	return 0;
}