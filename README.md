# OwO-codebook

還沒更新進pdf檔：
1. simplex
2. Lexicographically Smallest Rotation
3. 二分圖匹配
4. NTT

pdf不會放：
1. 混合圖歐拉迴路判定
2. priority_queue<Node,vector<Node>,cmp> pq;
struct cmp{
    bool operator()(Node a, Node b){
        if (a.x == b.x)  return a.y > b.y;
        return a.x > b.x;
    }
};

