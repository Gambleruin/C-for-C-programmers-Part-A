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

bool **graph;
	srand(); //seed rand()
	graph =new bool*[size];
	for (int i =0; i<size; i++)
		graph[i] =new bool[size];
	
//heap created 2d array of Bool