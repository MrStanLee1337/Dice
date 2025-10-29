#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <random>
#include <string>
using namespace std;

//mt19937 rnd(static_cast<unsigned int> (time(nullptr)));
mt19937 rnd(1);
struct Term {
	int count, max, add;//count d max + add
};

void print(Term term) {
	cout << term.count << '\n';
	cout << term.max << '\n';
	cout << term.add << '\n';
}
bool isDigit(char c) {
	return '0' <= c && c <= '9';
}

Term parse(const string& str) {
	Term term;
	int number = 0;
	bool isAnyAdd = false;
	bool isAddNegative = false;
	for (size_t i = 0; i < size(str); i++) {
		char c = str[i];
		if (c == 'd') {
			term.count = number ? number : 1;
			number = 0;
			continue;
		}
		if (c == '+' || c == '-') {
			isAnyAdd = true;
			if (c == '-') isAddNegative = true;
			term.max = number;
			number = 0;
			continue;
		}
		if (isDigit(c)) number = number * 10 + c - '0';
	}
	!isAnyAdd ? term.max = number, term.add = 0 : term.add = number * (isAddNegative ? -1 : 1);
	return term;

}

int getNumber(Term& term) {
	int number = 0;
	for (int i = 0; i < term.count; i++) {
		number += rnd() % term.max + 1;
	}
	return number;
}
/*
int dice(const string& str) {
	Term term = parse(str);
	return getNumber(term);

}*/

void printFunc(vector<int>& vec, int scaleDivision, int add) {
	int sum = 0, mx = 0, mn = 1e9, sz = size(vec);
	for (int i = 0; i < sz; i++) {
		if (vec[i] == 0) continue;
		sum += vec[i];
		mx = max(mx, vec[i]);
		mn = min(mn, vec[i]);
	}
	//vector<vector<char>> grid(sz, vector<char>(mx / scaleDivision));

	cout << "MaxValue is: " << mx + add << '\n';
	cout << "MinValue is: " << mn + add << '\n';
	cout << "Scale Division is: " << scaleDivision << '\n';
	cout << '\n';
	for (int j = mx + scaleDivision; j >= mn - scaleDivision ; j-=scaleDivision) {
		for (int i = 0; i < sz; i++) {
			if (vec[i] < j) cout << '*'; else cout << '@';
			
		}
		cout << '\n';
	}


}

void input() {
	cout << "Input Dice:\n";
	string str;
	getline(cin, str);

	Term term = parse(str);
	vector<int> vec(term.count * (term.max + 1), 0);

	cout << "Input n:\n";
	int n;
	cin >> n;

	cout << "Input scale division:\n";
	int scaleDiv;
	cin >> scaleDiv;

	for (int i = 0; i < n; i++) {
		++vec[getNumber(term)];
	}
	printFunc(vec, scaleDiv, term.add);
	cout << "Print values(y/n)?\n";
	char c;
	cin >> c;
	if (c == 'y') {
		cout << "Values:\n";
		for (int i = 1; i < size(vec); i++) if(vec[i]) cout << i << '|' << vec[i] + term.add << '\n';
	}
	getchar();
	cout << '\n';
}

int main() { 
	while (1) input();
	
	/*
	vector<int> vec(21, 0);
	for (int i = 0; i < 1000000; i++) {
		++vec[dice("1d20")];
	}
	printFunc(vec, 100);
	cout << "Values:\n";
	for (auto& x : vec) cout << x << '\n';
	*/
	return 0;
}

template<typename... Args>
void print(Args&&... args) {
	(std::cout << ... << std::forward<Args>(args)) << std::endl;
}