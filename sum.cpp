/* first assignment convert c into c++ */
#include <iostream>   //drops .h still available
#include <cstdio>  
#include <cstdlib>  

using namespace std;
const int N = 40; 
//inline int r_sides(){ return (rand() % sides + 1); }

/*
use the idea of STL containers.
*/

void sum(int *p, int n, vector <int> d){
	for (auto& i : d)
    	*p += i;
}

int main(){
	int accum =0;
	vector<int> data(N);
	memset( &d, 0, sizeof( d ) );
	sum(&accum, N, data);
	return 0;
}