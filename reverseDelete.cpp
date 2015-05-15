#include "reverseDelete.h"
#include <iostream>
using namespace std;


//constructor
GraphReverseDelete::GraphReverseDelete() { 
	V = 0;
	E = 0;
}

//destructor
GraphReverseDelete::~GraphReverseDelete() {}

// Inserts an edge with a starting node, an ending node, and a weight
//into the node that has its name that matches with the outgoing node (n1)
void GraphReverseDelete::insertEdge(int n1, int n2, int w){
	Edge e;
	e.node1 = n1;
	e.node2 = n2;
	e.weight = w;
	E++;
	int j = 0;
	edgeList.push_back(e);
	removeSwappedEdge(n1,n2);
	insertToAdjacencyList(n1, e);
}

//Inserts edge into vertex's adjacency list
void GraphReverseDelete::insertToAdjacencyList(int node, Edge e){
	int i = 0;
	while(i < reverseDeleteGraph.size()){
		if(reverseDeleteGraph[i].name == node){
			reverseDeleteGraph[i].adj.push_back(e);
			return;
		}
		i++;
	}
}

//Removes copy of swapped edge
void GraphReverseDelete::removeSwappedEdge(int node1, int node2){
	int i = 0;
	while(i < edgeList.size()){
		if(edgeList[i].node1 == node2 && edgeList[i].node2 == node1){
			edgeList.pop_back();
			break;
		}
		i++;
	}
}

//Inserts vertex with its name into the graph. Also, increments # of vertices
void GraphReverseDelete::insertVertex(int name){
	Vertex v;
	v.name = name;
	reverseDeleteGraph.push_back(v);
	V++;
}

//Checks if graph has vertex in it already. If it does return true
bool GraphReverseDelete::checkGraph(int name){
	int i = 0;
	while(i < reverseDeleteGraph.size()){
		if(reverseDeleteGraph[i].name == name){
			return true;
		}
		i++;
	} 
	return false;
}

//Prints all edges of the graph
void GraphReverseDelete::printEdgeList(){
	//cout << "-PRINTING EDGELIST-" << endl;
	for(int i = 0; i < edgeList.size(); i++){
		cout <<  edgeList[i].node1 << " " << edgeList[i].node2 << " " << edgeList[i].weight << endl;
	}
}


//Sorts the edges in non-decreasing order
void GraphReverseDelete::sortEdges(){
	for(int i = 0; i < edgeList.size(); i++){
		Edge e = edgeList[i];
		int j = i;
		while(j > 0 && edgeList[j - 1].weight < e.weight){
			edgeList[j] = edgeList[j-1];
			j--;
		}
		edgeList[j] = e;
	}
	//printEdgeList();
}

//Finds the same edge with its swapped vertex names
GraphReverseDelete::Edge GraphReverseDelete::findSwapped(Edge v){
	Edge swapped;
	swapped.node1 = v.node2;
	swapped.node2 = v.node1;
	swapped.weight = v.weight;
	return swapped;
}

//Finds edge and swapped edge in graph and deletes it from vertex's adjacency list
void GraphReverseDelete::deleteEdgesFromAdjList(Edge e, Edge swappedE){
	int i = 0;
	while(i < reverseDeleteGraph.size()){
		Vertex v = reverseDeleteGraph[i];
		for(int j = 0; j < v.adj.size(); j++){
			Edge vertexEdge = v.adj[j];
			if(vertexEdge.node1 == e.node1 && vertexEdge.node2 == e.node2 && vertexEdge.weight == e.weight || 
				vertexEdge.node1 == swappedE.node1 && vertexEdge.node2 == swappedE.node2 && vertexEdge.weight == swappedE.weight){
				reverseDeleteGraph[i].adj.erase(reverseDeleteGraph[i].adj.begin() + j);
				break;
			}
		}
		i++;
	}
}

//Finds node to begin Breadth First Search from
GraphReverseDelete::Vertex GraphReverseDelete::findStartPoint(Edge e, Edge swappedE){
	Vertex node;
	int i = 0;
	while(i < reverseDeleteGraph.size()){
		node = reverseDeleteGraph[i];
		if(node.name == e.node1 || node.name == swappedE.node1){
			return node;
		}
		i++;
	}
}

//Restores edge to edgelist nd the edge to the vertices that use it
int GraphReverseDelete::restoreEdge(Edge e, int index){
	edgeList.insert(edgeList.begin() + index, e);
	int i = 0;
	insertToAdjacencyList(e.node1, e);
	insertToAdjacencyList(e.node2, e);
	index++;
	
	
	return index;
}

//Deletes edges from highest weight to lowest weight. Checks if deleting
//that node makes it disjoint, and if so, restore it. Eventually, will create
//an optimal Minimal Spanning Tree
void GraphReverseDelete::reverseDelete(){
	int edgeListSize = edgeList.size();
	int vertexSize = reverseDeleteGraph.size();
	int i = 0;
	while (i < edgeListSize){
		edgeListSize = edgeList.size();
		Edge e = edgeList[0 + i];
		Edge swappedE = findSwapped(e);
		deleteEdgesFromAdjList(e, swappedE);
		Vertex node;
		node = findStartPoint(e, swappedE);
		edgeList.erase(edgeList.begin() + i);
		if(!(BFS(node))){
			i = restoreEdge(e, i);
		}
	}
	printEdgeList();
}


/*Searches through the node and returns true if it has reached
all nodes in the vertices vector, thereby making sure deleting the node
doesn't make the graph disjoint
*/
bool GraphReverseDelete::BFS(Vertex node){
	bool *visited = new bool[V+1];
	for(int i = 0; i < V; i++){
		visited[i] = false;
	}
	
	list<Vertex> queue;
	
	visited[node.name] = true;
	queue.push_back(node);
	while(!queue.empty()){
		Vertex v = queue.front();
		queue.pop_front();
		checkIfVisitedNode(visited, v, queue);
	}
	
	for(int i = 0; i < V; i++){
		if(!visited[i]){
			return false;
		}
	}
	return true;
}

void GraphReverseDelete::checkIfVisitedNode(bool visited[], Vertex v, list<Vertex> &queue){
	for(int i = 0; i < v.adj.size(); i++){
		if(visited[v.adj[i].node2] == false){
			visited[v.adj[i].node2] = true;
			findOutgoingVertices(queue, v, i);
		}
	}
	
}

void GraphReverseDelete::findOutgoingVertices(list<Vertex> &queue, Vertex v, int index){
	int i = 0;
	while(i < reverseDeleteGraph.size()){
		if(reverseDeleteGraph[i].name == v.adj[index].node2){
			queue.push_back(reverseDeleteGraph[i]);
			return;
		}
		i++;
	}
}

//Prints all vertices including 
void GraphReverseDelete::printVertices(){
	//cout << "-PRINTING VERTICES-" << endl;
	for(int i = 0; i < reverseDeleteGraph.size(); i++){
		Vertex v = reverseDeleteGraph[i];
		//cout << "V1: " << v.name << endl;
	}
}

