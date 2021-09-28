#include<iostream>
#include<cstdlib>
#include<clocale>
#include<string>
#include "tbitfield.h"
using namespace std;



int main() {
	setlocale(LC_ALL, "Russian");
	TBitField a(10);
	cout << a;



	return 0;
}
