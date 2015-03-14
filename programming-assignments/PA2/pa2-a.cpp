#include <iostream>
#include <string>
#include <map>

using namespace std;

void printMap(map<string, map<string, int> > nodes) {
    cout << "start ------" << endl;

    map<string, map<string, int> >::reverse_iterator rit;
    for (rit=nodes.rbegin(); rit!=nodes.rend(); ++rit) {
        cout << rit->first << " => length: " << rit->second.size() << '\n' << endl;
        
        map<string, int>::reverse_iterator rit2;
        
        for (rit2=rit->second.rbegin(); rit2!=rit->second.rend(); ++rit2) {
            cout << "    " << rit2->first << " => " << rit2->second << '\n' << endl;
        }
    }

    cout << "end ------" << endl;
}

void verifyHamiltonianPath() {
    unsigned int N(0), M(0);
    cin >> N >> M;
    // cout << "N: " << N << ", M: " << M << endl;
    map<string, map<string, int> > nodes;
    map<string, bool> graphNodes;

    for (unsigned int j = 0; j < M; j++) {
        string srcNode, dstNode;
        cin >> srcNode >> dstNode;
        if (nodes.find(srcNode) == nodes.end()) {
            map<string, int> connectedNodes;
            nodes[srcNode] = connectedNodes;
            nodes[srcNode][dstNode] = 0;
        }
        nodes[srcNode][dstNode] += 1;
        graphNodes[srcNode] = true;

        if (nodes.find(dstNode) == nodes.end()) {
            map<string, int> connectedNodes;
            nodes[dstNode] = connectedNodes;
            nodes[dstNode][srcNode] = 0;
        } 
        nodes[dstNode][srcNode] += 1;
        graphNodes[dstNode] = true;
        // cout << "Src: " << srcNode << ", Dst: " << dstNode << endl; 
    }

    unsigned int P;
    bool isHamiltonianPath = true;
    cin >> P;
    string startNode, pathNode, prevNode;
    map<string, bool> uniquePathNodes;
    string * pathNodesArray = new string[P];

    for (unsigned int j = 0; j < P; j++) { 
        cin >> pathNodesArray[j];
    }

    for (unsigned int j = 0; j < P; j++) { 
        pathNode = pathNodesArray[j];
        if (j == 0) {
            if (nodes.find(pathNode) == nodes.end()) {
                isHamiltonianPath = false;
                break;
            } else {
                startNode = pathNode;
            }
        } else {
            // cout << "Src:" << prevNode << ", Dst: " << pathNode << endl;
            if (nodes.find(pathNode) == nodes.end() ||
                nodes.find(prevNode) == nodes.end() ||
                nodes[prevNode][pathNode] == 0 || 
                nodes[pathNode][prevNode] == 0) {
                nodes[prevNode][pathNode] = false;
                nodes[pathNode][prevNode] = false;
                // cout << nodes[prevNode][pathNode] << ", " << nodes[pathNode][prevNode] << endl;
                // cout << "Cannot find ^ edge!" << endl;
                isHamiltonianPath = false;
                break;
            }
            nodes[prevNode][pathNode] -= 1;
            nodes[pathNode][prevNode] -= 1;
        }
        uniquePathNodes[pathNode] = true;
        prevNode = pathNode;
    }

    if (startNode != prevNode || 
        uniquePathNodes.size() != P-1 || 
        uniquePathNodes != graphNodes ||
        uniquePathNodes.size() != graphNodes.size() ||
        N != P-1 ||
        N != graphNodes.size()) {
        //  1. Must start and end at the same node
        //  2. Path nodes must be unique
        //  3. Path nodes must have same nodes as G
        //  4. Path nodes must have same number of nodes as G
        //  5. Given number of nodes should be same as number of nodes in G
        isHamiltonianPath = false;
    }

    map<string, bool>::reverse_iterator rit;

    for (rit = graphNodes.rbegin(); rit != graphNodes.rend(); ++rit) {
        if (!uniquePathNodes[rit->first]) {
            isHamiltonianPath = false;
        }
    }

    for (rit = uniquePathNodes.rbegin(); rit != uniquePathNodes.rend(); ++rit) {
        if (!graphNodes[rit->first]) {
            isHamiltonianPath = false;
        }
    }

    cout << (isHamiltonianPath ? "YES" : "NO") << endl;

    delete [] pathNodesArray;
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        // cout << endl << "Block " << i << endl;
        verifyHamiltonianPath();        
    }

    return 0;
}
