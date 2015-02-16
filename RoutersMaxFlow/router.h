// Authors: Daniel Chen & Gloria Chen

#ifndef ROUTER_H
#define	ROUTER_H

#include "BinaryHeap.h"
#include <iostream>

using namespace std;

class Edge {
  //this is for inserting into the heap
  public:
  inline bool operator< (const Edge& rhs) const {return min > rhs.min;}
  int min; // path min variable
  int prev, curr; // previous edge and current edge index
  int prev_ind;
};

class Router {
public:
  int **edges, **caps, *count, numEdges, *currentMin; //count is num connected, caps is capacities, currentMin flow allows us to not insert irrelevant edges
  int flow, currFlow, num; //flow stores total flow, currFlow stores current flow
  bool *known;
//  int numRout; // for debugging
  Router(const int **capacities, int numRouters);
  int solve(int NYCPos);
private:

};

#endif	/* ROUTER_H */

