/* 
dijkstra_stl_template practise in c++
for the reference where dijkstra can be proved to be true:
http://web.stanford.edu/class/archive/cs/cs161/cs161.1176/Lectures/CS161Lecture11.pdf
*/

#include <iostream>   
#include <sstream>
#include <cstdio>  
#include <cstdlib> 
#include <vector>

#include <vector> 
#include <list>
 
#include <limits> // for numeric_limits
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include <queue>

const max_weight = std::numeric_limits<double>::infinity();

// priority queue implementation
template<typename T>
class priorityQueue{
	struct Node
	{
		int priority;
		T info;
		Node* next;
		Node(T item) : info(item), next(nullptr){}
	};
	Node* front;

	public:
		priorityQueue() : front(nullptr) {}
		~priorityQueue(){
			Node *tmp =nullptr;
			while(front){
				tmp =front;
				front =front->next;
				delete tmp;
			}
			front =nullptr;
		}

		void insert( int priority, const T& item){
			Node* tmp;
			Node* node =new Node(item);
			node->priority =priority;

			if(front ==nullptr||priority <front->priority){
				node->next =front;
				front =node;   
			}else{
				tmp =front;
				while(tmp->next !=nullptr && tmp->next->priority <=priority)
					tmp =tmp->next;

				node->next =tmp->next;
				tmp->next =node;
			}
		}

		void pop_at_front(){
			if(front->next)
				front =front->next;
		}
/*
		void deleteItem(const T& item){
			Node *find =search(item);
			Node *node =front;
			if(node ==find)
				front =node->next;
			else{
				while(find != nullptr){
					if(node->next ==find){
						node->next =find->next;
						delete find;
						return;
					}
					node =node->next;
				}
			}
		}
*/
		const T extractMin(){
			if(front)
				return front;
			return nullptr;
		}

		friend std::ostream & operator <<(std::ostream &os, const priorityQueue<T> &pq){
			pq.display_min(os);
			return os;
		}

	private:
		Node *search(const T& item)
		{
			Node *node =front;
			while(node !=nullptr){
				if(node->info ==item)
					return node;

				node =node->next;
			}
			std::cerr << "No such element in the lsit \n";
			return nullptr;
		}

		void display(std::ostream& out = std::cout) const
		{
			Node *node =front;
			out<<"\nItem \tPriority \n";
			while(node != nullptr)
			{
				out <<node->info << "\t" <<node->priority << "\n";
				node =node->next;
			}
		}

		void display_min(std::ostream& out = std::cout) const
		{
			out <<front->info << "\t" <<front->priority << "\n";
		}
};

//dijkstra representation
template <typename T, U>
class Dijkstra
{
	std::vector<std::vector<T, U>> adjacency_vector;
	struct neighbor
	{
		T vertex;
		U weight;

		neighbor(int arg_target, int arg_weight)
        : vertex(arg_target), weight(arg_weight) {}
	};
	public:
		Dijkstra(): adjacency_vector(){}

		//friend std::ostream &operator<<(std::ostream &out, Dijkstra<T, U> &g);
		std::vector<T> DijkstraComputePaths(int source,                 
                          std::vector<std::pair<T, U>> const& adj_list
                          std::vector<U> &min_distance,
                          std::vector<T> &previous)
		{
			for(auto const &item :adj_list){
				adjacency_vector[item.first].push_back(item.second);
			}

			adjacency_vector const&adjacency_v; 
			int n = adjacency_v.size();
    		min_distance.clear();
    		min_distance.resize(n, max_weight);
    		min_distance[source] = 0;
    		previous.clear();
    		previous.resize(n, -1);
			priorityQueue<std::string> pq;
			pq.insert(std::make_pair(min_distance[source], source));

			while (!adjacency_v.empty()) {
				int dist = adjacency_v[source].first;
        		int u = adjacency_v[source].second;
        		pq.pop_at_front();

        		if (dist > min_distance[u])
	    			continue;
	    		// Visit each edge exiting u
				const std::vector<neighbor> &neighbors = adjacency_v[u];
				for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             			neighbor_iter != neighbors.end();
             			neighbor_iter++){
					
					T v = neighbor_iter->vertex;
            		int weight = neighbor_iter->weight;
            		int distance_through_u = dist + weight;

	    			if (distance_through_u < min_distance[v]) {
	        			min_distance[v] = distance_through_u;
	        			previous[v] = u;
	        			pq.insert(std::make_pair(min_distance[v], v));
	        		}
				}
			}
			return previous;
		}

		std::list<T> DijkstraGetShortestPathTo(
    		T vertex, const std::vector<T> &previous)
		{
    		std::list<T> path;
    		for ( ; vertex != -1; vertex = previous[vertex])
        		path.push_front(vertex);

    		return path;
		}
/*
	private:
		void print(std::ostream &out) const;
		*/

}

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

	//where to place??
	if(c_size ==size) 
		return true;
	//else if(old_size ==c_size) return false;
	return false;
}

int main()
{

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

	Dijkstra d;
	source, destin;
	std::list<int> previous;
	previous =d.init_adj_Rep(source, graph);
	std::list<int> =path;

	path =d.DijkstraGetShortestPathTo(destin, previous);
	//whatever u do with path


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


	//print() chaining, might put it in main? 
	void list:: print(){
		list_element* h =head;
		while(h !=0){
			cout <<h->d << ", ";
			h =h->next;
		}
		cout <<"###" <<endl;
	}
	
}










