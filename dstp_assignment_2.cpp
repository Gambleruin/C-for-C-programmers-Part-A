/* 
dijkstra_stl_template practise in c++
*/
#include <iostream>   //drops .h still available
#include <string>
#include <sstream>
#include <cstdio>  
#include <cstdlib> 

#include <vector> 
using namespace std;

//base graph constructor
bool **graph;
	srand(); //seed rand()
	graph =new bool*[size];
	for (int i =0; i<size; i++)
		graph[i] =new bool[size];

//heap created 2d array of Bool, init of the graph
//next, Density is 0.19
for(int i =0; i<size; ++i)
	for(int j =i; j<size; ++j)
		if(i ==j) graph[i][j] =false; //np loops
			else graph[i][j] =graph[j][i] =(prob()<0.19);

//density is the probability that an edge exists

/*
algorithm details:
	it starts with node0 and determines which nodes can be reached from this node
	placing them in an open set and placing node 0 as the first node of a connected
	component.
	each iteration adds one node to the closed set.
	this stops with either no further nodes reachable and is_connected is false or all nodes
	being included in the closed set.
	The algorthm was published as a SLAC report and later a generalization was published by hop
	croft and Tarjan in 1973

	open set will only include nodes that are NOT in the closed set!
*/

//implement ls_connected
bool is_connected(bool *graph[], int size)
{
	int old_size =0, c_size =0;
	bool* close =new bool[size];
	bool* open =new bool[size];
	for(int i =0; i<size; ++i)
		open[i] =close[i] =false;
	open[0] =true;

	//add to close, c_size =closed set sign

	for(int i =0; i<size; ++i){
		old_size =c_size;
		if(open[i]){
			close[i] =true; c_size++;			
		}
		for(int j =0; j<size; ++j)
			open[j] =open[j]||graph[i][j];
	}
		
	//where to place??
	if(c_size ==size) 
		return true;
	//else if(old_size ==c_size) return false;
	return false;

}

















