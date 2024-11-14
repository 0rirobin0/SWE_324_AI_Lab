#include <bits/stdc++.h>
using namespace std;
vector<int> nei[1005];
map<pair<int, int>, int> edgeCost;
void addEdge(int u, int v, int cost)
{
    nei[u].push_back(v);
    nei[v].push_back(u);
    // If the graph is
    // undirected
    edgeCost[{u, v}] = cost;
    edgeCost[{v, u}] = cost;
    // If the graph is
    // undirected
}
void UCS(int start, int goal)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> visited(1005, false);
    map<int, int> parent; // To track the parent of
                          // each node in the solution path
    pq.push({0, start});
    while (!pq.empty())
    {
        pair<int, int> current = pq.top();
        pq.pop();
        int currentState = current.second;
        int currentCost = current.first;
        if (visited[currentState])
        {
            continue;
        }
        cout << char(currentState + 'A') << " (Cost: "
             << currentCost << ")" << " -> ";

        visited[currentState] = true;
        if (currentState == goal)
        {
            vector<int> solutionPath;
            int node = currentState;
            while (node != start)
            {
                solutionPath.push_back(node);
                node = parent[node];
            }
            solutionPath.push_back(start);
            reverse(solutionPath.begin(),
                    solutionPath.end());
            cout << "Solution Path: ";
            for (int node : solutionPath)
            {
                cout << char(node + 'A') << " -> ";
            }
            cout << "\nGoal reached with cost: " << currentCost << endl;
            return;
        }
        for (int neighbor : nei[currentState])
        {
            if (!visited[neighbor])
            {
                int newCost = currentCost +
                              edgeCost[{currentState, neighbor}];
                pq.push({newCost, neighbor});
                parent[neighbor] = currentState;
            }
        }
        cout << "Queue: ";
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>, greater<pair<int, int>>>
            tempQueue = pq;
        while (!tempQueue.empty())
        {
            cout << char(tempQueue.top().second + 'A') << " (" << tempQueue.top().first << ")" << " ";
            tempQueue.pop();
        }
        cout << endl;
    }
    cout << "\nGoal not reachable from the start node." << endl;
}

int main()
{
    int n, e;
    cin >> n >> e;
    for (int i = 0; i < e; i++)
    {
        char p, q;
        int cost;
        cin >> p >> q >> cost;
        addEdge(p - 'A', q - 'A', cost);
    }
    char start, goal;
    cin >> start >> goal;
    UCS(start - 'A', goal - 'A');
    return 0;
}
/*
7 8
S A 3
S B 1
S C 8
A D 3
A E 7
A G 15
B G 20
C G 5
S G
*/