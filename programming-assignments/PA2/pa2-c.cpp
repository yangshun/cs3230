#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <list>

using namespace std;

void printGraph(map<string, map<string, bool> > &graph) {

    map<string, bool> edges;

    map<string, map<string, bool> >::reverse_iterator rit;
    for (rit = graph.rbegin(); rit != graph.rend(); ++rit) {
        map<string, bool>::reverse_iterator rit2;
        for (rit2 = rit->second.rbegin(); rit2 != rit->second.rend(); ++rit2) {
            edges[rit->first + " " + rit2->first] = true;
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

    cout << graph.size() << " " << SIZE << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << edgesArray[i] << endl;
    }

}

void addNode(map<string, map<string, bool> > &graph, string src, string dst) {
    if (graph.find(src) == graph.end()) {
        map<string, bool> dstNodes;
        graph[src] = dstNodes;
    }
    graph[src][dst] = true;
}

string N2S(int number) {
    stringstream ss;
    ss << number;
    return ss.str();
}


void reduceGraph() {
    int N(0), K(0);

    cin >> N >> K;
    string clauses[100][3];
    
    for (int i = 0; i < K; i++) {
        cin >> clauses[i][0] >> clauses[i][1] >> clauses[i][2];
    }

    map<string, map<string, bool> > graph;
    addNode(graph, "T", "S");
    addNode(graph, "S", "L1");
    addNode(graph, "S", "R1");
    addNode(graph, "L" + N2S(N), "T");
    addNode(graph, "R" + N2S(N), "T");
    for (int i = 1; i < N; i++) {
        addNode(graph, "L" + N2S(i), "L" + N2S(i+1));
        addNode(graph, "L" + N2S(i), "R" + N2S(i+1));
        addNode(graph, "R" + N2S(i), "R" + N2S(i+1));
        addNode(graph, "R" + N2S(i), "L" + N2S(i+1));
    }

    for (int i = 1; i <= N; i++) {
        list<string> nodesList;
        nodesList.push_back("L" + N2S(i));
        nodesList.push_back("B" + N2S(i) + "." + N2S(0));
        for (int j = 1; j <= K; j++) {
            nodesList.push_back("X" + N2S(i) + "." + N2S(j) + ".L");
            nodesList.push_back("X" + N2S(i) + "." + N2S(j) + ".R");
            nodesList.push_back("B" + N2S(i) + "." + N2S(j));
        }
        nodesList.push_back("R" + N2S(i));

        list<string>::iterator back = nodesList.begin();
        list<string>::iterator front = nodesList.begin();
        front++;

        while (front != nodesList.end()) {
            addNode(graph, *back, *front);
            addNode(graph, *front, *back);
            back++;
            front++;
        }
    }

    for (int i = 0; i < K; i++) {
        string clauseNode = "C" + N2S(i+1);
        for (int j = 0; j < 3; j++) {
            string literal = clauses[i][j];
            bool isNegation = literal[0] == '-';
            if (isNegation) {
                literal = literal.substr(1);
                addNode(graph, "X" + literal + "." + N2S(i+1) + ".R", clauseNode);
                addNode(graph, clauseNode, "X" + literal + "." + N2S(i+1) + ".L");
            } else {
                addNode(graph, "X" + literal + "." + N2S(i+1) + ".L", clauseNode);
                addNode(graph, clauseNode, "X" + literal + "." + N2S(i+1) + ".R");
            }
            
        }
    }

    printGraph(graph);
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        reduceGraph();        
    }

    return 0;
}
