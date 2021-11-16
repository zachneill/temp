#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

#define HIGH 1e6

/**
 * TODO: Define any structs you might need here.
 */
struct Node {
    int parentIdx; 
    float dist;
    float dist; 
    bool visited;
    bool queued;
    int parent;
};
struct Graph
{
    std::vector<std::string> data;
    std::vector<std::vector<int> > edges;
    std::vector<std::vector<float> > edge_costs;
    // TODO: Add any members you need to the graph.
    std::vector<float> dists; 
    std::vector<int> neighbors;
    std::vector<Node> node_vec;
    int currentIdx;
};

/**
 * Function definitions.
 */
int nameToIdx(std::string name, std::vector<std::string>& v);
Graph createGraph(std::string file_path);
std::vector<int> tracePath(int n, Graph& g);
void printPath(std::vector<int>& path, Graph& g);
std::vector<int> getNeighbors(int n, Graph& g);
std::vector<float> getEdgeCosts(int n, Graph& g);
int getParent(int n, Graph& g, Node& node);
void initGraph(Graph& g);
std::vector<int> bfs(int start, int goal, Graph& g, Node& n);

/**
 * Function implementations.
 */

int nameToIdx(std::string name, std::vector<std::string>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == name) return i;
    }
    return -1;
}
Node createNode(){
    Node n;
    return n;
}
Graph createGraph(std::string file_path)
{
    Graph g;
    std::ifstream in(file_path);
    if (!in.is_open())
    {
        std::cerr << "ERROR: Failed to load graph from " << file_path << std::endl;
        return g;
    }

    std::string s = "";
    int N = 0;
    while (s != "NODES") in >> s >> N;

    for (int i = 0; i < N; i++)
    {
        in >> s;
        g.data.push_back(s);
    }

    g.edges = std::vector<std::vector<int> >(N, std::vector<int>());
    g.edge_costs = std::vector<std::vector<float> >(N, std::vector<float>());
    g.dists = std::vector<float>(N, 10000);
    while (s != "EDGES") in >> s >> N;

    std::string city1, city2;
    float dist;
    for (int i = 0; i < N; i++)
    {
        in >> city1 >> city2 >> dist;
        int c1 = nameToIdx(city1, g.data);
        int c2 = nameToIdx(city2, g.data);
        g.edges[c1].push_back(c2);
        g.edges[c2].push_back(c1);
        g.edge_costs[c1].push_back(dist);
        g.edge_costs[c2].push_back(dist);
    }

    return g;
}

std::vector<int> tracePath(int n, Graph& g, Node& node)
{
    std::vector<int> path;
    int curr = n;
    do {
        path.push_back(curr);
        curr = getParent(curr, g, node);
    } while (curr != -1);

    // Since we built the path backwards, we need to reverse it.
    std::reverse(path.begin(), path.end());
    return path;
}

void printPath(std::vector<int>& path, Graph& g)
{
    if (path.size() < 1)
    {
        std::cout << "No path found :(\n";
        return;
    }

    std::cout << "Path: ";
    for (int i = 0; i < path.size() - 1; i++)
    {
        std::cout << g.data[path[i]] << " -> ";
    }
    std::cout <<  g.data[path.back()] << "\n";
}

std::vector<int> getNeighbors(int n, Graph& g)
{
    return g.edges[n];
}

std::vector<float> getEdgeCosts(int n, Graph& g)
{
    return g.edge_costs[n];
}

int getParent(int idx, Graph& g, Node& node)
{
    return node.parent;
}

void initGraph(Graph& g)
{
    // TODO: Initialize any data you need for graph search.
    for (int i = 0; i< g.data.size(); i++){
        Node n;
        g.node_vec.push_back(n);
    }
}

std::vector<int> bfs(int start, int goal, Graph& g, Node& n)
{
    initGraph(g); 
    std::vector<int> path;  // Put your final path here.
    std::queue<int> visit_list;
    g.currentIdx = start;  // setup for root node
    n.dist = 0;
    visit_list.push(g.currentIdx);

    while (! visit_list.empty()){  // traverses nodes until we hit jackpot 
        n.parentIdx = g.currentIdx;
        g.currentIdx = visit_list.front();
        if (g.currentIdx == goal){
            goal = g.currentIdx;
            path = tracePath(goal, g, n);
            break;
        }
        visit_list.pop(); // moves current index from visit list to current node

        g.neighbors = getNeighbors(g.currentIdx, g);
        for (int i = 0; i < g.neighbors.size(); i++){
            visit_list.push(g.neighbors[i]); // Add each unvisited neighbor of current to back of visit list.
        }
        // Set parent of each neighbor to current, set distance to current distance + 1. Go to 2.
        n.parentIdx = getParent(g.currentIdx, g, n); 
        for (int i = 0; i < g.neighbors.size(); i++){
            g.node_vec[g.currentIdx] = g.node_vec[n.parentIdx];
        }
    }
    // TODO: Perform Breadth First Search over the graph g.
    return path;
}

int main() {
    Node n = createNode();
    Graph g = createGraph("mi_graph.txt");
    int start = nameToIdx("ann_arbor", g.data);
    int goal = nameToIdx("marquette", g.data);

    std::cout << "Searching for a path from " << g.data[start];
    std::cout << " (index: " << start << ") to " << g.data[goal];
    std::cout << " (index: " << goal << ")...\n";

    std::vector<int> path = bfs(start, goal, g, n);
    printPath(path, g);

    return 0;
} 