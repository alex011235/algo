Graph Algorithms
=================================

### Bellman-Ford
Computes the shortest from a source vertex s to all the other vertices in a weighted directed graph. It does the same job as Dijkstra's algorithm, but it can handle negative edge weights. Thus it's more versatile. 

[Bellman-Ford, Wikipedia](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)

<p align="center">
<img src="images/bellmanford1.png" height="250" alt="Screenshot"/>
</p>

<p align="center">
<img src="images/bellmanford2.png" height="250" alt="Screenshot"/>
</p>

### Breadth First Seach (BFS)
BFS is an algorithm for graph/tree traversing/searching. The traversing starts at a given node and explores the neighbors before moving to the next level. See the example below.

[BFS, Wikipedia](https://en.wikipedia.org/wiki/Breadth-first_search)

<p align="center">
<img src="images/bfs.png" height="250" alt="Screenshot"/>
</p>

### Depth-First Search (DFS)
DFS is an algorithm for traversing/searching trees and graphs. The algorithm starts at a given node and explores as "deep" as possible along each branch before backtracking.

[DFS, Wikipedia](https://en.wikipedia.org/wiki/Depth-first_search)

<p align="center">
<img src="images/dfs.png" height="250" alt="Screenshot"/>
</p>

#### DFS, path-search
A variant of the ordinary DFS algorithm. This version finds a path from the source vertex s and the destination vertex t, although not necessarily the shortest. 

<p align="center">
<img src="images/dfs_path.png" height="250" alt="Screenshot"/>
</p>

#### Dijkstra's Algorithm
`dijkstra.cc` and `dijkstra_pq.cc` find the shortest path between a give source s node and every other node in the graph s belongs to. The Latter is implemented with a priority queue.

<p align="center">
<img src="images/dijkstra.png" height="250" alt="Screenshot"/>
</p>

#### Floyd-Warshall's Algorithm
An algorithm for finding shortest paths in a weighted graph with positive or negative edge  weights. A single execution of the algorithm will find the lengths of the shortest paths between all pairs of vertices.
This implementation supports path reconstruction.

<p align="center">
<img src="images/floydwarshall.png" height="320" alt="Screenshot"/>
</p>

#### Kosaraju's Algorithm
Generates the strongly connected components (SCC) of a directed graph.
The SCC parts are marked blue in the example below.

<p align="center">
<img src="images/kosaraju.png" height="250" alt="Screenshot"/>
</p>

#### Prim's Algorithm
Finds a minimum spanning tree (MST) for a weighted undirected graph.

<p align="center">
<img src="images/prim.png" height="250" alt="Screenshot"/>
</p>

#### Ford-Fulkerson Algorithm
This algorithm computes the maximum flow from the source vertex s to the sink vertex t. 

[Ford-Fulkersson, Wikipedia](https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm)


![PageRank](images/fordfulkerson1.png)

![PageRank](images/fordfulkerson2.png)


#### Algorithm for approximation of the travelling salesman problem
Greedy. Takes the shortest path from the current node (nearest neighbor). 