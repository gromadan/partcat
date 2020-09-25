#include <iostream>
#include "../words/word.h"

using namespace std;

int main() {
	int l=8;
	char ww[l+1];
	for (int i=0;i<l;i++) ww[i]=1;
	ww[l]=0;
	Word p=Word(nullptr,0);
	do {
		Word(ww,l).print();
		cout << endl;
	}
	while (Word::iterate(ww,l));
}

