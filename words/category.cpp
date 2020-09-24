#include "tree.h"
#include "word.h"
#include "category.h"
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

//Category Category::NC=Category({Word::single,Word::four});

Category::Category(const std::vector<Word> g,int d, int Nm) : gen(g), depth (d), Nmax(Nm), N(0){
	news=new queue<Word>;
	add(Word::identity);
	for (vector<Word>::iterator it=gen.begin();it!=gen.end();++it) add(*it);
	addAll();
	//cout << "N(words)=" << t.getN() << ", N(classes)=" << N <<endl;
}

Category::Category(const Category &c1, const Category &c2, int d, int Nm) : depth(d), Nmax(Nm), N(0) {
	gen=c1.gen;
	gen.insert(gen.end(),c2.gen.begin(),c2.gen.end());
	news=new queue<Word>;
	for(std::vector<Word>::const_iterator it=c1.rep.begin();it!=c1.rep.end();++it) if (it->getl()<d) add(*it);
	for(std::vector<Word>::const_iterator it=c2.rep.begin();it!=c2.rep.end();++it) if (it->getl()<d) add(*it);
	addAll();
}

void Category::printGens() {
	cout << "<";
	std::vector<Word>::iterator it=gen.begin();
	if (it==gen.end()) {
		cout << ">";
		return;
	}
	it->print();
	++it;
	for (;it!=gen.end();++it) {
		cout<<", ";
		it->print();
	}
	cout << ">";
	return;
}

bool Category::operator<(const Category &c) const {
	for (vector<Word>::const_iterator it=gen.begin();it!=gen.end();++it) if (!c.t.contains(*it)) return false;
	return true;
}

int Category::add(const Word &w) {
	if (w.isNull()) return 0;
	if (t.contains(w)) return 0;
	//cout << "adding products of "; w.print();cout<<endl;
	if (w.getl()>2)
		for (int i=0;i<w.getl();i++)
			add(w.comp(i));
	news->push(w);
	rep.push_back(w);
	for (int i=0;i<w.getl();i++) {
		Word wr=w.rot(i);
		t.add(wr);
		t.add(wr.conj());
	}
	N++;
	return 1;
}

/*
int Category::addProds(){
	int cnt=0;
	queue<Word> *q=news;
	news=new queue<Word>;
	Word* l[t.getN()];
	t.getList(l);
	while (!q->empty()) {
		for (int i=0;i<t.getN();i++)
			cnt+=add(q->front()+(*l[i]));
		q->pop();
	}
	delete q;
	return cnt;
}
*/

int Category::addProds(){
	int cnt=0;
	queue<Word> *q=news;
	news=new queue<Word>;
	vector<Word> l[depth+1];
	t.getList(l);
	while (!q->empty()) {
		for (int i=0;i<depth-q->front().getl()-1;i++)
			for (vector<Word>::iterator it=l[i].begin();it!=l[i].end();it++)
				cnt+=add(q->front()+(*it));
		q->pop();
		if (N>Nmax) {
			delete q;
			return cnt;
		}
	}
	delete q;
	return cnt;
}

void Category::regenerate(int d, int Nm) {
	depth=d;
	Nmax=Nm;
	delete news;
	news=new queue<Word>;
	for(vector<Word>::iterator it=rep.begin();it!=rep.end();it++) news->push(*it);
	addAll();
}

void Category::printCharSeq() {
	int l[depth];
	for (int i=0;i<depth;i++) l[i]=0;
	t.getCharSeq(l);
	for (int i=0;i<depth;i++) cout << l[i] << ", ";
	cout << endl;
}

int Category::classify() {
	cout << "-----------------------\n";
	cout << "C=";
	printGens();
	cout << endl;
	if (isHyperOctahedr()) {
		if (!contains(Word("aabaab"))) {
			if (contains(Word::four) && *this<Category({Word::four},depth,Nmax)) {
				cout << "C=<┌┬┬┐>. It is free and hyperoctahedral.\n";
				return 1;
			}
			for (int i=2;i<depth/4;i++) {
				if (contains(Word::pi(i)) && *this<Category({Word::pi(i)},depth,Nmax)) {
					cout << "C=<π" << i << ">. It is hyperoctahedral.\n";
					return 1;
				}
			}
			cout << "┌┬┬┐∈C and probably ..∉C, i.e. the category probably correspond to a hyperoctahedral easy QG.\n";
		}
		else cout << "┌┬┬┐∈C and aabaab∈C and probably ..∉C, i.e. the category probably correspond to a hyperoctahedral easy QG in the form of semidirect product C*(Γ)×C(Sn).\n";
	}
	if (isGroup()) {
		if (contains(Word::four)) {
			if (contains(Word::couple)) {
				if (contains(Word::single)) {
					cout << "C=P, i.e. C is the category of all partitions. It corresponds to the group Sn.\n";
					return 1;
				}
				if (*this<Category({Word::cross,Word::couple,Word::four},depth,Nmax)) {
					cout << "C=<X,..,┌┬┬┐>. This corresponds to the group Sn×Z2.\n";
					return 1;
				}
				cout << "<X,..,┌┬┬┐>⊆C⊆<X,.,┌┬┬┐>=P, i.e. C=<X,..,┌┬┬┐> or C=P. This corresponds to group Sn×Z2, resp. Sn.\n";
				return 0;
			}
			if (*this<Category({Word::cross,Word::four},depth,Nmax)) {
				cout << "C=<X,┌┬┬┐>. This corresponds to the group Hn.\n.";
				return 1;
			}
			if (*this<Category({Word::cross,Word::four,Word::couple},depth,Nmax)) {
				cout << "<X,┌┬┬┐>⊆C⊆<X,..,┌┬┬┐>, i.e. C=<X,┌┬┬┐> or C=<X,..,┌┬┬┐>. This corresponds to the group Hn, resp. Sn×Z2.\n";
				return 0;
			}
			cout << "<X,┌┬┬┐>⊆C⊆P, i.e. C=<X,┌┬┬┐> or C=<X,..,┌┬┬┐> or C=<X,.,┌┬┬┐=P. This corresponds to the group Hn, resp. Sn×Z2, resp. Sn.\n";
			return 0;
		}
		if (contains(Word::couple)) {
			if (contains(Word::single)) {
				if (*this<Category({Word::cross,Word::single},depth,Nmax)) {
					cout << "C=<X,.>. This corresponds to the group Bn.\n";
					return 1;
				}
				cout << "<X,.>⊆C⊆<X,.,┌┬┬┐>=P, i.e. C=<X,.> or C=P. This corresponds to group Bn, resp. Sn.\n";
				return 0;
			}
			if (*this<Category({Word::cross,Word::couple},depth,Nmax)) {
				cout << "C=<X,..>. This corresponds to the grup Bn×Z2.\n";
				return 1;
			}
			if (*this<Category({Word::cross,Word::single},depth,Nmax)) {
				cout << "<X,..>⊆C⊆<X,.>, i.e. C=<X,..> or C=<X,.>. This corresponds to group Bn×Z2, resp. Bn.\n";
				return 0;
			}
			cout << "<X,..>⊆C⊆P, i.e. C=<X,..> or C=<X,.> or C=<X,.,┌┬┬┐>=P. This corresponds to group Bn×Z2, resp. Bn, resp. Sn.\n";
			return 0;
		}
		if (*this<Category({Word::cross},depth,Nmax)) {
			cout << "C=<X>. This corresponds to group On.\n";
			return 1;
		}
		if (*this<Category({Word::cross,Word::couple},depth,Nmax)) {
			cout << "<X>⊆C⊆<X,..>, i.e. C=<X> or C=<X,..>. This corresponds to group On, resp. Bn×Z2.\n";
			return 0;
		}
		if (*this<Category({Word::cross,Word::single},depth,Nmax)) {
			cout << "<X>⊆C⊆<X,.>, i.e. C=<X> or C=<X,..> or C=<X,.>. This corresponds to group On, resp. Bn×Z2, resp. Bn.\n";
			return 0;
		}
		if (*this<Category({Word::cross,Word::four},depth,Nmax)) {
			cout << "<X>⊆C⊆<X,┌┬┬┐>, i.e. C=<X> or C=<X,┌┬┬┐>. This corresponds to group On, resp. Hn.\n";
			return 0;
		}
		if (*this<Category({Word::cross,Word::four,Word::couple},depth,Nmax)) {
			cout << "<X>⊆C⊆<X,┌┬┬┐,..>, i.e. C=<X> or C=<X,┌┬┬┐> or C=<X,┌┬┬┐,..>. This corresponds to group On, resp. Hn, resp. Sn×Z2.\n";
			return 0;
		}
		cout << "X∈C, i.e. the category correspond to a group.\n";
	}
	if (isHalfLib()) {
		if (contains(Word::four)) {
			if (*this<Category({Word::zhe,Word::four},depth,Nmax)) {
				cout << "C=<Ж,┌┬┬┐>. It is half-liberated.\n";
				return 1;
			}
			for (int i=3;i<depth/2;i++) {
				if (contains(Word::h(i))) {
					if (*this<Category({Word::zhe,Word::four,Word::h(i)},depth,Nmax)) {
						cout << "C=<Ж,┌┬┬┐,h" << i << ">. It is half-liberated\n";
						return 1;
					}
					cout << "<Ж,┌┬┬┐,h" << i << ">⊆C. It is half-liberated\n";
					return 2;
				}
			}
			cout << "<Ж,┌┬┬┐>⊆C. It is probably half-liberated.\n";
			return 2;
		}
		if (contains(Word::couple)) {
			if (*this<Category({Word::zhe,Word::couple},depth,Nmax)) {
				cout << "C=<Ж,..>. It is half-liberated.\n";
				return 1;
			}
			cout << "<Ж,..>⊆C. It is probably half-liberated.\n";
			return 0;
		}
		if (*this<Category({Word::zhe},depth,Nmax)) {
			cout << "C=<Ж>. It is half-liberated.\n";
			return 1;
		}		
		cout << "Ж∈C and probably X∉C, i.e. the category probably correspond to a half-liberated easy QG.\n";
	}
	if (contains(Word::four)) {
		if (contains(Word::couple)) {
			if (contains(Word::single)) {
				if (isFree()) {
					cout << "C=NC. It is free and non-hyperoctahedral.\n";
					return 1;
				}
				cout << "NC⊆C.\n";
				return 0;
			}
			if (*this<Category({Word::couple,Word::four},depth,Nmax)) {
				cout << "C=<..,┌┬┬┐>. It is free and non-hyperoctahedral.\n";
				return 1;
			}
			if (isFree()) {
				cout <<"<..,┌┬┬┐>⊆C⊆NC, so C=<..,┌┬┬┐> or C=NC. It is free and non-hyperoctahedral.\n";
				return 0;
			}
			cout <<"<..,┌┬┬┐>⊆C.\n";
			return 0;
		}
		if (*this<Category({Word::four},depth,Nmax)) {
			cout << "C=<┌┬┬┐>. It is free and hyperoctahedral.\n";
			return 1;
		}
		if (*this<Category({Word::four,Word::couple},depth,Nmax)){
			cout << "<┌┬┬┐>⊆C⊆<..,┌┬┬┐>, so C=<┌┬┬┐> or C=<..,┌┬┬┐>. It is free.\n";
			return 0;
		}
		if (isFree()) {
			cout << "<┌┬┬┐>⊆C⊆NC, so C=<┌┬┬┐> or C=<..,┌┬┬┐> or C=NC. It is free.\n";
			return 0;
		}
		cout << "<┌┬┬┐>⊆C.\n";
		return 0;
	}
	if (contains(Word::couple)) {
		if (contains(Word::abcb)) {
			if (contains(Word::single)) {
				if (*this<Category({Word::single},depth,Nmax)) {
					cout << "C=<.>, NC2⊂C⊂NC. It is free and non-hyperoctahedral. \n";
					return 1;
				}
				if (isFree()) {
					cout << "<.>⊆C⊆NC, so C=<.> or C=NC. It is free and non-hyperoctahedral.\n";
					return 0;
				}
				cout << "<.>⊆C.\n";
				return 0;
			}
			if (*this<Category({Word::abcb},depth,Nmax)) {
				cout << "C=<|abcb>, NC2⊂C⊂NC. It is free and non-hyperoctahedral. \n";
				return 1;
			}
			if (*this<Category({Word::single},depth,Nmax)) {
				cout << "<|abcb>⊆C⊆<.>, i.e. C=<|abcb> or C=<.>. It is free and non-hyperoctahedral. \n";
				return 0;
			}
			if (isFree()) {
				cout << "<abcb>⊆C⊆NC, so C=<abcb> or C=<.> or C=NC. It is free and non-hyperoctahedral.\n";
				return 0;
			}
			cout << "<abcb>⊆C.\n";
			return 0;
		}
		if (*this<Category({Word::couple},depth,Nmax)) {
			cout << "C=<..>, NC2⊂C⊂NC. It is free and non-hyperoctahedral. \n";
			return 1;
		}
		if (*this<Category({Word::abcb},depth,Nmax)) {
			cout << "<..>⊆C⊆<|abcb>, i.e. C=<..> or C=<|abcb>. It is free and non-hyperoctahedral. \n";
			return 0;
		}
		if (*this<Category({Word::single},depth,Nmax)) {
			cout << "<..>⊆C⊆<.>, i.e. C=<..> or C=<|abcb> or C=<.>. It is free and non-hyperoctahedral. \n";
			return 0;
		}
		if (isFree()) {
			cout << "<..>⊆C⊆NC, so C=<..> or C=<abcb> or C=<.> or C=NC. It is free and non-hyperoctahedral.\n";
			return 0;
		}
		cout << "<..>⊆C.\n";
		return 0;
	}
	if (*this<Category({},depth,Nmax)) {
		cout << "C=NC2. It is free and non-hyperoctahedral.\n";
		return 1;
	}
	if (*this<Category({Word::couple},depth,Nmax)) {
		cout << "NC2⊆C⊆<..>, i.e. C=NC2 or C=<..>. It is free and non-hyperoctahedral. \n";
		return 0;
	}
	if (*this<Category({Word::four},depth,Nmax)) {
		cout << "NC2⊆C⊆<┌┬┬┐>, so C=NC2 or C=<┌┬┬┐>. It is free.\n";
		return 0;
	}
	if (*this<Category({Word::abcb},depth,Nmax)) {
		cout << "NC2⊆C⊆<|abcb>, i.e. C=NC2 or C=<..> or C=<|abcb>. It is free and non-hyperoctahedral. \n";
		return 0;
	}
	if (*this<Category({Word::single},depth,Nmax)) {
		cout << "NC2⊆C⊆<.>, i.e. C=NC2 or C=<..> or C=<|abcb> or C=<.>. It is free and non-hyperoctahedral. \n";
		return 0;
	}
	if (*this<Category({Word::couple,Word::four},depth,Nmax)) {
		cout << "NC2⊆C⊆<..,┌┬┬┐>, so C=NC2 or C=<┌┬┬┐> or C=<..,┌┬┬┐>. It is free.\n";
		return 0;
	}
	if (isFree()) cout << "NC2⊆C⊆NC, i.e. the category correspond to free easy QG.\n";
	
	return 0;
}

void Category::printrels(int n, int d){
	cout << "LIB \"freegb.lib\";" << endl;
	cout << "ring r = 0,(u(1.."<< n << ")(1.." << n << ")),dp;" << endl;
	cout << "def R = makeLetterplaceRing("<<(d/2+1)<<"); setring R;" << endl;
	cout << "ideal I=" << endl;
	Word::identity.printrel(0,n);
	Word::identity.printrel(2,n);
	for (vector<Word>::iterator it=gen.begin();it!=gen.end();it++)
		it->printrel(it->getl()/2,n);
	cout << "0;";
}
