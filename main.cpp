#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "reverseDelete.h"
using namespace std;

int main(int argc, char ** argv){

	ifstream edgeFile;
	GraphReverseDelete reverseGraph;
	if (argc == 2){
		
		edgeFile.open(argv[1]);
		if (!edgeFile.is_open()){
			perror("Could not open edge file correctly.");
			return 0;
		}

	} else {
		cout << "Usage: <input-file>" << endl;
		return 0;
	}
	int n1, n2, w;
	while(edgeFile >> n1 >> n2 >> w){
		if(!reverseGraph.checkGraph(n1)){
			reverseGraph.insertVertex(n1);
		}
		reverseGraph.insertEdge(n1, n2, w);
		if(!reverseGraph.checkGraph(n2)){
			reverseGraph.insertVertex(n2);
		}
		reverseGraph.insertEdge(n2,n1,w);
	}
	reverseGraph.sortEdges();
	//reverseGraph.printEdgeList();
	//reverseGraph.printVertices();
	reverseGraph.reverseDelete();
}
