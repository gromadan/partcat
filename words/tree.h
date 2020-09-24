#ifndef TREE_H
#define TREE_H

#include "vertex.h"
#include <vector>

using namespace std;

class Tree{
	Vertex root;
	//static Vertex makeTree(const Vertex &root);
	static bool equalTrees(const Vertex &r, const Vertex &s);
	int add(const char *key, Vertex &r);
	static bool contains(const char *key,const Vertex &r);
	static void getList(vector<Word> *l,Vertex &r, char *key, int d);
	static void getCharSeq(int *l,Vertex &r, int d);
	int N;
public:
	Tree():N(0) {root.NChildren=1;}
	Tree(const Tree &t);
	Tree operator=(const Tree &t);
	bool operator==(const Tree &t) const;
	bool operator!=(const Tree &t) const {return !(*this==t);}
	bool contains(const Word &w) const;
	void print();
	void printrels(int n, int d);
	int add(const Word &w); //returns 1 if its new, 0 otherwise
	void getList(vector<Word> *l){char key[32]; for (int i=0;i<32;i++) key[i]=0; getList(l,root,key,0);}
	void getCharSeq(int *l){getCharSeq(l,root,0);}
	int getN() {return N;}
};

#endif


