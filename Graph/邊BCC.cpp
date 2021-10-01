vector<int> g[maxn];
stack<int> stk;
int depth[maxn], low[maxn], bcc[maxn], nbcc;
bool visited[maxn];

void tarjan(int v, int p){
	stk.push(v);
	visited[v] = 1;
	low[v] = depth[v] = ~p ? depth[p] + 1 : 0;
	for (int u : g[v])	{
		if (u == p)
			continue;
		if (visited[u])
			low[v] = min(low[v], depth[u]);
		else
		{
			tarjan(u, v);
			low[v] = min(low[v], low[u]);
		}
	}
	if (low[v] == depth[v])
	{ //the edge (v,p) is a bridge if v is not the root vertex
		while (!stk.empty())
		{
			int x = stk.top(); //x belongs to the same component as v
			stk.pop();
			bcc[x] = nbcc;
			if (x == v)
				break;
		}
		nbcc++;
	}
}
