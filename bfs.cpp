#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 1e5 + 2;
bool Vis[N];
vector<int> adj[N];
int main()
{

    for (int i = 0; i < N; i++)
    {
        Vis[i] = 0;
    }

    //    Taking input of graph in adjacency list

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    // traversing the adj list  with BFS

    queue<int> q;
    q.push(1);
    Vis[1] = true;

    while (!q.empty())
    {
        int current_node = q.front();
        q.pop();
        cout << current_node << endl;

        vector<int>::iterator it;
        for (it = adj[current_node].begin(); it < adj[current_node].end(); it++)
        {
            if (!Vis[*it])
            {
                q.push(*it);
                Vis[*it] = true;
            }
        }
    }

    return 0;
}