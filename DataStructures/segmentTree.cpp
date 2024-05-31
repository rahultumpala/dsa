#include <bits/stdc++.h>

using namespace std;

/*

always start with query(0, 0, segtree.size());
query(i, r_l, r_r, l , r);
i = index of segtree
r_l = start of range that i contains
r_r = end of range that i contains
l = start of range of query
r = end of range of query

The following SegmentTree will answer RMQ (Range Minimum Query)

*/

vector<int> segtree;
vector<int> nums;

int build(int i, int l, int r) {
	// printf("build -- %d %d %d\n", i, l , r);
	if (l + 1 == r) {
		segtree[i] = nums[l];
	} else {
		int mid = (l + r) / 2;
		int left = build(2 * i + 1, l, mid);
		int right = build(2 * i + 2, mid, r);
		segtree[i] = min(left, right);
	}
	return segtree[i];
}

int query(int i, int r_l, int r_r,  int l, int r) {
	// printf("query -- %d %d %d %d %d %d\n", segtree[i], i, r_l, r_r, l , r);

	if (r_l + 1 == r_r)return segtree[i];
	if (r_l == l && r_r == r + 1) return segtree[i];

	int mid = (r_l + r_r) / 2;
	int left_min = INT_MAX, right_min = INT_MAX;

	if (l < mid)
		left_min = query(2 * i + 1, r_l, mid, l, min(mid-1, r));
	if (mid <= r)
		right_min = query(2 * i + 2, mid, r_r, max(mid, l), r);

	return min(left_min, right_min);
}

signed main() {
	int n, q;
	cin >> n >> q;
	nums.resize(n);
	segtree.resize(4 * n, INT_MAX);
	for (int i = 0; i < n; i++) cin >> nums[i];
	build(0, 0, n);
	while (q--) {
		int l, r;
		cin >> l >> r;
		cout << query(0, 0, n, l - 1 , r - 1) << endl;
	}
}