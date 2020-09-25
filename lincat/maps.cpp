#include <iostream>
#include "../words/word.h"

using namespace std;

int main() {
	int lmax=9;
	cout << "module M;\n";
	cout << "list cont;\n";
	for (int l=3;l<=lmax;++l) {
		char ww[l+1];
		for (int i=0;i<l;i++) ww[i]=1;
		ww[l]=0;
		cout << "M=\n";
		if (Word(ww,l).alpha(0)) cout << "n*";
		cout << "gen(" << Word(ww,l).comp(0).intrep() << ")\n";
		while (Word::iterate(ww,l)){
			cout << ",";
			if (Word(ww,l).alpha(0)) cout << "n*";
			cout << "gen(" << Word(ww,l).comp(0).intrep() << ")\n";
		}
		cout <<";\n";
		cout << "cont[" << l << "]=M;\n";
	}
	cout << "list rot;\n";
	for (int l=2;l<=lmax;++l) {
		char ww[l+1];
		for (int i=0;i<l;i++) ww[i]=1;
		ww[l]=0;
		cout << "M=\n";
		cout << "gen(" << Word(ww,l).rot(1).intrep()<< ")\n";
		while (Word::iterate(ww,l)) cout << ",gen(" << Word(ww,l).rot(1).intrep()<< ")\n";
		cout << ";\n";
		cout << "rot[" << l << "]=M;\n";
	}
	cout << "list conj;\n";
	for (int l=1;l<=lmax;++l) {
		char ww[l+1];
		for (int i=0;i<l;i++) ww[i]=1;
		ww[l]=0;
		cout << "M=\n";
		cout << "gen(" << Word(ww,l).conj().intrep()<< ")\n";
		while (Word::iterate(ww,l)) cout << ",gen(" << Word(ww,l).rot(1).intrep()<< ")\n";
		cout << ";\n";
		cout << "conj[" << l << "]=M;\n";
	}
	cout << "list cat;\n";
	for (int l=1;l<=lmax;++l) {
		cout << "list L;\n";
		for (int l2=l;l2<=lmax-l;++l2) {
			char ww[l+1];
			char ww2[l2+1];
			for (int i=0;i<l;i++) ww[i]=1;
			for (int i=0;i<l2;i++) ww2[i]=1;
			ww[l]=0;
			ww2[l2]=0;
			cout << "M=\n";
			cout << "gen(" << (Word(ww,l)+Word(ww2,l2)).intrep() << ")\n";
			while (Word::iterate(ww2,l2))
				cout << ",gen(" << (Word(ww,l)+Word(ww2,l2)).intrep() << ")\n";
			while (Word::iterate(ww,l)) {
				for (int i=0;i<l2;i++) ww2[i]=1;
				do cout << ",gen(" << (Word(ww,l)+Word(ww2,l2)).intrep() << ")\n";
				while (Word::iterate(ww2,l2));
			}
			cout << ";\n";
			cout << "L[" << l2 << "]=M;\n";
		}
		cout << "cat[" << l << "]=L;\n";

	}
}
 	
