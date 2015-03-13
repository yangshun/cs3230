#include <iostream>
#include <string>
#include <map>

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

void verifyHamiltonianPath() {
    unsigned int N(0), M(0);
    cin >> N >> M;
    cout << "N: " << N << ", M: " << M << endl;
    map<string, map<string, bool> > nodes;

    for (unsigned int j = 0; j < M; j++) {
        string srcNode, dstNode;
        cin >> srcNode >> dstNode;
        if (nodes.find(srcNode) == nodes.end()) {
            map<string, bool> connectedNodes;
            nodes[srcNode] = connectedNodes;
        }
        nodes[srcNode][dstNode] = true;

        if (nodes.find(dstNode) == nodes.end()) {
            map<string, bool> connectedNodes;
            nodes[dstNode] = connectedNodes;
        } 
        nodes[dstNode][srcNode] = true;
        cout << "Src: " << srcNode << ", Dst: " << dstNode << endl; 
    }

    unsigned int P;
    bool isHamiltonianPath = true;
    cin >> P;
    cout << "P: " << P << endl;
    string startNode, pathNode, prevNode;
    map<string, bool> pathNodes;

    for (unsigned int j = 0; j < P; j++) { 
        cin >> pathNode;
        if (j == 0) {
            if (nodes.find(pathNode) == nodes.end()) {
                isHamiltonianPath = false;
                break;
            } else {
                startNode = pathNode;
            }
        } else {
            if (nodes.find(pathNode) == nodes.end() ||
                nodes.find(prevNode) == nodes.end() ||
                !nodes[prevNode][pathNode] || 
                !nodes[pathNode][prevNode]) {
                // cout << prevNode << "," << pathNode << endl;
                nodes[prevNode][pathNode] = false;
                nodes[pathNode][prevNode] = false;
                isHamiltonianPath = false;
                break;
            }
        }
        pathNodes[pathNode] = true;
        prevNode = pathNode;
    }

    if (startNode != prevNode || 
        pathNodes.size() != P-1 || 
        pathNodes.size() != nodes.size()) {
        // 1. Must start and end at the same node
        // 2. Path nodes must be unique
        // 3. Path nodes must have same number of nodes as G
        isHamiltonianPath = false;
    }

    cout << (isHamiltonianPath ? "YES" : "NO") << endl;
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        cout << endl << "Block " << i << endl;
        verifyHamiltonianPath();        
    }

    return 0;
}
