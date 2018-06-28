#include "graphDijkstra.h"

// init the graph with adjacency lists (this is old way)
/*
Graph::Graph(char* graph[], int edgenum):nodeArr(MAX_VERTEX_NUM)
{
    edge_num =  edgenum; 
    vertex_num = 0;
    graph_list = new list<Node>[MAX_VERTEX_NUM+1];

    for(int i = 0; i < edgenum; ++i){
        addEdge(graph, i);   
    }


 
    //init to all the vertices
    for(int i = 0; i < MAX_VERTEX_NUM; ++i){
        nodeArr[i].known = false;
        nodeArr[i].dist = INFINITY;
        nodeArr[i].path = -1; //this node does not exist
    }
    vertex_num++;
}
*/

//dijkstra without using priority queue
void Graph::dijkstra(int src)
{
    /*
    for(int i = 0; i < vertex_num; ++i){
        nodeArr[i].known = false;
        nodeArr[i].dist = INFINITY;
        nodeArr[i].path = 0;
    }
    */

    nodeArr[src].dist = 0;
 
    for(; ;){
        //find all dist correspondence for all unvisited nodes
        int v = 0;
        int max = INFINITY;
        for(int i = 0; i < vertex_num; ++i){
            if(!nodeArr[i].known && (max > nodeArr[i].dist)){
                max = nodeArr[i].dist;
                v = i;
            }
        }

        //all vertices have been visited(relaxed), terminate dijkstra
        if(max == INFINITY)
            break;
 
        nodeArr[v].known = true;
        // update v's neighbors 
        for(list<Node>::iterator it = graph_list[v].begin(); it != graph_list[v].end(); ++it){
            if(!nodeArr[(*it).vertex].known){
                if(nodeArr[v].dist + (*it).weight < nodeArr[(*it).vertex].dist){
                    nodeArr[(*it).vertex].dist = nodeArr[v].dist + (*it).weight;
                    nodeArr[(*it).vertex].path = v;
                }
            }
        }
    }
}

/******************************************************************/
//init a node 
Node* Graph::InitNode(int edge_num, int id, int dist)
{
    Node *node(id);
    node->edge_num =edge_num;
    node->dist =dist;
    return node;
}

//add all adjacent edges to the correspondent vertex
void Graph::addEdge(char* graph[], int columns)
{
    Node node;
    vector<int> v = get_graph_value(graph, columns);
 
    node =InitNode(v[0], v[2], v[3]);
/*
    if(node.vertex > vertex_num)
        vertex_num = node.vertex;
*/
 
    int id =node.id;
    //reconsider all the deplicated edges,
    for(list<Node>::iterator it = graph_list[id].begin(); it != graph_list[id].end(); ++it){
        if((*it).id == id){
            if((*it).dist > node.dist){
                (*it).dist = node.dist;   
            }
            return;
        }
    }
 
    graph_list[id].push_back(node);
}

// read in all info of a graph, initiate it
Graph::Graph(char* graph[], int edgenum, int vertexnum)
{
    //one time initiation
    int vertex_num =vertexnum;
    int edge_num =edgenum;
    graph_list = new list<Node>[MAX_VERTEX_NUM+1];

    for(int i = 0; i < edgenum; ++i){
        addEdge(graph, i);   
    }

    //init to all the vertices
    for(int i = 0; i < MAX_VERTEX_NUM; ++i){
        for(Node &n :graph_list[i]){
            n.id =i; // add identity to this node

            n.known = false;
            n.dist = INFINITY;
            n.path = -1; // this node does not exist
        }
    }
}
  
//release dynamic memory
Graph::~Graph()
{
    delete[] graph_list;
}
 
//dijkstra with using priority queue
void Graph::dijkstra_stl_pq(int src): min_distance(MAX_VERTEX_NUM)
{
    int edgenum =0;
	// init position to be added at the front of queue (starting dijkstra)
	Node front =InitNode(src, edgenum, INFINITY);
	//Node front =graph_list[src];
	priority_queue<Node> que;
    min_distance[src] = 0;

	// init the queue with the source
	que.push(front);

	while(!que.empty()){
		Node front =que.top();
		que.pop();
		int v =front.id;

		// Because we leave old copies of the vertex in the priority queue
	    // (with outdated higher distances), we need to ignore it when we come
	    // across it again, by checking its distance against the minimum distance
		if (min_distance[v].dist < front.dist) 
			continue;

		front.known = true;

		// update front's neighbors
		for(list<Node>::iterator it = graph_list[v].begin(); it != graph_list[v].end(); ++it){
            if(!(*it).known){
                // small n stands for neighbor
                int distance_through_n =front.dist +(*it).dist;
                int neighbor_id =(*it).id;
                if(distance_through_n < min_distance[neighbor_id]){
                    min_distance[neighbor_id] = distance_through_n;
                    (*it).path = v;
                    //nodeArr[(*it).vertex].id = (*it).vertex;
                    que.push((*it));
                }
            }
        }
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

void Graph::printShorestPath()
{
    cout << "Node\t" << "known\t" << "dist\t" << "path" << endl;
    /*
    for(int i = 0; i < vertex_num; ++i){
        if(nodeArr[i].known)
            cout << i << "\t" << nodeArr[i].known << "\t" << nodeArr[i].dist << "\t" << nodeArr[i].path << endl;
    } 
    */

    for(Node &n :graph_list[i]){
        if(n.known) 
            cout << i << "\t" << nodeArr[i].known << "\t" << nodeArr[i].dist << "\t" << nodeArr[i].path << endl;
    }
}

void Graph::print()
{
    for(int i = 0 ; i < vertex_num; ++i){
        if(graph_list[i].begin() != graph_list[i].end()){
            cout << i << "-->";
            for(list<Node>::iterator it = graph_list[i].begin(); it != graph_list[i].end(); ++it){
                cout << (*it).id << "(edge id:" << (*it).edge_num << ",weight:" << (*it).dist << ")-->";
            }
            cout << "NULL" << endl;
        }
    }
}






