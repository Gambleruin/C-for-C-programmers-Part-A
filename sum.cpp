/* first assignment convert c into c++ */
#include <iostream>   //drops .h still available
#include <string>
#include <sstream>
#include <cstdio>  
#include <cstdlib> 

#include <vector> 
using namespace std;
const int N = 40; 
vector<int> data(N);
inline void init(){ for (int j = 0; j < N; ++j) 
    	data[j] =j; }

/*
use the idea of STL containers.
*/

void sum(int *p, int n, vector <int> d){
	for (auto& i : d)
    	*p += i;
}

int main(){
	int accum =0;
	//init the vector
	init();
	//static memory allocation, this is not needed, 
	//memset( &data, 0, sizeof( data ) );
	sum(&accum, N, data);

	//print out the result
	cout<<"sum is %d\n"<< accum<<endl;
	return 0;
}