#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 1e5 + 2;
bool Vis[N];
vector<int> adj[N];

void dfs(int node)
{
    // pre-order
    Vis[node] = true;
    cout << node << " ";

    // inorder
    vector<int>::iterator it;
    for (it = adj[node].begin(); it != adj[node].end(); it++)
    {
        if (!Vis[*it])
        {
            dfs(*it);
        }
    }

    // post order
    // cout<< node <<" ";
}

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

    dfs(1);

    return 0;
}