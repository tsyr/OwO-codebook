//從u到v的最短路徑，必會通過重心樹上的lca(u,v)
struct Centroid_Decomposition{
  typedef long long type;
  int subSize[100005];
  bool used[100005];
  vector<pair<int, type>> tree[100005];
  int cd_father[100005], dep[100005]; //cd_father[i]:i在重心樹上的父親，dep[i]:i在重心樹上的深度
  type dis[20][100005]; 
  //dis[d][v]:v到重心樹上深度為d的祖先的距離
  int idx[100005]; 
  //idx[i]:i是cd_father[i]在重心樹上的第幾號兒子

  void addEdge(int u, int v, type w)  {
    tree[u].push_back(make_pair(v, w));
    tree[v].push_back(make_pair(u, w));
  }
  int dfs(int u, int p)  {
    subSize[u] = 1;
    for (pair<int, type> v : tree[u])
      if (v.first != p && !used[v.first])
        subSize[u] += dfs(v.first, u);
    return subSize[u];
  }
  int get_centroid(int u, int p, int n)  {
    for (pair<int, type> v : tree[u])
      if (v.first != p && subSize[v.first] > n / 2 && !used[v.first])
        return get_centroid(v.first, u, n);
    return u;
  }
  void get_distance(int u, int p, int depp, type dist){
    dis[depp][u] = dist;
    for (pair<int, type> v : tree[u])
      if (v.first != p && !used[v.first])
        get_distance(v.first, u, depp, dist+v.second);
  }
  int centroid_decomposition(int u, int p, int depp, int id)  { //一開始叫(1,-1,0,0)
    int n = dfs(u, p);
    int centroid = get_centroid(u, p, n);
    dep[centroid] = depp, cd_father[centroid] = p, idx[centroid] = id;
    get_distance(centroid, p, depp, 0);
    used[centroid] = 1;
    int cur = 0;
    for (pair<int, type> v : tree[centroid])
      if (v.first != p && !used[v.first])
        centroid_decomposition(v.first, centroid, depp + 1, cur++);
    return centroid;
  }
} cd;
