#include "graphDijkstra.h"

void Graph::dijkstra(int src)
{
    //init
    for(int i = 0; i < vertex_num; ++i){
        nodeArr[i].known = false;
        nodeArr[i].dist = INFINITY;
        nodeArr[i].path = 0;
    }

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
        //update v's neighbors 
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

void Graph::printShorestPath()
{
    cout << "Node\t" << "known\t" << "dist\t" << "path" << endl;
    for(int i = 0; i < vertex_num; ++i){
        if(nodeArr[i].known)
            cout << i << "\t" << nodeArr[i].known << "\t" << nodeArr[i].dist << "\t" << nodeArr[i].path << endl;
    } 
}

void Graph::print()
{
    for(int i = 0 ; i < vertex_num; ++i){
        if(graph_list[i].begin() != graph_list[i].end()){
            cout << i << "-->";
            for(list<Node>::iterator it = graph_list[i].begin(); it != graph_list[i].end(); ++it){
                cout << (*it).vertex << "(边号:" << (*it).edge_num << ",权重:" << (*it).weight << ")-->";
            }
            cout << "NULL" << endl;
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

//add all edges to graph 
void Graph::addEdge(char* graph[], int columns)
{
    Node node;
    vector<int> v = get_graph_value(graph, columns);
 
    node.edge_num = v[0];
    node.src = v[1];
    node.vertex = v[2];
    node.weight = v[3];

    if(node.vertex > vertex_num)
        vertex_num = node.vertex;
 
    //reconsider all the deplicated edges
    for(list<Node>::iterator it = graph_list[node.src].begin(); it != graph_list[node.src].end(); ++it){
        if((*it).vertex == node.vertex){
            if((*it).weight > node.weight){
                (*it).weight = node.weight;   
            }
            return;
        }
    }
 
    graph_list[node.src].push_back(node);
}
 
 
// init the graph with adjacency lists
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
 
 
//release dynamic memory
Graph::~Graph()
{
    delete[] graph_list;
}
 




