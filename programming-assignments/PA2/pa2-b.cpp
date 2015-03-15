#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

void printMap(map<string, map<string, bool> > nodes) {
    cout << "start ------" << endl;

    map<string, map<string, bool> >::reverse_iterator rit;
    for (rit=nodes.rbegin(); rit!=nodes.rend(); ++rit) {
        cout << rit->first << " => length: " << rit->second.size() << '\n' << endl;
        
        map<string, bool>::reverse_iterator rit2;
        
        for (rit2=rit->second.rbegin(); rit2!=rit->second.rend(); ++rit2) {
            cout << "    " << rit2->first << " => " << rit2->second << '\n' << endl;
        }
    }

    cout << "end ------" << endl;
}

string getNodePartFromNode(string node, string type) {
    return type + node.substr(1);
}

void createNewNode(map<string, map<string, bool> > &nodes, string node) {
    map<string, bool> vertexConnectedNodes;
    nodes[node] = vertexConnectedNodes;

    map<string, bool> headConnectedNodes;
    string headNode = getNodePartFromNode(node, "H");
    nodes[headNode] = headConnectedNodes;

    nodes[node][headNode] = true;
    nodes[headNode][node] = true;

    map<string, bool> tailConnectedNodes;
    string tailNode = getNodePartFromNode(node, "T");
    nodes[tailNode] = tailConnectedNodes;

    nodes[node][tailNode] = true;
    nodes[tailNode][node] = true;
}

string stringRepOfEdge(string srcNode, string dstNode) {
    return srcNode < dstNode ? (srcNode + " " + dstNode) : (dstNode + " " + srcNode);
}

void printGraph(map<string, map<string, bool> > &nodes) {

    map<string, bool> edges;

    map<string, map<string, bool> >::reverse_iterator rit;
    for (rit = nodes.rbegin(); rit != nodes.rend(); ++rit) {
        map<string, bool>::reverse_iterator rit2;
        for (rit2 = rit->second.rbegin(); rit2 != rit->second.rend(); ++rit2) {
            edges[stringRepOfEdge(rit->first, rit2->first)] = true;
        }
    }

    unsigned int SIZE = edges.size();
    string * edgesArray = new string[SIZE];
    map<string, bool>::reverse_iterator rit3;
    
    int i = 0;
    for (rit3 = edges.rbegin(); rit3 != edges.rend(); ++rit3, ++i) {
        edgesArray[i] = rit3->first;
    }

    sort(edgesArray, edgesArray + SIZE);

    cout << nodes.size() << " " << SIZE << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << edgesArray[i] << endl;
    }

}

void reduceGraph() {
    unsigned int N(0), M(0);
    cin >> N >> M;
    map<string, map<string, bool> > nodes;

    for (unsigned int j = 0; j < M; j++) {
        string srcNode, dstNode;
        cin >> srcNode >> dstNode;
        if (nodes.find(srcNode) == nodes.end()) {
            createNewNode(nodes, srcNode);
        }
        
        if (nodes.find(dstNode) == nodes.end()) {
            createNewNode(nodes, dstNode);
        }

        string srcHeadNode = getNodePartFromNode(srcNode, "H");
        string dstTailNode = getNodePartFromNode(dstNode, "T");
        
        nodes[srcHeadNode][dstTailNode] = true;
        nodes[dstTailNode][srcHeadNode] = true;
    }

    printGraph(nodes);

}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        reduceGraph();        
    }

    return 0;
}
