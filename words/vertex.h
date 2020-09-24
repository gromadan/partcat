#ifndef VERTEX_H
#define VERTEX_H
#include "word.h"

class Vertex{
	int contains;
	Vertex *child;
	int NChildren;
public:
	Vertex():contains(0), child(nullptr), NChildren(0){}
	Vertex(const Vertex &v):NChildren(v.NChildren) {                             //generate the whole subtree 
		if (v.child!=nullptr) {
			child=new Vertex[NChildren];
			for (int i=0;i<NChildren;++i) child[i]=v.child[i];
		} else child=nullptr;
	}
	Vertex operator=(const Vertex &v) {                                          //copies the whole subtree
		NChildren=v.NChildren;
		if (child!=nullptr) delete[] child;
		contains=v.contains;
		if (v.child!=nullptr) {
			child=new Vertex[NChildren];
			for (int i=0;i<NChildren;++i) child[i]=v.child[i];
		} else child=nullptr;
		return *this;
	}
	~Vertex(){if (child!=nullptr) delete[] child;} //will delete also its successors
	friend class Tree;
};

#endif // VERTEX_H

