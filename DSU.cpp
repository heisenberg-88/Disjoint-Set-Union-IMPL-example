// https://acm.timus.ru/problem.aspx?space=1&num=1671&locale=en
// https://cp-algorithms.com/data_structures/disjoint_set_union.html
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility> 
#include <iterator>
#include <set>
using namespace std;
class DSU {
	public:
		vector<int> size, parent, rank;
		int n;
		DSU(int n) {
			size.resize(n);
			parent.resize(n);
			rank.resize(n);
			this->n = n;
			make_set();
		}
		void make_set() {
			for (int i = 0; i < n; i++) {
				parent[i] = i;
				size[i] = 1;
				rank[i] = 0;
			}
		}
		int find_set(int x) {
			if (parent[x] == x) {
				return x;
			}
			return parent[x] = find_set(parent[x]);
		}
		bool union_set(int a, int b) {
 			a = find_set(a);
			b = find_set(b);
			if (a != b) {
				if (size[a] < size[b]) {
					swap(a, b);
				}
				parent[b] = a;
				size[a] += size[b];
				return true;
			}
			return false;
		}
		bool union_set_byRank(int a, int b) {
			a = find_set(a);
			b = find_set(b);
			if (a != b) {
				if (rank[a] < rank[b])
					swap(a, b);
				parent[b] = a;
				if (rank[a] == rank[b])
					rank[a]++;
				return true;
			}
			return false;
		}
};
int main() {
	int N, M;
	cin >> N >> M;
	vector<pair<int, int>> edges(M);
	for (int i = 0; i < M; ++i) {
		int u, v;
		cin >> u >> v;
		edges[i] = { u - 1, v - 1 }; // Convert to 0-based indexing
	}

	int Q;
	cin >> Q;
	vector<int> removeEdges(Q);
	vector<bool> isRemoved(M, false);
	for (int i = 0; i < Q; ++i) {
		cin >> removeEdges[i];
		removeEdges[i]--; // Convert to 0-based indexing
		isRemoved[removeEdges[i]] = true;
	}
	
	DSU* dsu = new DSU(N);
	int NumOfComps = N;
	for (int i = 0; i < M; i++) {
		if (isRemoved[i] == false) {
			bool unionSuccess = dsu->union_set(edges[i].first, edges[i].second);
			if (unionSuccess == true) {
				NumOfComps--;
			}
		}
	}
	vector<int> ans(Q);
	for (int i = Q - 1; i >= 0; i--) {
		ans[i] = NumOfComps;
		int u = edges[removeEdges[i]].first;
		int v = edges[removeEdges[i]].second;
		bool unionSuccess = dsu->union_set(u, v);
		if (unionSuccess == true) {
			NumOfComps--;
		}
	}
	for (auto i : ans) {
		cout << i << " ";
	}
}
