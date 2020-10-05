#ifndef WORD_H
#define WORD_H

class Word{
	char *w;
	int l;
	void normalize();
public:
	Word(const char *word);
	Word(const char *word, int ll);
	Word(const Word &p);
	~Word() {delete[] w;}
	void print() const;
	void printrel(int k, int n) const;
	Word operator=(Word rhs);
	bool operator==(Word &rhs);
	bool operator!=(Word &rhs);
	bool operator<(Word &rhs); 
	bool operator<=(Word &rhs); 
	bool operator>(Word &rhs); 
	bool operator>=(Word &rhs); 
	bool isNull() const{return (w==nullptr);}
	bool isNonCross() const;
	bool isPair() const;
	Word conj() const;
	Word operator+(const Word &q) const;
	Word rot(int n) const;
	Word comp(int n) const;
	int alpha(int n) const;
	int getl() const {return l;}
	const char* getw() const {return w;}
	int getw(int i) const {return w[i];}
	int intrep() const;
	bool compatible(int *a, int s, int k) const;
	static const Word identity;
	static const Word cross;
	static const Word single;
	static const Word four;
	static const Word zhe;
	static const Word couple;
	static const Word abcb;
	static Word h(int n);
	static Word pi(int n);
	static int iterate(char* w, int s);
	static int iterate2(int *a, int n, int k);
};

#endif
