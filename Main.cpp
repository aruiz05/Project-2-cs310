#include <climits>
#include <iostream>

using namespace std;

int getMinimumUnvisitedVertex(int* distances, bool* visited, int numOfVertices){
    int minDistance = INT_MAX;
    int minIndex = -1;

    // find unvisited vertex with the smallest distance
    for(int i = 1; i <= numOfVertices; i++){
        if(!visited[i] && distances[i] < minDistance){
            minDistance = distances[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void runDijkstra(int** adjacencyMatrix, int numOfVertices, int source){
    int* distances = new int[numOfVertices + 1];
    bool* visited = new bool[numOfVertices + 1];

    // start every distance as unknown and every vertex as unvisited
    for(int i = 1; i <= numOfVertices; i++){
        distances[i] = INT_MAX;
        visited[i] = false;
    }

    // distance from source node to itself is always 0
    distances[source] = 0;

    for(int i = 1; i <= numOfVertices; i++){
        int current = getMinimumUnvisitedVertex(distances, visited, numOfVertices);

        if(current == -1){
            break;
        }

        visited[current] = true;

        // check all possible neighbors in matrix
        for(int neighbor = 1; neighbor <= numOfVertices; neighbor++){
            int weight = adjacencyMatrix[current][neighbor];

            // relax edge if going through current is shorter
            if(weight > 0 && !visited[neighbor] && distances[current] != INT_MAX){
                int newDistance = distances[current] + weight;

                if(newDistance < distances[neighbor]){
                    // only distance is updated because printing lengths not paths
                    distances[neighbor] = newDistance;
                }
            }
        }
    }

    cout << "The shortest path lengths from Node " << source
         << " to all other nodes are:" << endl;

    // print final shortest distance from source to each node
    for(int i = 1; i <= numOfVertices; i++){
        cout << i << ": " << distances[i] << endl;
    }

    delete[] distances;
    delete[] visited;
}

int main(){
    int numOfVertices;
    int numOfEdges;

    if(!(cin >> numOfVertices >> numOfEdges)){
        cout << "Input not found!" << endl;
        return 0;
    }

    int** adjacencyMatrix = new int*[numOfVertices + 1];

    // build empty matrix, 0 = no edge between two nodes
    for(int i = 0; i <= numOfVertices; i++){
        adjacencyMatrix[i] = new int[numOfVertices + 1];

        for(int j = 0; j <= numOfVertices; j++){
            adjacencyMatrix[i][j] = 0;
        }
    }

    int* degrees = new int[numOfVertices + 1];

    for(int i = 0; i <= numOfVertices; i++){
        degrees[i] = 0;
    }

    for(int i = 0; i < numOfEdges; i++){
        int startVertex;
        int endVertex;
        int weight;

        cin >> startVertex >> endVertex >> weight;

        // store each undirected edge in both directions
        adjacencyMatrix[startVertex][endVertex] = weight;
        adjacencyMatrix[endVertex][startVertex] = weight;
        degrees[startVertex]++;
        degrees[endVertex]++;
    }

    cout << "The adjacency matrix of G is:" << endl;

    for(int i = 1; i <= numOfVertices; i++){
        for(int j = 1; j <= numOfVertices; j++){
            cout << adjacencyMatrix[i][j];

            if(j < numOfVertices){
                cout << " ";
            }
        }

        cout << endl;
    }

    cout << "The nodes with odd degrees in G are:" << endl;
    cout << "O = {";

    // vertices are checked in order so odd degree list is sorted
    for(int i = 1; i <= numOfVertices; i++){
        if(degrees[i] % 2 == 1){
            cout << " " << i;
        }
    }

    cout << " }" << endl;

    // run dijkstra once for ach odd degree node
    for(int i = 1; i <= numOfVertices; i++){
        if(degrees[i] % 2 == 1){
            runDijkstra(adjacencyMatrix, numOfVertices, i);
        }
    }

    for(int i = 0; i <= numOfVertices; i++){
        delete[] adjacencyMatrix[i];
    }

    delete[] adjacencyMatrix;
    delete[] degrees;

    return 0;
}
