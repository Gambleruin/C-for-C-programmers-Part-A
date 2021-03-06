#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/timeb.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "graphDijkstra.h"
 
#define MAX_LINE_LEN 4000
 
int read_file(char ** const buff, const unsigned int spec, const char * const filename);
void release_buff(char ** const buff, const int valid_item_num);
 
int main(int argc, char *argv[])
{
    char *topo[5000];
    int edge_num;
    char *demand;
    int demand_num;
 
    char *topo_file = argv[1];
    edge_num = read_file(topo, 5000, topo_file);
    printf("the number of edges is %d\n", edge_num);
    if (edge_num == 0)
    {
        printf("Please input valid topo file.\n");
        return -1;
    }
 
    int src;
    cout << "enter the source：";
    cin >> src;
 
    Graph G(topo, edge_num);
    //G.print();
    
    cout << "Dijkstra: " << endl;
    G.Log(src);
    G.dijkstra(src);
    //G.printShorestPath();
 
    release_buff(topo, edge_num);
	return 0;
}

int read_file(char ** const buff, const unsigned int spec, const char * const filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Fail to open file %s, %s.\n", filename, strerror(errno));
        return 0;
    }
    printf("Open file %s OK.\n", filename);
 
    char line[MAX_LINE_LEN + 2];
    unsigned int cnt = 0;
    while ((cnt < spec) && !feof(fp))
    {
        line[0] = 0;
        fgets(line, MAX_LINE_LEN + 2, fp);
        if (line[0] == 0)   continue;
        buff[cnt] = (char *)malloc(MAX_LINE_LEN + 2);
        strncpy(buff[cnt], line, MAX_LINE_LEN + 2 - 1);
        buff[cnt][4001] = 0;
        cnt++;
    }
    fclose(fp);
    printf("There are %d lines in file %s.\n", cnt, filename);
 
    return cnt;
}
 
//release buff
void release_buff(char ** const buff, const int valid_item_num)
{
    for (int i = 0; i < valid_item_num; i++)
        free(buff[i]);
}
 

