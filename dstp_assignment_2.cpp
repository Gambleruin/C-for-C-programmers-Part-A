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
#include <unordered_map>
 
#include <limits> // for numeric_limits
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include <queue>

const max_cost = std::numeric_limits<double>::infinity();

/*
template <typename T>
class graph
{
	std::vector<Vertex> vertices;
	std::vector<Vertex> vertices;
	struct Vertex
	{
		int id;
		int cost;
		const bool directed;
	};

	public:
		graph(bool directed =false): directed(directed){}

		int AddVertex(int id, T val){
			vertices.push_back(Vertex(id, val));
			return id;
		}

		void AddEdge(int start_id, int end_id, int cost =0);
		const T &GetVertexData(int vertex_id) const;



		template <typename U>
		friend std::ostream &operator<<(std::ostream &out, Graph<U> &g);

	private:
		void Print(std::ostream &out) const;

}
*/
// priority queue implementation
template<typename T>
class priorityQueue{
	struct Node
	{
		int priority;
		T info;
		Node* next;
		Node(T item): info(item), next(nullptr){}
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

class edge
{
	int destination_vertex;
	int Cost;
	public:

		int getDest() const {
			return destination_vertex;
		}

		int getCost() const{
			return Cost;
		}

		edge(int ver, int co)
			: destination_vertex(ver), Cost(co)
		{}

	friend std::ostream& operator<<(std::ostream& s, edge const& e)
	{
		return s <<e.destination_vertex;
	}
};

class graph;
class vertex
{
	friend class graph;
	int id;
	std::list<edge> list; 

	public:
		vertex(int id)
			: id(id)
		{}

	friend std::ostream& operator<<(std::ostream& s, vertex const& v)
	{
		s << v.id << "->";
		std::copy(v.list.begin(), v.list.end(),
			std::ostream_iterator<>(s, ","));
		return s;
	}

};

class graph
{
	private:
		std::vector<vertex> vertices;
		int 				next;

	public:
		graph()
			: next(0)
		{}
		/*
			add a new node 'n'
			the vector of edges defines what node(s) 'n' connects to,
			add an edge from 'n' to each node in 'edges'
			add an edge from each node in 'edges' to 'n'
			it is assumed that 'edges' does not contain any nodes
		*/
		void add_node(std::vector<int> const &edges)
		{
			vertices.push_back(vertex(next));

			for(unsigned int i =0; i<edges.size(); ++i)
			{
				vertices[edges[i]].list.push_back(next);
				vertices[next].list.push_back(edge[i]);
			}
			++next;
		}

		friend std::ostream &operator<<(std::ostream& s, graph const& g)
		{
			std::copy(g.vertices.begin(), g.vertices.end(),
				std::ostream_iterator<vertex>(s, "\n"));
			return s;
		}
};

//dijkstra representation, the type here is edge
template <typename T>
class Dijkstra
{
	//std::vector<std::vector<T>> adjacency_vector;
	// the neighbor struct will not be needed as edge class is suffice
	/*
	struct neighbor
	{
		T edge;
		U weight;

		neighbor(int arg_target, int arg_weight)
        : vertex(arg_target), weight(arg_weight) {}
	};
	*/
	public:
		//Dijkstra(): adjacency_vector(){}    ????

		//friend std::ostream &operator<<(std::ostream &out, Dijkstra<T, U> &g);
		std::vector<T> DijkstraComputePaths(int source,                 
                          std::vector<std::vector<T>> const& adjvM
                          std::vector<int> &min_distance,
                          std::vector<int> &previous)
		{
			/*
			for(auto const &item :adj_list){
				adjacency_vector[item.first].push_back(item.second);
			}
			*/
			
			//adjacency_vector const&adjacency_v; 
			int n = adjvM.size();
    		min_distance.clear();
    		min_distance.resize(n, max_cost);
    		min_distance[source] = 0;
    		previous.clear();
    		previous.resize(n, -1);
			priorityQueue<std::edge> pq;
			pq.insert(min_distance[source], std::make_pair(min_distance[source], source));

			while (!pq.empty()) {
				/*
				if pq.first! =nullptr && pq.first! =source:
					then do:
						u =pq.pop_at_front();

				u =source;
				// the corresponding weight is abitrary in the beginning, which will be initialized. 
				*/
				int u =pq.extractMin().first;
				int dist =pq.extractMin().second;
				pq.pop_at_front();

        		if (dist > min_distance[u])
	    			continue;
	    		// Visit each edge exiting u
				const std::vector<std::edge> &neighbors = adjvM[u];
				for (std::vector<std::edge>::const_iterator neighbor_iter = neighbors.begin();
             			neighbor_iter != neighbors.end();
             			neighbor_iter++){
					
					int v = neighbor_iter->destination_vertex;
            		int cost = neighbor_iter->cost;
            		int distance_through_u = dist + weight;

	    			if (distance_through_u < min_distance[v]) {
	        			min_distance[v] = distance_through_u;
	        			previous[v] = u;
	        			pq.insert(min_distance[v], std::make_pair(min_distance[v], v));
	        		}
				}
			}
			return previous;
		}

		std::list<int> DijkstraGetShortestPathTo(
    		int vertex, const std::vector<int> &previous)
		{
    		std::list<int> path;
    		for ( ; vertex != -1; vertex = previous[vertex])
        		path.push_front(vertex);

        	//??? 
    		return path;
		}
/*
	private:
		void print(std::ostream &out) const;
		*/

}

/*
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
*/

int main()
{
/*
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
	previous =d.DijkstraComputePaths(source, graph);
	std::list<int> =path;

	path =d.DijkstraGetShortestPathTo(destin, previous);

	void list:: print(){
		list_element* h =head;
		while(h !=0){
			cout <<h->d << ", ";
			h =h->next;
		}
		cout <<"###" <<endl;
	}
*/
	graph g;
    std::vector<int>    v;
    g.add_node(v);

    v.push_back(0);
    g.add_node(v);

    std::cout << g << "\n";
	
}










