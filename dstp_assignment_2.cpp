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
 
#include <list>
#include <limits> // for numeric_limits
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include <queue>

//graph representation
const int num_vertices =5;
const double max_cost = std::numeric_limits<double>::infinity();

class edge
{
	int destination_vertex;
	int Cost;
	bool is_c;

	public:
		edge(int ver, int cost, bool Ic)
			: destination_vertex(ver), Cost(cost), is_c(Ic)
		{}
		int getDest() const {
			return destination_vertex;
		}
		int getCost() const{
			return Cost;
		}
		bool is_connected(edge const& e) const{
			return e.is_c;
		}


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
    std::vector<edge>  list;

    public:
        vertex(int id) 
            : id(id)
        {} 

/*
        vertex(const vertex& copy)   
        : id(copy.id), list(new std::vector<edge>(*copy.list))  
    	{}
*/
    	

    	friend std::ostream& operator<<(std::ostream& s, vertex const& v)
    	{   
        	s << v.id << "->";
          	std::copy(v.list.begin(), v.list.end(),
            std::ostream_iterator<edge>(s, ","));
            return s;
    	}   
};

class graph
{   
	private:
        std::vector<vertex> vertices;
        std::vector<std::vector<edge>> adjM;

    public:

        // graph(graph &g) { /* Copy data members from t*/}
    	graph(std::vector<vertex> v, std::vector<std::vector<edge>> ajM): 
    		vertices(v), adjM(ajM){}

        void add_node ( edge const &e, int id)
        {   
        	vertices.push_back(vertex(id));
        	for(int i =0; i<num_vertices; i++){
        		printf("the id is: %d\n\n\n\n", vertices[id].id);
 				vertices[id].list.push_back(e);
 			}
        } 

        void add_edgeList(std::vector<vertex> v)
        {
        	for (auto &it: v)
        	{
        		printf("kuai jin lai, ni mian hao shu fu\n\n\n");
    			adjM[it.id] =it.list;
    		}
        }

        std::vector<vertex> getVertices(){
        	return vertices;
        }

        std::vector<std::vector<edge>> getAdjM(){
        	return adjM;
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

        friend std::ostream& operator<<(std::ostream& s, graph const& g)
        {   
             std::copy(g.vertices.begin(), g.vertices.end(),
                       std::ostream_iterator<vertex>(s, "\n"));
             return s;
        }   
};  

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

template <typename T>
class Dijkstra
{
	public:

		priorityQueue<T> init_queue(const T& item){
			priorityQueue<T> pq;
			return pq;
		}

		std::vector<int> DijkstraComputePaths(int source,                 
                          std::vector<std::vector<edge>> const& adjvM,
                          std::vector<int> &min_distance,
                          std::vector<int> &previous, 
                          priorityQueue<T> pq)
		{

			int n = adjvM.size();
    		min_distance.clear();
    		min_distance.resize(n, max_cost);
    		min_distance[source] = 0;
    		previous.clear();
    		previous.resize(n, -1);

			pq.insert(min_distance[source], std::make_pair(min_distance[source], source));
			while (!pq.empty()) {

				int u =pq.extractMin().first;
				int dist =pq.extractMin().second;
				pq.pop_at_front();

        		if (dist > min_distance[u])
	    			continue;
				const std::vector<edge> &neighbors = adjvM[u];
				for (std::vector<edge>::const_iterator neighbor_iter = neighbors.begin();
             			neighbor_iter != neighbors.end();
             			neighbor_iter++){
					
					int v = neighbor_iter->getDest();
            		int cost = neighbor_iter->getCost();
            		int distance_through_u = dist + cost;

	    			if (distance_through_u < min_distance[v]) {
	        			min_distance[v] = distance_through_u;
	        			previous[v] = u;
	        			pq.insert(min_distance[v], std::make_pair(min_distance[v], v));
	        		}
				}
			}
			return previous;
		}

		std::list<int> DijkstraGetShortestPathTo(int v_id, const std::vector<int> &previous)
		{
    		std::list<int> path;
    		for (; v_id != -1; v_id = previous[v_id])
        		path.push_front(v_id);

    		return path;
		}
};

void application(const std::vector<edge> &edges){

	std::vector<vertex> v;
	std::vector<std::vector<edge>> adjM;
	graph g(v, adjM);
	int next =0;

	//void (graph::* addN) (const edge &, int) = &graph::add_node;
	//void (graph::* addEdge) (std::vector<vertex>) = &graph::add_edgeList;
	for (auto &it: edges){	
			/*
				if(it.is_connected(it)){
					printf("wtf\n");
					g.add_node(it, i);

				}
			*/
		    g.add_node(it, i);
		
	}
	printf("wtf\n");
	v =g.getVertices();
	//(g.*addEdge)(v);
	g.add_edgeList(v);
	adjM =g.getAdjM();

	// now the entire graph representation is in adjM

      
}

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
	std::vector<edge> edges;
	edge e0 (0,1,true);
	edge e1 (1,1,true);
	edge e2 (2,1,true);
	edge e3 (3,1,true);
	edges.push_back(e0);
	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);
	/*
	for(auto const& value: edges) {
		std::cout << value.getCost(); 
	}
	*/
	application(edges);

	//Dijkstra::DijkstraComputePaths();
	return 0;
}










