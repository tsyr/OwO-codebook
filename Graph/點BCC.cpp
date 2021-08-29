vector<P> g[maxn]; //{u,e} u是點,e是邊的編號
stack<int> stk;
int low[maxn], depth[maxn], bcc[maxn], nbcc;
bool visited[maxn], cut[maxn], pushed[maxn];
void tarjan(int v, int p) {//tarjan(1,-1)
	visited[v] = 1;
	low[v] = depth[v] = ~p ? depth[p] + 1 : 0;
	int child = 0;
	for (int i = 0; i < g[v].size(); ++i){
		int u = g[v][i].first, e = g[v][i].second;
		if (u == p)
			continue;
		if (!pushed[e]){
			pushed[e] = 1;
			stk.push(e);
		}
		if (visited[u])
			low[v] = min(low[v], depth[u]);
		else{
			++child;
			tarjan(u, v);
			low[v] = min(low[v], low[u]);
			if (low[u] >= depth[v]){
				cut[v] = 1;
				while (!stk.empty()){
					int b = stk.top();
					stk.pop();
					bcc[b] = nbcc;
					if (b == e)
						break;
				}
				++nbcc;
			}
		}
	}
	if (p == -1 && child == 1)
		cut[v] = 0;
}
