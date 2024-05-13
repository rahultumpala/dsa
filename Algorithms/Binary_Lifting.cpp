/*

Binary Lifting:
---------------

Store 2^X ancestors of each element
Actually store only the first ancestor = 2^0 = 1 then travel through ancestors to find the 2^Xth ancestor

2^x = 2^(x-1) + 2^(x-1)

2^Xth ancestor of cur = 2^(X-1)th ancestor of 2^(X-1)th ancestor of current node

ex: 8th ancestor of cur = 4th ancestor of 4th ancestor of current node

2^3 ancestor = 2^2 ancestor of 2^2 ancestor of current node

*/

signed main() {
	int n, m;
	cin >> n >> m;

	map<int, vector<int>> adj;

	while (m--) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	// store ancestors
	int anc[n + 1][25];

	// store in & out times - euler tour
	int t_in[n + 1], t_out[n + 1];
	int time = 0;

	auto dfs = [&](auto && self, int cur, int p) -> void {
		t_in[cur] = time++;

		for (int i = 1; i < 25; i++) {
			/*
			 2^x = 2^(x-1) + 2^(x-1)
			 2^Xth ancestor of cur = 2^(X-1)th ancestor of 2^(X-1)th ancestor of cur
			 ex: 8th ancestor of cur = 4th ancestor of 4th ancestor of cur
			 2^3 ancestor = 2^2 ancestor of 2^2 ancestor of cur
			*/
			int lift = anc[cur][i - 1];
 			anc[cur][i] = anc[lift][i - 1];
		}

		for (int &next : adj[cur]) {

			if (next == p) continue;

			// 2^0 = 1, set the direct parent of the child node
			anc[next][0] = cur;
			self(self, next);
		}

		t_out[cur] = time - 1;
	};

	// is U an ancestor of V
	auto isAnc = [&](int u, int v) -> bool {
		return t_in[u] <= t_in[v] && t_out[u] >= t_out[v];
	};

	// rooting the tree at 1
	dfs(dfs, 1, 0);

	auto get_lca = [&](int a, int b) -> int{
		
		if(isAnc(a ,b)) return a;
		if(isAnc(b, a)) return b;

		for(int i = 24; i > -1; i--){
			int lift = anc[a][i];

			if(!isAnc(lift, b)){
				a = lift;
			}
		}

		// the direct parent of a is the LCAz
		return anc[a][0];
	};
}