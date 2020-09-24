#include <iostream>
#include "part.h"

using namespace std;

int idw[2]={1,1};
int pairw[2]={1,1};
int crossw[4]={1,2,1,2};
int singlew[1]={1};
int fourw[4]={1,1,1,1};
int zhew[6]={1,2,3,1,2,3};
int couplew[2]={1,2};
int abcbw[4]={1,2,3,2};
const Partition Partition::identity=Partition(idw,1,1);
const Partition Partition::pair=Partition(pairw,0,2);
const Partition Partition::cross=Partition(crossw,2,2);
const Partition Partition::single=Partition(singlew,0,1);
const Partition Partition::four=Partition(fourw,0,4);
const Partition Partition::zhe=Partition(zhew,3,3);
const Partition Partition::couple=Partition(couplew,0,2);
const Partition Partition::abcb=Partition(abcbw,0,4);


Partition::Partition(int *ww,int kk,int ll)
 : k(kk), l(ll)
{
	if (ww==nullptr){
		w=nullptr;
		return;
	}
	w=new int[k+l];
	for(int i=0;i<k+l;i++) w[i]=ww[i];
	normalize();
}

Partition::Partition(const Partition &p)
 : k(p.k), l(p.l)
{
	if (p.w==nullptr) {
		w=nullptr;
		return;
	}
	w=new int[k+l];
	for(int i=0;i<k+l;i++) w[i]=p.w[i];
	//normalize();
}

void Partition::print() const{
	if (w==nullptr) {
		cout << "NULL";
		return;
	}
	for(int i=0;i<k;i++) cout << (char)('a'-1+w[i]);
	cout << "|";
	for(int i=k;i<k+l;i++) cout << (char)('a'-1+w[i]);
}

void Partition::normalize(){
	if (w==nullptr) return;
	int *ww=new int[k+l];
	int let=1;
	for(int i=0;i<k+l;i++) ww[i]=0;
	for(int i=0;i<k+l;i++) {
		if (ww[i]==0) {
			for(int j=i;j<k+l;j++) if (w[j]==w[i]) ww[j]=let;
			let++;
		}
	}
	int* word=w;
	w=ww;
	delete[] word;
}

bool Partition::operator==(Partition &rhs){
	if (w==nullptr || rhs.w==nullptr) return false;
	if (k!=rhs.k) return false;
	if (l!=rhs.l) return false;
	for(int i=0;i<k+l;i++) if (w[i]!=rhs.w[i]) return false;
	return true;
}

bool Partition::operator!=(Partition &rhs){
	return !(*this==rhs);
}

bool Partition::operator<(Partition &q){
	if (w==nullptr || q.w==nullptr) return false;
	if (k+l<q.k+q.l) return true;
	if (k+l>q.k+q.l) return false;
	if (k<q.k) return true;
	if (k>q.k) return false;
	for(int i=0;i<k+l;i++) {
		if (w[i]<q.w[i]) return true;
		if (w[i]>q.w[i]) return false;
	}
	return false;
}

bool Partition::operator<=(Partition &q){
	if (w==nullptr || q.w==nullptr) return false;
	if (k+l<q.k+q.l) return true;
	if (k+l>q.k+q.l) return false;
	if (k<q.k) return true;
	if (k>q.k) return false;
	for(int i=0;i<k+l;i++) {
		if (w[i]<q.w[i]) return true;
		if (w[i]>q.w[i]) return false;
	}
	return true;
}

bool Partition::operator>(Partition &q){
	return !(*this<=q);
}

bool Partition::operator>=(Partition &q){
	return !(*this<q);
}

Partition Partition::operator*(const Partition &q) const{
	if (w==nullptr || q.w==nullptr) return Partition(nullptr,0,0);
	if (l!=q.k) return Partition(nullptr,0,0);
	int kk=k;
	int ll=q.l;
	int word[kk+ll];
	int s=k+l;
	int ss=s+q.k+q.l+1;
	for(int i=0;i<kk;i++) word[i]=w[i];
	for(int i=0;i<ll;i++) word[kk+i]=s+q.w[q.k+i];
	int a[ss];
	int j=ss;
	for(int i=0;i<ss;i++) a[i]=0;
	for(int i=0;i<l;i++) {
		if (a[w[k+l-i-1]]==0) a[w[k+l-i-1]]=j++;
		if (a[s+q.w[i]]==0) a[s+q.w[i]]=a[w[k+l-i-1]];
		else if (a[s+q.w[i]]!=a[w[k+l-i-1]]) {
			int m=a[s+q.w[i]];
			for (int n=0;n<ss;n++) if (a[n]==m) a[n]=a[w[k+l-i-1]];
		}
	}
	for(int i=0;i<kk+ll;i++)
		word[i]=a[word[i]]?a[word[i]]:word[i];
	/*print();
	cout << "*";
	q.print();
	cout << "=";
	Partition(word,kk,ll).print();
	cout << endl;*/
	return Partition(word,kk,ll);
}

Partition Partition::conj() const{
	if (w==nullptr) return Partition(nullptr,0,0);
	int ww[k+l];
	for(int i=0;i<k+l;i++) ww[i]=w[k+l-i-1];
	return Partition(ww,l,k);
}

Partition Partition::operator+(const Partition &q) const{
	if (w==nullptr || q.w==nullptr) return Partition(nullptr,0,0);
	int kk=k+q.k;
	int ll=l+q.l;
	int ww[kk+ll];
	int s=q.k+q.l;
	for(int i=0;i<q.k;i++) ww[i]=q.w[i];
	for(int i=0;i<k+l;i++) ww[q.k+i]=w[i]+s;
	for(int i=0;i<q.l;i++) ww[kk+l+i]=q.w[q.k+i];
	/*print();
	cout << "+";
	q.print();
	cout << "=";
	Partition(ww,kk,ll).print();
	cout << endl;*/
	return Partition(ww,kk,ll);
}
