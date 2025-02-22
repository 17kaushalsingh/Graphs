# Traversals

## BFS Traversal (Level Order Traversal)
    - Time: Nodes (N) + Degree (2xEdges for undirected, Edges for directed)
    - Space: Nodes (N)
    - Initial Configuration: Queue data structure having the starting node, isVisited array with starting node visited
    - Algorithm: Start taking out from the front of queue and print/store, and then add its neighbour. Repeat until the queue is empty.

```cpp
void bfsTraversal(int startNode, vector<int> adj[], vector<bool> &isVisited, vector<int> &bfsTraversalAns)
{
    queue<int> q;
    q.push(startNode);
    isVisited[startNode] = true;

    while (!q.empty())
    {
        int frontNode = q.front();
        q.pop();
        bfsTraversalAns.push_back(frontNode);

        for (auto adjNode : adj[frontNode])
        {
            if (!isVisited[adjNode])
            {
                isVisited[adjNode] = true;
                q.push(adjNode);
            }
        }
    }
}
```

## DFS Traversal
    - Time: Nodes (N) + Degree (2xEdges for undirected, Edges for directed)
    - Space: Nodes (N), Recursion Space Stack: Node (N)
    - Initial Configuration: isVisited array
    - Algorithm: Use recursion, mark the node as visited on entering the function and print/store it. Call the recursion on its neighbours if they are unvisited

```cpp
void dfsTraversal(int node, vector<int> adj[], vector<bool> &isVisited, vector<int> &dfsTraversalAns)
{
    isVisited[node] = true;
    dfsTraversalAns.push_back(node);

    for (auto adjNode : adj[node])
    {
        if (!isVisited[adjNode])
        {
            dfsTraversal(adjNode, adj, isVisited, dfsTraversalAns);
        }
    }
}
```