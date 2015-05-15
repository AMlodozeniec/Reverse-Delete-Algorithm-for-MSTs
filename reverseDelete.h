#ifndef REVERSEDELETE_H
#define REVERSEDELETE_H

#include <vector>
#include <string>
#include <iostream>
#include <list>
using namespace std;


class GraphReverseDelete {
	
	public:
		struct Edge {
			int node1;
			int node2;
			int weight;
		};
		struct Vertex{
			int name;
			vector<Edge> adj;
		};
		GraphReverseDelete();
		~GraphReverseDelete();
		void insertEdge(int n1, int n2, int w);
		void insertVertex(int name);
		bool checkGraph(int name);
		void printVertices();
		void printEdgeList();
		void reverseDelete();
		void sortEdges();
	
	private:
		int E; //# of edges
		int V; //# of vertices
		void removeSwappedEdge(int node1, int node2);
		vector<Vertex> reverseDeleteGraph;
		Edge findSwapped(Edge v);
		vector<Edge> edgeList;
		bool BFS(Vertex node);
		void insertToAdjacencyList(int node, Edge e);
		void deleteEdgesFromAdjList(Edge e, Edge swappedE);
		Vertex findStartPoint(Edge e, Edge swappedE);
		int restoreEdge(Edge e, int index);
		void checkIfVisitedNode(bool visited[], Vertex v, list<Vertex> &queue);
		void findOutgoingVertices(list<Vertex> &queue, Vertex v, int index);
};

#endif
