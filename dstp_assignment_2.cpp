/* 
dijkstra_stl_template practise in c++
for the reference where dijkstra can be proved to be true:
http://web.stanford.edu/class/archive/cs/cs161/cs161.1176/Lectures/CS161Lecture11.pdf
*/
#include <iostream>   //drops .h still available
#include <string>
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
using namespace std;

/*
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
*/



typedef int vertex_t;
typedef double weight_t;
 
const weight_t max_weight = std::numeric_limits<double>::infinity();
 
struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};
 
typedef std::vector<std::vector<neighbor> > adjacency_list_t;
typedef std::pair<weight_t, vertex_t> weight_vertex_pair_t;
 
void DijkstraComputePaths(vertex_t source,
                          const adjacency_list_t &adjacency_list,
                          std::vector<weight_t> &min_distance,
                          std::vector<vertex_t> &previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    // we use greater instead of less to turn max-heap into min-heap
    std::priority_queue<weight_vertex_pair_t,
			std::vector<weight_vertex_pair_t>,
			std::greater<weight_vertex_pair_t> > vertex_queue;
    vertex_queue.push(std::make_pair(min_distance[source], source));
 
    while (!vertex_queue.empty()) 
    {
        weight_t dist = vertex_queue.top().first;
        vertex_t u = vertex_queue.top().second;
        vertex_queue.pop();
 
	// Because we leave old copies of the vertex in the priority queue
	// (with outdated higher distances), we need to ignore it when we come
	// across it again, by checking its distance against the minimum distance
	if (dist > min_distance[u])
	    continue;
 
        // Visit each edge exiting u
	const std::vector<neighbor> &neighbors = adjacency_list[u];
        for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            vertex_t v = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t distance_through_u = dist + weight;
	    if (distance_through_u < min_distance[v]) {
	        min_distance[v] = distance_through_u;
	        previous[v] = u;
	        vertex_queue.push(std::make_pair(min_distance[v], v));
 
	    }
 
        }
    }
}
 
 
std::list<vertex_t> DijkstraGetShortestPathTo(
    vertex_t vertex, const std::vector<vertex_t> &previous)
{
    std::list<vertex_t> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}
 
 
int main()
{
    // remember to insert edges both ways for an undirected graph
    adjacency_list_t adjacency_list(6);
    // 0 = a
    adjacency_list[0].push_back(neighbor(1, 7));
    adjacency_list[0].push_back(neighbor(2, 9));
    adjacency_list[0].push_back(neighbor(5, 14));
    // 1 = b
    adjacency_list[1].push_back(neighbor(0, 7));
    adjacency_list[1].push_back(neighbor(2, 10));
    adjacency_list[1].push_back(neighbor(3, 15));
    // 2 = c
    adjacency_list[2].push_back(neighbor(0, 9));
    adjacency_list[2].push_back(neighbor(1, 10));
    adjacency_list[2].push_back(neighbor(3, 11));
    adjacency_list[2].push_back(neighbor(5, 2));
    // 3 = d
    adjacency_list[3].push_back(neighbor(1, 15));
    adjacency_list[3].push_back(neighbor(2, 11));
    adjacency_list[3].push_back(neighbor(4, 6));
    // 4 = e
    adjacency_list[4].push_back(neighbor(3, 6));
    adjacency_list[4].push_back(neighbor(5, 9));
    // 5 = f
    adjacency_list[5].push_back(neighbor(0, 14));
    adjacency_list[5].push_back(neighbor(2, 2));
    adjacency_list[5].push_back(neighbor(4, 9));
 
    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;
    DijkstraComputePaths(0, adjacency_list, min_distance, previous);
    std::cout << "Distance from 0 to 4: " << min_distance[4] << std::endl;
    std::list<vertex_t> path = DijkstraGetShortestPathTo(4, previous);
    std::cout << "Path : ";
    std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;
 
    return 0;
}

//graph representation
template <typename T>
class Graph
{
	public:

		Graph(bool directed =false): directed(directed){}
		int AddVertex(const T& item);
		const &GetVertexData(int vertex_id) const;

		//??
		template <typename U>
		friend std::ostream &operator<<(std::ostream &out, Graph<U> &g);

	private:
		//??
		int num_

}

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

		void insert(const T& item, int priority){
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

int main()
{
	priorityQueue<std::string> pq1;
  	pq1.insert("code", 82);
  	pq1.insert("sleep", 17);
  	pq1.insert("food", 2);
  	pq1.insert("date", 4);
  	std::cout << pq1;
}









