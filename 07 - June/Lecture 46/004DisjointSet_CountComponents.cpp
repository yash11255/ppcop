/*

	number of components in an undirection graph using the union-find algorithm.

*/

#include<iostream>
#include<unordered_map>
#include<set>
#include<vector>

using namespace std;

template <typename T>
class disjointSet {

	unordered_map<T, T> parentMap; // to store a mapping b/w vertices & their parents
	unordered_map<T, T> rankMap;   // to store a mapping b/w vertices & their ranks i.e. sizes

public :

	void createSet(T x) {
		parentMap[x] = x;
		rankMap[x] = 1;
	}

	T findSet(T x) {
		if (parentMap[x] == x) {
			return x;
		}

		return parentMap[x] = findSet(parentMap[x]); // path compression
	}

	void unionSet(T x, T y) {
		T p_x = findSet(x);
		T p_y = findSet(y);
		if (p_x != p_y) {
			if (rankMap[p_x] > rankMap[p_y]) { // union by rank (size)
				parentMap[p_y] = p_x;
				rankMap[p_x] += rankMap[p_y];
			} else {
				parentMap[p_x] = p_y;
				rankMap[p_y] += rankMap[p_x];
			}
		}
	}

};


template <typename T>
class edge {
public :

	T u;
	T v;

	edge(T u, T v) {
		this->u = u;
		this->v = v;
	}
};

template <typename T>
class graph {

	set<T>  vertexSet;        // to store the graph representation
	vector<edge<T>> edgeList; // to store the graph representation

public :

	void addEdge(T u, T v) {
		// add an edge of weight 'w' b/w 'u' and 'v'
		edgeList.push_back(edge<T>(u, v));
		vertexSet.insert(u);
		vertexSet.insert(v);
	}

	int countComponents() {
		disjointSet<T> ds;
		for (T vertex : vertexSet) {
			ds.createSet(vertex);
		}
		int numComponents = vertexSet.size();
		for (edge<T> e : edgeList) {
			if (ds.findSet(e.u) != ds.findSet(e.v)) {
				ds.unionSet(e.u, e.v);
				numComponents--;
			}
		}
		return numComponents;
	}
};

int main() {

	graph<char> g;

	g.addEdge('A', 'B');
	g.addEdge('A', 'C');
	g.addEdge('B', 'C');

	g.addEdge('D', 'E');
	g.addEdge('D', 'F');

	g.addEdge('G', 'H');

	cout << g.countComponents() << endl;

	return 0;
}
