#include "graph.h"
#include <algorithm>
#include <climits>
using namespace std;

/** Finds the min of the residual path. */
int find_min(map<pair<int,int>,int> vec, vector<int> path) {
	int min = INT_MAX;

	for (size_t i = 0; i < path.size()-1; ++i) {
		int u = path[i];
		int v = path[i+1];
		pair<int,int> p(u,v);
		int cand = vec[p];
		if (cand < min) min = cand;
	}
	
	return min;
}

int ford_fulkerson(Graph G, const int s, const int t) { 
	map<pair<int,int>,int> ew = G.getEdgeWeights();
	int max_flow = 0;
	Graph Gf = G;

	bool is_path = true;
	while (is_path) { 
		map<pair<int,int>,int> cf = Gf.getEdgeWeights();
		map<pair<int,int>,int> f;
		for (auto e: cf) {
			if(e.second <= 0) {
				Gf.removeEdge(e.first.first,e.first.second);
			}
		} 
	
		pair<vector<int>,bool> pv = pathDFS(Gf,s,t);
		is_path = pv.second;
		if (!is_path) break;
		vector<int> path = pv.first;

		int cf_min = find_min(cf,path);

		for (size_t i = 0; i < path.size()-1; ++i) {
			int u = path[i];
			int v = path[i+1];
			Gf.setEdgeWeight(u,(Gf.getEdgeWeight(u,v)-cf_min),v);	
			Gf.setEdgeWeight(v,cf_min,u);	
		}

		max_flow += cf_min;
		
	}

	return max_flow;
}