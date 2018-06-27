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
#define INFINITY 1000000//define infinity 
 
//each node to which path in graph can be found has its own property
struct GraphNode{
    bool known;//if there exists a path to which source node is connected to the current node
    int dist;//shortest path between current node and source node
    int path;//the previous node on the path
};
 
typedef struct Node{ 
    int edge_num;
    int src;
    int vertex;//self 
    int weight;
}Node; 

class Graph{
    private:
        int edge_num;
        int vertex_num;
        list<Node> * graph_list;//adjacency list
        vector<GraphNode> nodeArr;//graph of nodes to be run on dijkstra 
        
    public:
        Graph(){}
        Graph(char* graph[], int edgenum); 
        ~Graph();
        void print();
        void dijkstra(int src);
        void printShorestPath(); 
    private:
        vector<int> get_graph_value(char* graph[], int columns);
        void addEdge(char* graph[], int columns);
};
 
#endif
 
