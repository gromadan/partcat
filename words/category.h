#ifndef CATEGORY_H
#define CATEGORY_H

#include "tree.h"
#include "word.h"
#include <vector>
#include <queue>
#include <iostream>

class Category{
	std::vector<Word> gen;
	std::vector<Word> rep;
	std::queue<Word> *news;
	Tree t;
	int depth,Nmax;
	int N; //Number of classes of words
public:
	Category(const std::vector<Word> g,int d, int Nm);
	~Category() {delete news;}
	Category(const Category &c):gen(c.gen), rep(c.rep), news(new std::queue<Word>(*c.news)), t(c.t), depth(c.depth), Nmax(c.Nmax), N(c.N){};
	Category(const Category &c1,const Category &c2, int d, int Nm);
	Category operator=(const Category &c) {delete news;gen=c.gen;rep=c.rep;news=new std::queue<Word>(*c.news); t=c.t;depth=c.depth; Nmax=c.Nmax; N=c.N;return *this;}
	int add(const Word &w);
	int addProds();
	void addAll() {while(N<Nmax && addProds());}
	void regenerate(int d, int N);
	bool operator<(const Category &c) const;
	bool operator==(const Category &c) const {return (*this<c && c<*this);}
	Category operator+(Category c) {return Category(*this,c,depth,Nmax);}
	void print(){t.print();std::cout << "N(words)=" << t.getN() << ", N(classes)=" << N << std::endl;}
	//void printrels(int n,int d){t.printrels(n,d);}
	void printrels(int n, int d);
	void printCharSeq();
	bool contains(const Word &p) {return t.contains(p);}
	void printGens();
	bool isFree() {return (*this<Category({Word::single,Word::four},depth,Nmax));}    //true=definitely is free, false=probably not free
	bool isGroup() {return t.contains(Word::cross);} //true=definitely group, false=probably not group
	bool isHalfLib() {return (!t.contains(Word::cross)&&t.contains(Word::zhe));} //true=probably half-liberated, false=probably not half-liberated
	bool isHyperOctahedr() {return (t.contains(Word::four)&&!t.contains(Word::couple));} //true=probably is hyperoctahedral, false=probably not
	int classify();
	//static Category NC;
	int getN() {return N;}
	int gettN() {return t.getN();}
	int getgN() {return gen.size();}
};

#endif

