#include "router.h"

Router::Router(const int **capacities, int numRouters)
{
  edges = new int*[numRouters];
  caps = new int*[numRouters];
  count = new int[numRouters];
  currentMin = new int[numRouters];
  known = new bool[numRouters];
  num = numRouters;
  numEdges = 0;//for heapsize, will inc with every new edge
  flow = 0;//initial max flow starts at 0

  for(int i = 0; i < numRouters; i++){
    edges[i] = new int[20]; // connected to 20 routers max
    caps[i] = new int[20];
    count[i] = 0;
    known[i] = 0;
    int j=0;
    
    for(int k = 0; k < numRouters; k++){
      if(capacities[i][k] != 0 && !(k == 0 && capacities[i][0] != 0)){
        edges[i][j] = k;
        caps[i][j++] = capacities[i][k];
        count[i]++;
        numEdges++;
      }
    }
  }// read the matrix into a list
} // Router()


int Router::solve(int NYCPos)
{
  for(int i = 0; i < count[NYCPos]; i++){
    caps[NYCPos][i] = 0;
  }

  while(1){ //break if heap returns empty
    BinaryHeap <Edge> heap(numEdges);// ----------------numEdges could potentially slow things down
 
    for(int i = 0; i < num; i++){
      known[i] = 0;
      currentMin[i] = 0;
    }
   
    for(int i = 0; i < count[0]; i++){
      Edge edge;
      edge.min = caps[0][i];
      edge.prev = 0;
      edge.prev_ind = 0;
      edge.curr = edges[0][i];
      currentMin[edges[0][i]] = caps[0][i];
      known[0] = 1;
      heap.insert(edge);
    }// all connected to LA are now in the heap
    
    int itr = 0;
    Edge temp[numEdges]; // the current path
    heap.deleteMin(temp[itr]); // actually the max of heap
    while(temp[itr].curr != NYCPos){ // not at tank
      for(int i = 0; i < count[temp[itr].curr]; i++){
        Edge edge;

        while((known[edges[temp[itr].curr][i]] || caps[temp[itr].curr][i] < currentMin[edges[temp[itr].curr][i]]) && i + 1 != count[temp[itr].curr]){ // if vertex is unnecessary
          i++;
        }
 /*       if(flag == 1){ // i has incremented to the end of array or no more augmented paths
          break;
        }*/

        if(caps[temp[itr].curr][i] > temp[itr].min) // for the flow of the current path
          edge.min = temp[itr].min;
        else
          edge.min = caps[temp[itr].curr][i];

        edge.prev = temp[itr].curr;
        edge.curr = edges[temp[itr].curr][i];
        edge.prev_ind = itr;
        currentMin[edges[temp[itr].curr][i]] = caps[temp[itr].curr][i];
        heap.insert(edge);
      }// all connected to temp.curr are now in the heap
      known[temp[itr].curr] = 1; // mark as known to not be inserted again

      if(heap.isEmpty()){ // no more augmented paths
        break;
      }

      heap.deleteMin(temp[++itr]);

      while(known[temp[itr].curr] == 1)
        heap.deleteMin(temp[++itr]);
    }
    if(temp[itr].min == 0 || temp[itr].curr != NYCPos) // no more augmented paths
      break;

    //now to adjust arrays, and add min to flow
    flow += temp[itr].min;
    currFlow = temp[itr].min;
    //adjust NYC, dec itr
    if(itr != 0){
  //  cout << " "<< temp[itr].prev;
    for(int i = 0; i < count[temp[itr].prev]; i++){
      if(NYCPos == edges[temp[itr].prev][i]){
        caps[temp[itr].prev][i] -= currFlow;
        itr = temp[itr].prev_ind;
      }
    }
        }
    while(temp[itr].curr != 0 && temp[itr].prev != 0){
      for(int k = 0; k < count[temp[itr].curr]; k++){
        if(temp[itr].prev == edges[temp[itr].curr][k]){
          caps[temp[itr].curr][k] += currFlow;
        }
      } // add backflow

      for(int k = 0; k < count[temp[itr].prev]; k++){
        if(temp[itr].curr == edges[temp[itr].prev][k]){
          caps[temp[itr].prev][k] -= currFlow;
        }
      } // complete residual
      itr = temp[itr].prev_ind;

    }//adjust each used edge accordingly
    while(temp[itr].curr != 0 && temp[itr].prev != 0){
      for(int i = 0; i < count[temp[itr].prev]; i++){
       // if(temp[itr].curr == edges[temp[itr].prev][i])
         //   caps[temp[itr].prev][i] -= currFlow;
      }
      for(int i = 0; i < count[temp[itr].curr]; i++){
        if(temp[itr].prev == edges[temp[itr].curr][i])
          caps[temp[itr].curr][i] += currFlow;
      }
      itr = 0;
    }

    for(int i = 0; i < count[0]; i++)
      if(temp[itr].curr == edges[0][i])
        caps[0][i] -= currFlow;

  }
  return flow;
} // solve()
