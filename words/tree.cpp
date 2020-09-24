#include <iostream>
#include <stack>
#include "word.h"
#include "tree.h"
#include <vector>

using namespace std;

Tree::Tree(const Tree &t):root(t.root), N(t.N){
}

Tree Tree::operator=(const Tree &t){
	root=t.root;
	N=t.N;
	return *this;
}

bool Tree::equalTrees(const Vertex &r, const Vertex &s){
	if (r.contains!=s.contains) return false;
	if ((r.NChildren!=s.NChildren)) {
		std::cout<< "Unexpected error" <<std::endl;
		return false;
	}
	if (r.child!=nullptr && s.child!=nullptr) for (int i=0;i<r.NChildren;i++) if (!equalTrees(r.child[i],s.child[i])) return false;
	return true;
}

bool Tree::operator==(const Tree &t) const{
	return equalTrees(this->root,t.root);
}

void Tree::print(){
	vector<Word> l[32];
	getList(l);
	for (int i=0;i<31;i++)
		for (vector<Word>::iterator it=l[i].begin();it!=l[i].end();it++){
			it->print();
			cout<<endl;
		}
}

void Tree::printrels(int n, int d){
	vector<Word> l[32];
	getList(l);
	cout << "LIB \"freegb.lib\";" << endl;
	cout << "ring r = 0,(u(1.."<< n << ")(1.." << n << ")),dp;" << endl;
	cout << "def R = makeLetterplaceRing("<<(d/2+1)<<"); setring R;" << endl;
	cout << "ideal I=" << endl;
	Word::identity.printrel(0,n);
	Word::identity.printrel(2,n);
	for (int i=0;i<d;i++)
		for (vector<Word>::iterator it=l[i].begin();it!=l[i].end();it++){
			it->printrel((i+1)/2,n);
		}
	cout << "0;";
}

bool Tree::contains(const Word &w) const{
	if (w.isNull()) return false;
	if (w.getl()==0) return true;
	return contains(w.getw(),root);
}

bool Tree::contains(const char *key,const Vertex &r){
	if (key[1]==0) return (r.contains>>key[0])&1;
	if (r.child==nullptr) return false;
	return contains(key+1,r.child[key[0]-1]);
}

int Tree::add(const Word &w){
	if (w.isNull()) return 0;
	if (w.getl()==0) return 0;
	return add(w.getw(),root);
}

int Tree::add(const char *key, Vertex &r){
	if (key[1]==0) {
		r.contains|=1<<key[0];
		N++;
		//cout << "adding "; w.print(); cout<<endl;
		return 1;
	}
	if (r.child==nullptr) {
		r.child=new Vertex[r.NChildren];
		for(int i=0;i<r.NChildren-1;i++) 
			r.child[i].NChildren=r.NChildren;
		r.child[r.NChildren-1].NChildren=r.NChildren+1;
	}
	return add(key+1,r.child[key[0]-1]);
}

void Tree::getList(vector<Word> *l,Vertex &r, char *key, int d) {
	for (int c=r.contains,i=0;c!=0;c>>=1,++i) if (c&1) {
		key[d]=i;
		l[d].push_back(Word(key,d+1));
	}
	if (r.child!=nullptr)
		for (int i=0;i<r.NChildren;i++) {
			key[d]=i+1;
			key[d+1]=0;
			getList(l,r.child[i],key,d+1);
		}
}

void Tree::getCharSeq(int *l,Vertex &r, int d) {
	for (int c=r.contains;c!=0;c>>=1) if (c&1) ++l[d];
	if (r.child!=nullptr) for (int i=0;i<r.NChildren;i++) getCharSeq(l,r.child[i],d+1);
}
