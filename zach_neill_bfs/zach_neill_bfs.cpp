#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#define HIGH 1e6

struct Node {
    float dist = 1000000;
    int parentIdx = -1; 
    bool visited = false;
    bool queued = false;
};
struct Graph
{
    std::vector<std::string> data;
    std::vector<std::vector<int> > edges;
    std::vector<std::vector<float> > edge_costs;
    std::vector<float> costs;
    std::vector<Node> node_vec;
    int currentIdx;
};

int nameToIdx(std::string name, std::vector<std::string>& v);
Graph createGraph(std::string file_path);
std::vector<int> tracePath(int n, Graph& g);
void printPath(std::vector<int>& path, Graph& g);
std::vector<int> getNeighbors(int n, Graph& g);
std::vector<float> getEdgeCosts(int n, Graph& g);
void initGraph(Graph& g);
int getParent(int n, Graph& g);
std::vector<int> bfs(int start, int goal, Graph& g);

int nameToIdx(std::string name, std::vector<std::string>& v)
{
    for (int i = 0; i < v.size(); i++) if (v[i] == name) return i;
    return -1;
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

std::vector<int> tracePath(int n, Graph& g)
{
    std::vector<int> path;
    int curr = n;
    do {
        path.push_back(curr);
        curr = getParent(curr, g);
    } while (curr != -1);

    std::reverse(path.begin(), path.end());  // Since we built the path backwards, we need to reverse it.
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
    for (int i = 0; i < path.size() - 1; i++) std::cout << g.data[path[i]] << " -> ";
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

int getParent(int idx, Graph& g)
{
    return g.node_vec[idx].parentIdx;
}

void initGraph(Graph& g)
{
    for (int i = 0; i< g.data.size(); i++){
        Node n;
        g.node_vec.push_back(n);
    }
}

std::vector<int> bfs(int start, int goal, Graph& g)
{
    initGraph(g);  // basic inits
    std::vector<int> path; 
    std::queue<int> visit_list;

    g.node_vec[start].dist = 0;  // setup for initial node
    g.node_vec[start].queued = true;
    visit_list.push(start);

    while (! visit_list.empty()){  // traverses nodes until we hit jackpot 
        g.currentIdx = visit_list.front();
        g.node_vec[g.currentIdx].visited = true;
        std::vector<int> neighbors = getNeighbors(g.currentIdx, g);
        std::vector<float> costs = getEdgeCosts(g.currentIdx, g);

        if (g.currentIdx == goal){  // ends if we reached our destination
            path = tracePath(g.currentIdx, g);
            break;
        }
        visit_list.pop();  // moves current index from visit list to current node
        for (int i = 0; i < neighbors.size(); i++){
            if (! g.node_vec[neighbors[i]].visited){  // Add unvisited neighbor of current to back of visit.
                if (! g.node_vec[neighbors[i]].queued) visit_list.push(neighbors[i]);
                if (g.node_vec[neighbors[i]].dist > g.node_vec[g.currentIdx].dist + costs[i]){
                    g.node_vec[neighbors[i]].dist = g.node_vec[g.currentIdx].dist + costs[i];
                    g.node_vec[neighbors[i]].parentIdx = g.currentIdx;
                }  // compares distances to avoid the connection loop
            }
        }
    }
    return path;
}

int main() {
    Graph g = createGraph("mi_graph.txt");
    int start = nameToIdx("ann_arbor", g.data);
    int goal = nameToIdx("marquette", g.data);

    std::cout << "Searching for a path from " << g.data[start];
    std::cout << " (index: " << start << ") to " << g.data[goal];
    std::cout << " (index: " << goal << ")...\n";

    std::vector<int> path = bfs(start, goal, g);
    printPath(path, g);

    return 0;
} 
