//判有向圖有沒有負環，可以設一個超級源點，從那個點spfa
procedure Shortest-Path-Faster-Algorithm(G, s)
      for each vertex v ≠ s in V(G)
          d(v) := ∞
      d(s) := 0
      offer s into Q
      cnt[s] = 0 //cnt記錄更新到目前用了幾條邊
      while Q is not empty
          u := poll Q
          for each edge (u, v) in E(G)
              if d(u) + w(u, v) < d(v) then
                  cnt[v] = cnt[u] + 1;
                //如果cnt[v] > n表示有負環
                  d(v) := d(u) + w(u, v)
                  if v is not in Q then
                      offer v into Q
//判有向圈：設超級源點連到每個點，開始dfs某個點設inque=1，dfs完設inque=0。如果dfs到某個inque=1的點表示有圈。
