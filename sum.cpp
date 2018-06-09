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

	//init the vector
	for (int j = 0; j < N; ++j) {
    	data[j] =j;

	memset( &d, 0, sizeof( d ) );
	sum(&accum, N, data);

	//print out the result
	cout<<"sum is %d\n"<< accum<<endl;
	return 0;
}