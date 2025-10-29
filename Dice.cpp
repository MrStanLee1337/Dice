#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <random>
#include <string>
#include <iomanip>
using namespace std;

//mt19937 rnd(static_cast<unsigned int> (time(nullptr)));
mt19937 rnd(1);

struct Term {
	int count, max, add;//count d max + add
};

void print(Term term);

bool isDigit(char c) {
	return '0' <= c && c <= '9';
}

Term getTermFromString(const string& str);

int getNumberFromTerm(const Term& term);


void printFunc(vector<int>& vec, int scaleDivision, int add);

int input(const string& str);

void play();


int main() { 
	while (true) play();
	return 0;
}

void print(Term term) {
	cout << term.count << '\n';
	cout << term.max << '\n';
	cout << term.add << '\n';
}

Term getTermFromString(const string& str) {
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

int getNumberFromTerm(const Term& term) {// excluding
	int number = 0;
	for (int i = 0; i < term.count; i++) {
		number += rnd() % term.max + 1;
	}
	return number + term.add;
}

void printFunc(vector<int>& vec, int scaleDivision, int add, int setwidth) {
	int sum = 0, mx = 0, mn = 1e9, sz = size(vec);
	for (int i = 0; i < sz; i++) {
		if (vec[i] == 0) continue;
		sum += vec[i];
		mx = max(mx, vec[i]);
		mn = min(mn, vec[i]);
	}

	cout << "MaxValue is: " << mx + add << '\n';
	cout << "MinValue(except 0) is: " << mn + add << '\n';
	cout << "Scale Division is: " << scaleDivision << '\n';
	cout << '\n';
	for (int j = mx + 1; j >= mn; j -= scaleDivision) {
		cout << setw(setwidth) << j;
		for (int i = 0; i < sz; i++) {
			cout << setw(setwidth);
			if (vec[i] < j) cout << ' '; else cout << '*';
		}
		cout << '\n';
	}
	cout << setw(setwidth) << ' ';
	for (int i = 0; i < sz; i++) cout << setw(setwidth) << i + add;
	cout << '\n';

}

int input(const string& str) {
	cout << str;
	int val;
	cin >> val;
	return val;
}

void play() {
	cout << "Input Dice:\n";
	string str;
	getline(cin, str);

	Term term = getTermFromString(str);
	vector<int> vec(term.max * term.count + 1, 0);

	int n = input("Input n:\n");
	int scaleDiv = input("Input scale division:\n");

	for (int i = 0; i < n; i++) {
		++vec[getNumberFromTerm(term) - term.add];
	}

	printFunc(vec, scaleDiv, term.add, 3);
	int c = input("Print values (press 1)?\nNext dice(press 2)?\n");
	cout << c;
	if (c == 1) {
		cout << "Values:\n";
		for (int i = 0; i < size(vec); i++) cout << std::setw(2) << i + term.add << '|' << vec[i]  << '\n';
	}
	getchar();
	cout << '\n';
}

template<typename... Args>
void print(Args&&... args) {
	(std::cout << ... << std::forward<Args>(args)) << std::endl;
}