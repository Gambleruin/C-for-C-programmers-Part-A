#ifndef GRAPH_H
#define GRAPH_H
 
#include <list>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <queue>
 
using namespace std;
 
#define MAX_VERTEX_NUM 600
#define INFINITY 1000000

/*
struct GraphNode{
    bool known;//if there exists a path to which source node is connected to the current node
    int dist;//shortest path between current node and source node
    int path;//the previous node on the path
    int id; //to which graph node it  corresponds
    bool operator <(const GraphNode &x) const //operator overload
    {
    	if(x.dist !=dist)
    		return x.dist <dist;
    	else
    		return false;
    }
};
*/

typedef struct Node{ 
    //int edge_num;
    int src;
    int id; //self 

    //added
    bool known;//if there exists a path to which source node is connected to the current node
    int dist;//shortest path between current node and source node
    int path;//the previous node on the path

    Node(){}

    bool operator <(const Node &x) const //operator overload
    {
    	if(x.dist !=dist)
    		return x.dist <dist;
    	else
    		return false;
    }    
}Node; 

class Graph{
    private:
        int edge_num;
        int vertex_num;
        list<Node> *graph_list;//adjacency list
        // vector<GraphNode> nodeArr; (from old code)
        
    public:
        Graph(){}
        Graph(char* graph[], int edgenum);
        ~Graph();
        void print();
        //void dijkstra(int src);
        void dijkstra(int src);
        void printShorestPath(); 
    private:
        vector<int> get_graph_value(char* graph[], int columns);
        Node Init(int edge_num, int id, int dist);
        void addEdge(char* graph[], int columns);
};
 
#endif
 
