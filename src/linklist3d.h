#ifndef LINKLIST3D_H
#define LINKLIST3D_H

#include "mass.h"

/**
	@author Kapone <kapone@7rc.org>
*/
class Node {
public:
      Node( Mass* temp ) { mass = temp; };

      Mass  *mass; 
      Node* link[ 6 ];
};

class LinkList3d{
    /* Object pointed to by this object */
    static const int left    = 0;
    static const int right   = 1;
    static const int up      = 2;
    static const int down    = 3;
    static const int front   = 4;
    static const int back    = 5;

    /* Object contained by this object */
    Node* root;
    Node* curr;
    vector<Node*> stack;

    Node* findPlace( Node* );

    COOR_TYPE modulus( vector<COOR_TYPE> );

public:
    LinkList3d();
    LinkList3d( Mass *temp );

    ~LinkList3d();

    /* Used for pushing and popping curr */
    void pop();
    void push();

    
    void add( Mass* temp );
    Mass *getCurrent(){ return ( curr == NULL )? curr->mass:NULL;  };
};

#endif
