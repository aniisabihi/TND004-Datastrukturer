/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark: interface for undirected graphs    *
**********************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"

class Graph
{
public:
    // -- CONSTRUCTORS
    explicit Graph(int n);

    // -- DESTRUCTOR
    ~Graph();

    // -- MEMBER FUNCTIONS

    // insert undirected edge (u, v) with weight w
    // update weight w if edge (u, v) is present
    void insertEdge(int u, int v, int w);

    // remove undirected edge (u, v)
    void removeEdge(int u, int v);

    // Prim's minimum spanning tree algorithm
    void mstPrim() const;

    // Kruskal's minimum spanning tree algorithm
    void mstKruskal() const;

    // print graph
    void printGraph() const;

    int W(int v, int u) const;

    int find_smallest_undone_distance_vertex() const;

    void printU() const;

    void heapify(Heap<Edge> & H) const;


private:
    // -- DATA MEMBERS
    List *array;
    int  *dist;
    int  *path;
    bool *done;
    int  size;
};

#endif
