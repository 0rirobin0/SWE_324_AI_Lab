#include <bits/stdc++.h>
using namespace std;
vector<int> nei[1005];
bool vis[1005];
bool Dfs(int src, int target, int depthLimit)
{
    if (depthLimit < 0)
    {
        return false;
    }
    if (src == target)
    {
        vis[src] = true;
        cout << char(src + 'A') << " -> ";
        return true;
    }
    vis[src] = true;
    cout << char(src + 'A') << " -> ";
    for (int adj : nei[src])
    {
        if (!vis[adj] && Dfs(adj, target, depthLimit - 1))
        {
            return true;
        }
    }
    return false;
}
bool IDDFS(int src, int target, int maxDepth)
{
    for (int depthLimit = 0; depthLimit <= maxDepth;
         depthLimit++)
    {
        memset(vis, false, sizeof(vis)); // Clear visited array
        cout << "Depth-Limited Search with depth limit " << depthLimit << " from " << char(src + 'A') << " to " << char(target + 'A') << ":" << endl;
        if (Dfs(src, target, depthLimit))
        {
            cout << "\nTarget found within depth limit." << endl;
            return true;
        }
        else
        {
            cout << "\nTarget not found within depth limit."
                 << endl;
        }
    }
    return false;
}
int main()
{
    int n;
    cin >> n;
    int e = n - 1;
    for (int i = 0; i < e; i++)
    {
        char p, q;
        cin >> p >> q;
        nei[p - 'A'].push_back(q - 'A');
        nei[q - 'A'].push_back(p - 'A');
    }
    for (int i = 0; i < n; i++)
    {
        cout << char(i + 'A') << "--> ";
        for (int node : nei[i])
        {
            cout << char(node + 'A') << " ";
        }
        cout << endl;
    }
    char source, target;
    int maxDepth;
    cin >> source >> target >> maxDepth;
    int src = source - 'A';
    int tgt = target - 'A';
    if (!IDDFS(src, tgt, maxDepth))
    {
        cout << "\nTarget not found within the maximum depth." << endl;
    }
    return 0;
}
/*
6
A B
A C
B D
B E
C F
A E
3
*/