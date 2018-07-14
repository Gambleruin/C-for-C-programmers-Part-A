#include "graphDijkstra.h"

using Iter = std::vector<Node>::iterator;
//init a node 
Node Graph::Init(int src, int id, int dist)
{
    Node node;
    node.id =id;
    node.src =src;
    node.dist =dist;

    node.path =-1;
    node.known =false;
    return node;
}

// this function is to log graph info and report shortest distance
void Graph::Log(int src){
    for (int i = 0; i < 7; ++i){
        Node node;
        node =Init(src, i+1, INFINITY);
        log_on_nodes.push_back(node);
    }
}

//save all edge info into a vector
vector<int> Graph::get_graph_value(char* graph[], int columns)
{
    vector<int> v;
    char buff[20];
    int i = 0, j = 0, val;
    memset(buff, 0, 20);
 
    while((graph[columns][i] != '\n') && (graph[columns][i] != '\0')){
        if(graph[columns][i] != ','){
            buff[j] = graph[columns][i];
            j++;
        }
        else{
            j = 0;
            val = atoi(buff); 
            v.push_back(val);
            memset(buff, 0, 20);
        }
        i++;
    }
    val = atoi(buff); 
    v.push_back(val);
 
    return v;
}

//add all adjacent edges to the correspondent/vertex
void Graph::addEdge(char* graph[], int columns)
{
    vector<int> v = get_graph_value(graph, columns);
/*
    if(node.vertex > vertex_num)
        vertex_num = node.vertex;
*/
    int src = v[1];
    int id =v[2];
    int dist =v[3];

    //reconsider all the deplicated edges,the same edge with different weight?
    for(list<Node>::iterator it = graph_list[src].begin(); it != graph_list[src].end(); ++it){
        if((*it).id == id){
            if((*it).dist > dist){
                (*it).dist = dist;   
            }
            return;
        }
    }

    Node node =Init(src, id, dist);
    //before running dijkstra
    node.known = false;
    node.path = -1; // this node does not exist
    graph_list[src].push_back(node);
}

// read in all info of a graph, initialize it
Graph::Graph(char* graph[], int edgenum)
{
    graph_list = new list<Node>[MAX_VERTEX_NUM+1];
    for(int i = 0; i < edgenum; ++i){
        addEdge(graph, i);   
    }
}

//release dynamic memory
Graph::~Graph()
{
    delete[] graph_list;
}

//dijkstra with using priority queue
void Graph::dijkstra(int src)
{
    int debug =0;
    auto cmp =[](Node left, Node right) { 
        return left.dist > right.dist;
    };

    priority_queue<Node, vector<Node>, decltype(cmp)> que(cmp);
	// Init position to be added at the front of queue (starting dijkstra)
	Node front =Init(src, src, 0);

    vector<int> m_distance(10);
    fill(m_distance.begin(), m_distance.end(), INFINITY);
    m_distance[src]= 0;

	// init the queue with the source
    que.push(front);

    //init log
    log_on_nodes[src -1].dist =0;
    log_on_nodes[src -1].path =0;

	while(!que.empty()){

        printShortestPath();
        if (debug == 7)
            break;

		Node front =que.top();
        int v =front.id;
        int p =front.path;
        int update_dist =front.dist;
		que.pop();

        //printf("current front is: \n\n%d\n\n\n\n\n", v);

		// Because we leave old copies of the vertex in the priority queue
	    // (with outdated higher distances), we need to ignore it when we come
	    // across it again, by checking its distance against the minimum distance
		if (m_distance[v] < update_dist) 
			continue;

		front.known = true;

        //update log information
        int idx =v-1;

        log_on_nodes[idx].known =true;
    
		// update front's neighbors
		for(list<Node>::iterator it = graph_list[v].begin(); it != graph_list[v].end(); ++it){
            if(!(*it).known){

                int distance_through =update_dist +(*it).dist;
                int neighbor_id =(*it).id;
                if(distance_through < m_distance[neighbor_id]){
                    m_distance[neighbor_id] = distance_through;
                    //followed by previous node on path
                    (*it).path = v;
                    //nodeArr[(*it).vertex].id = (*it).vertex;
                    que.push((*it));

                    //update log
                    log_on_nodes[neighbor_id -1].path =v;
                    log_on_nodes[neighbor_id -1].dist =distance_through;
                }
            }
        }
        
        cout << "\n";
        debug++;
	}
}

void Graph::printShortestPath()
{   
    cout << "v\t" << "known\t" << "dv\t" << "pv" << endl;
    for (Iter it = log_on_nodes.begin(); it!=log_on_nodes.end(); ++it) {
        //if(it->known) 
            cout << it->id <<"\t" << it->known << "\t" << it->dist << "\t" << it->path << endl;
    }

}

void Graph::print()
{
    int vertex_num =12;
    for(int i = 0 ; i < vertex_num; ++i){
        if(graph_list[i].begin() != graph_list[i].end()){
            for(list<Node>::iterator it = graph_list[i].begin(); it != graph_list[i].end(); ++it){
                cout << i << "-->";
                cout << (*it).id << "\tweight:" << (*it).dist << "\n";
            }
            cout << "NULL" << endl;
        }
    }
}






