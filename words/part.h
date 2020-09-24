#ifndef PART_H
#define PART_H

class Partition{
	int *w;
	int k,l;
	void normalize();
public:
	Partition(int *w,int k,int l);
	Partition(const Partition &p);
	~Partition() {delete[] w;}
	void print() const;
	bool operator==(Partition &rhs);
	bool operator!=(Partition &rhs);
	bool operator<(Partition &rhs); 
	bool operator<=(Partition &rhs); 
	bool operator>(Partition &rhs); 
	bool operator>=(Partition &rhs); 
	bool isNull(){return (w==nullptr);}
	Partition operator*(const Partition &q) const;
	Partition conj() const;
	Partition operator+(const Partition &q) const;
	int getk() {return k;}
	int getl() {return l;}
	int getw(int i) {return w[i];}
	static const Partition identity;
	static const Partition pair;
	static const Partition cross;
	static const Partition single;
	static const Partition four;
	static const Partition zhe;
	static const Partition couple;
	static const Partition abcb;
};

#endif
