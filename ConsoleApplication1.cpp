#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <limits>

using namespace std;


unordered_map<int, int> shortest_distance(int numVertices, int startNode, const unordered_map<int, vector<int>>& edges) {
    unordered_map<int, int> distances;
    
    for (int i = 0; i < numVertices; i++) {
        distances[i] = (i == startNode) ? 0 : numeric_limits<int>::max();
    }

    deque<int> q;
    q.push_back(startNode);

    while (!q.empty()) {
        int v = q.front();
        q.pop_front();

        for (const auto& pair : edges) {
            if (pair.first == v) { 
                for (int u : pair.second) {
                    if (distances[u] > distances[v] + 1) {
                        distances[u] = distances[v] + 1;
                        q.push_back(u);
                    }
                }
            }

            for (int u : pair.second) {
                if (u == v && distances[pair.first] > distances[v] + 1) {
                    distances[pair.first] = distances[v] + 1;
                    q.push_back(pair.first);
                }
            }
        }

    }

    return(distances);
}

int main()
{
    setlocale(LC_ALL, "rus");
    ifstream graph_file("graph.txt");

    if (!graph_file.is_open()) {
        cout << "Ошибка при открытии файла\n";
    }

    int numVertices, numEdges;
    graph_file >> numVertices >> numEdges;

    unordered_map<int, vector<int>> edges(numEdges);
    unordered_map<int, vector<int>>::iterator it;

    for (int i = 0; i < numEdges; i++) {
        int from, to;
        graph_file >> from >> to;

        edges[from].push_back(to);
    }

    int startNode;
    graph_file >> startNode;
    graph_file.close();

    unordered_map<int, int> distances = shortest_distance(numVertices, startNode, edges);

    for (int i = 0; i < numVertices; i++) {
        if (distances.find(i) != distances.end()) {
            cout << i << " " << distances[i] << "\n";
        }
    }
}

