#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <random>
using namespace std;

mt19937 rnd(static_cast<unsigned int> (time(nullptr)));

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
			term.count = number;
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

int dice(const string& str) {
	Term term = parse(str);
	//print(term);
	return -1;

}
int main() { 
	int d = dice("214d52-16");
	return 0;
}