#include "linklist3d.h"

LinkList3d::LinkList3d()
{
    root = NULL;
}


LinkList3d::LinkList3d( Mass *temp )
{
    root = new Node( temp );
}


LinkList3d::~LinkList3d()
{
}


Node* LinkList3d::findPlace( Node *temp )
{
    Node *cur = root;
    vector<COOR_TYPE> loc1 = temp->mass->getLocation();
    vector<COOR_TYPE> loc2;

    if( cur == NULL )
      goto ret;

    for( int i = 0; i < 6; i++ )
    {
      for(; cur->link[i] != NULL; cur = cur->link[i]  )
      {
        loc2 = cur->mass->getLocation();
        
        if( i % 2 )
        {
          if( loc1[i] > loc2[i] )
            break;
        }
        else
          if( loc1[i] < loc2[i] )
            break;
      }
    }

    ret:
      return cur;
}

void LinkList3d::add( Mass *arg1 )
{
    Node      *cur = new Node( arg1 );

    if( cur == NULL )
    {
      root = cur;
      return;
    }

    /* Placement depends on which side is closer */
    for( int i = 0; i < 6; i+=2 );
}


void LinkList3d::pop()
{
  curr = stack.back(); 
  stack.pop_back();
}


void LinkList3d::push()
{
  stack.push_back( curr );
}
