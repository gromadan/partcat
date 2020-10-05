#include <iostream>
#include "word.h"
#include "string.h"

using namespace std;

const Word Word::identity=Word("aa");
const Word Word::cross=Word("abab");
const Word Word::single=Word("a");
const Word Word::four=Word("aaaa");
const Word Word::zhe=Word("abcabc");
const Word Word::couple=Word("ab");
const Word Word::abcb=Word("abcb");

Word Word::h(int n) {
	char ww[2*n+1];
	for(int i=0;i<2*n;i+=2) {
		ww[i]=1;
		ww[i+1]=2;
	}
	ww[2*n]=0;
	return Word(ww,2*n);
}

Word Word::pi(int n) {
	char ww[4*n+1];
	for(int i=0;i<n;i++) {
		ww[i]=i+1;
		ww[2*n+i]=i+1;
		ww[2*n-i-1]=i+1;
		ww[4*n-i-1]=i+1;
	}
	ww[4*n]=0;
	return Word(ww,4*n);
}


Word::Word(const char *ww, int ll)
{
	if (ww==nullptr){
		w=nullptr;
		l=0;
		return;
	}
	l=ll;
	w=new char[l+1];
	for(int i=0;i<l;i++) w[i]=ww[i];
	w[l]=0;
	//normalize();
}

Word::Word(const char *ww)
{
	if (ww==nullptr){
		w=nullptr;
		l=0;
		return;
	}
	l=strlen(ww);
	w=new char[l+1];
	for(int i=0;i<l+1;i++) w[i]=ww[i];
	normalize();
}

Word::Word(const Word &p)
 : l(p.l)
{
	if (p.w==nullptr) {
		w=nullptr;
		return;
	}
	w=new char[l+1];
	for(int i=0;i<l+1;i++) w[i]=p.w[i];
	//normalize();
}

Word Word::operator=(Word p) {
	delete[] w;
	l=p.l;
	if (p.w==nullptr) {
		w=nullptr;
		return *this;
	}
	w=new char[l+1];
	for(int i=0;i<l+1;i++) w[i]=p.w[i];
	return *this;
}


void Word::print() const{
	if (w==nullptr) {
		cout << "NULL";
		return;
	}
	for(int i=0;i<l;i++) cout << (char)('a'-1+w[i]);
}

void Word::normalize(){
	if (w==nullptr) return;
	char *ww=new char[l+1];
	int let=1;
	for(int i=0;i<l+1;++i) ww[i]=0;
	for(int i=0;i<l;++i) {
		if (ww[i]==0) {
			for(int j=i;j<l;j++) if (w[j]==w[i]) ww[j]=let;
			++let;
		}
	}
	char* word=w;
	w=ww;
	delete[] word;
}

bool Word::operator==(Word &rhs){
	if (w==nullptr || rhs.w==nullptr) return false;
	if (l!=rhs.l) return false;
	for(int i=0;i<l;i++) if (w[i]!=rhs.w[i]) return false;
	return true;
}

bool Word::operator!=(Word &rhs){
	return !(*this==rhs);
}

bool Word::operator<(Word &q){
	if (w==nullptr || q.w==nullptr) return false;
	if (l<q.l) return true;
	if (l>q.l) return false;
	for(int i=0;i<l;i++) {
		if (w[i]<q.w[i]) return true;
		if (w[i]>q.w[i]) return false;
	}
	return false;
}

bool Word::operator<=(Word &q){
	if (w==nullptr || q.w==nullptr) return false;
	if (l<q.l) return true;
	if (l>q.l) return false;
	for(int i=0;i<l;i++) {
		if (w[i]<q.w[i]) return true;
		if (w[i]>q.w[i]) return false;
	}
	return true;
}

bool Word::operator>(Word &q){
	return !(*this<=q);
}

bool Word::operator>=(Word &q){
	return !(*this<q);
}

bool Word::isNonCross() const {
	int bmax=l;
	for (int b1=1;b1<bmax;++b1) {
		for (int b2=b1+1;b2<bmax;++b2) {
			int i=0;
			while (i<l && w[i]!=b1) ++i;
			while (i<l && w[i]!=b2) ++i;
			if (i==l) bmax=b2;
			while (i<l && w[i]!=b1) ++i;
			if (i==l) break;
			while (i<l && w[i]!=b2) ++i;
			if (i!=l) return false;
		}
	}
	return true;
}


bool Word::isPair() const{
	for (int let=1;;++let) {
		int n=0;
		for (int i=0;i<l;++i)
			if (w[i]==let) ++n;
		if ((n==1) || (n>2)) return false;
		if (n==0) return true;
	}
}


Word Word::comp(int n) const {
	if (n<0||n>=l) n=n%l;
	char ww[l-1];
	if (n==0) {
		for(int i=0;i<l-2;i++) {
			if (w[i+1]==w[0]) ww[i]=w[l-1];
			else ww[i]=w[i+1];
		}
	} else {
		for (int i=0;i<n-1;i++) {
			if (w[i]==w[n]) ww[i]=w[n-1];
			else ww[i]=w[i];
		}
		for (int i=n+1;i<l;i++) {
			if (w[i]==w[n]) ww[i-2]=w[n-1];
			else ww[i-2]=w[i];
		}
	}
	ww[l-2]=0;
	Word ret(ww,l-2);
	ret.normalize();
	return ret;
}
	

Word Word::rot(int n) const {
	char ww[l+1];
	char let=1;
	if (n<0) n=n%l+l;
	if (n>=l) n=n%l;
	for(int i=0;i<l+1;++i) ww[i]=0;
	for(int i=0;i<l;++i) {
		if (ww[i]==0) {
			int i2=i+n;
			int j=i;
			int j2;
			if (i2<l) {
				for(j2=i2;j2<l;j++,j2++) if (w[j2]==w[i2]) ww[j]=let;
				for(j2=0;j<l;j++,j2++) if (w[j2]==w[i2]) ww[j]=let;
			}
			else {
				i2-=l;
				for(j2=i2;j<l;j++,j2++) if (w[j2]==w[i2]) ww[j]=let;
			}
			++let;
		}
	}
	return Word(ww,l);
}

Word Word::conj() const{
	if (w==nullptr) return Word(nullptr);
	char ww[l+1];
	char let=1;
	for(int i=0;i<l+1;++i) ww[i]=0;
	for(int i=0;i<l;++i) {
		if (ww[i]==0) {
			int i2=l-i-1;
			for(int j=i,j2=i2;j<l;++j,--j2) if (w[j2]==w[i2]) ww[j]=let;
			++let;
		}
	}
	return Word(ww,l);
}

Word Word::operator+(const Word &q) const{
	if (w==nullptr || q.w==nullptr) return Word(nullptr);
	char ww[l+q.l+1];
	char s=0;
	for(int i=0;i<l;i++) if ((ww[i]=w[i])>s) s=w[i];
	for(int i=0;i<q.l;i++) ww[i+l]=q.w[i]+s;
	ww[l+q.l]=0;
	/*this->print();
	cout << "+";
	q.print();
	cout << "=";
	Word(ww,l+q.l).print();
	cout << endl;*/
	return Word(ww,l+q.l);
}

bool Word::compatible(int *a, int s, int k) const{
	if (w==nullptr) return false;
	if (l-s<k) cout << "Unexpected error";
	for(int i=0;i<k;i++) {
		for(int j=i+1;j<k;j++) {
			if ((w[i+s]==w[j+s])&&(a[i]!=a[j])) return false;
		}
	}
	return true;
}

int Word::intrep() const {
	char ww[l+1];
	for (int i=0;i<l;i++) ww[i]=1;
	ww[l]=0;
	int n=1;
	for (int i=0;i<l;i++) {
		while (ww[i]!=w[i]) {
			iterate(ww,l);
			++n;
		}
	}
	return n;
}

int Word::iterate(char* w, int s) {
	if (s<=1) return 0;
	for (int i=0;i<s-1;i++) {
		if (w[i]>=w[s-1]) {
			w[s-1]++;
			return 1;
		}
	}
	w[s-1]=1;
	return iterate(w,s-1);
}

int Word::iterate2(int *a,int n, int k) {
	if (k<=0) return 0;
	if (a[k-1]<n) {
		++a[k-1];
		return 1;
	}
	a[k-1]=1;
	return iterate2(a,n,k-1);
}

void Word::printrel(int k, int n) const{
	if (w==nullptr) return;
	int ab[l];
	int cd[l];
	for (int i=0;i<l;i++) ab[i]=1;
	for (int i=0;i<l;i++) cd[i]=1;
	do {
		bool ccomp=compatible(cd,0,k);
		do {
			bool bcomp=compatible(ab+k,k,l-k);
			if ((!bcomp)&&(!ccomp)) continue;
			if (!compatible(ab+k,k,l-k))  cout << "0";
			else if (k==0) cout << "1";
			else {
				cout << "0";
				for (int i=0;i<k;i++) ab[i]=1;
				do {
					if (compatible(ab,0,l)) {
						cout << "+";
						if (k>0) cout << "u(" << ab[k-1] << ")(" << cd[k-1] << ")";
						for(int i=k-2;i>=0;i--) cout << "*u(" << ab[i] << ")(" << cd[i] << ")";
					}
				} while (iterate2(ab,n,k));
			}
			//cout << "=";
			if (!ccomp) ;// cout << "0";
			else if (k==l) cout << "-1";
			else {
				for (int i=k;i<l;i++) cd[i]=1;
				do {
					if (compatible(cd,0,l)) {
						cout << "-";
						if (k<l) cout << "u(" << ab[k] << ")(" << cd[k] << ")";
						for(int i=k+1;i<l;i++) cout << "*u(" << ab[i] << ")(" << cd[i] << ")";
					}
				} while (iterate2(cd+k,n,l-k));
			}
		cout << "," <<endl;
		} while (iterate2(ab+k,n,l-k));
	} while (iterate2(cd,n,k));
}

int Word::alpha(int n) const {
	if (n<0||n>=l) n=n%l;
	if (n==0) {
		for(int i=1;i<l-1;i++)
			if (w[i]==w[0] || w[i]==w[l-1]) return 0;
	} else { 
		for (int i=0;i<n-1;i++) 
			if (w[i]==w[n] || w[i]==w[n-1]) return 0;
		for (int i=n+1;i<l;i++)
			if (w[i]==w[n] || w[i]==w[n-1]) return 0;
	}
	return 1;
}
