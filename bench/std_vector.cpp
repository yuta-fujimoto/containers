#include "timer.hpp"
#include <vector>

#define REPEAT 500

int main()
{
	int a;
	std::vector<int> v;
	std::vector<int>::iterator it;
	std::vector<int>::reverse_iterator rit;
	std::vector<int>::size_type s;
	std::vector<int>::reference r = a;
	bool b;
	timer t;

	t.start();
	for (int i = 0; i < REPEAT; ++i) {
		it = v.begin();
	}
	t.record("BEGIN");
	for (int i = 0; i < REPEAT; ++i) {
		it = v.end();
	}
	t.record("END");
	for (int i = 0; i < REPEAT; ++i) {
		rit = v.rbegin();
	}
	t.record("RBEGIN");
	for (int i = 0; i < REPEAT; ++i) {
		rit = v.rend();
	}
	t.record("REND");

	for (int i = 0; i < REPEAT; ++i) {
		s = v.size();
	}
	t.record("SIZE");
	for (int i = 0; i < REPEAT; ++i) {
		s = v.max_size();
	}
	t.record("MAX_SIZE");
	for (int i = 0; i < REPEAT / 2; ++i) {
		v.resize(i);
	}
	for (int i = REPEAT / 2 - 1; i >= 0; --i) {
		v.resize(i);
	}
	t.record("RESIZE");

	for (int i = 0; i < REPEAT; ++i) {
		s = v.capacity();
	}
	t.record("CAPACITY");

	for (int i = 0; i < REPEAT; ++i) {
		b = v.empty();
	}
	t.record("EMPTY");

	for (int i = 0; i < REPEAT / 2; ++i) {
		v.resize(i);
	}
	for (int i = REPEAT / 2 - 1; i >= 0; --i) {
		v.resize(i);
	}
	t.record("RESERVE");

	v.push_back(1);
	t.start();
	for (int i = 0; i < REPEAT; ++i) {
		v[0];
	}
	t.record("[]");

	for (int i = 0; i < REPEAT; ++i) {
		r = v.front();
	}
	t.record("front");

	for (int i = 0; i < REPEAT; ++i) {
		r = v.back();
	}
	t.record("back");

	std::vector<int> temp;
	temp.push_back(1);
	temp.push_back(2);

	t.start(); 
	for (int i = 0; i < REPEAT; ++i) {
		v.assign(temp.begin(), temp.end());
	}
	t.record("ASSIGN-1");

	for (int i = 0; i < REPEAT; ++i) {
		v.assign(i, i);
	}
	t.record("ASSIGN-2");

	for (int i = 0; i < REPEAT; ++i) {
		v.push_back(i);
	}
	t.record("PUSH_BACK");

	for (int i = 0; i < REPEAT; ++i) {
		v.pop_back();
	}
	t.record("POP_BACK");

	for (int i = 0; i< REPEAT; ++i) {
		v.insert(v.end(), i);
	}
	t.record("INSERT-1");

	for (int i = 0; i< REPEAT; ++i) {
		v.insert(v.end(), 5, i);
	}
	t.record("INSERT-2");
	for (int i = 0; i< REPEAT; ++i) {
		v.insert(v.end(), temp.begin(), temp.end());
	}
	t.record("INSERT-3");

	for (int i = 0; i< REPEAT; ++i) {
		v.erase(v.end() - 1);
	}
	t.record("ERASE-1");
	for (int i = 0; i< REPEAT; ++i) {
		v.erase(v.end() - 1, v.end());
	}
	t.record("ERASE-2");

	for (int i = 0; i< REPEAT; ++i) {
		v.swap(temp);
	}
	t.record("SWAP");
	for (int i = 0; i< 1; ++i) {
		v.clear();
	}
	t.record("CLEAR");
}
