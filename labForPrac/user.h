#pragma once

#include <string>
#include <vector>

using  namespace std;

struct User {
	User();
	string FIO;
	string adress;
	string numberPhone[3];
	string balanceForPhone;
	template<typename T>
	string funcForConstructor(vector<T>& vec, T peremen);
	void PrintInfo();
};


