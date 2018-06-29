#include "graphDijkstra.h"

using Iter = std::vector<int>::const_iterator;
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
/*
    for(int i = 0; i < 10; ++i){
        for(Node &n :graph_list[i]){
            
        }
    }
*/
}

//release dynamic memory
Graph::~Graph()
{
    delete[] graph_list;
}

//dijkstra with using priority queue
void Graph::dijkstra(int src)
{
    int edgenum =0;
	// Init position to be added at the front of queue (starting dijkstra)
	Node front =Init(src, src, 0);
	// check the logic of priority queue, making sure that it is right
	priority_queue<Node> que;
    vector<int> m_distance(10);
    fill(m_distance.begin(), m_distance.end(), INFINITY);

    m_distance[src]= 0;

	// init the queue with the source
	que.push(front);
	while(!que.empty()){
		Node front =que.top();
		que.pop();
		int v =front.id;
		// Because we leave old copies of the vertex in the priority queue
	    // (with outdated higher distances), we need to ignore it when we come
	    // across it again, by checking its distance against the minimum distance
		if (m_distance[v] < front.dist) 
			continue;

		front.known = true;
		// update front's neighbors
		for(list<Node>::iterator it = graph_list[v].begin(); it != graph_list[v].end(); ++it){
            if(!(*it).known){
                // small n stands for neighbor
                int distance_through_n =front.dist +(*it).dist;
                int neighbor_id =(*it).id;
                if(distance_through_n < m_distance[neighbor_id]){
                    m_distance[neighbor_id] = distance_through_n;
                    //followed by previous node on path
                    (*it).path = v;
                    //nodeArr[(*it).vertex].id = (*it).vertex;
                    que.push((*it));
                }
            }
        }
	}
}

void Graph::printShorestPath()
{
    cout << "Node\t" << "known\t" << "dist\t" << "path" << endl;
    int i=0;
    for(Node &n :graph_list[i]){
        printf("was I being here? ");
        if(n.known) 
            cout << i <<"\t" << n.known << "\t" << n.dist << "\t" << n.path << endl;
    }
}

void Graph::print()
{
    for(int i = 0 ; i < vertex_num; ++i){
        if(graph_list[i].begin() != graph_list[i].end()){
            cout << i << "-->";
            for(list<Node>::iterator it = graph_list[i].begin(); it != graph_list[i].end(); ++it){
                cout << (*it).id << "weight:" << (*it).dist << "-->";
            }
            cout << "NULL" << endl;
        }
    }
}






