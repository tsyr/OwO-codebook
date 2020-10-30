typedef int type;
struct Node{
    type key;
    int dist; int lc, rc;
};
vector<Node> vv;
struct Leftist_Heap{
    int root;
    Leftist_Heap() { root = -1; }
    type top(){
        assert(root >= 0);
        return vv[root].key;
    }
    int merge(int a, int b){
        if (a==-1)  return b; if (b==-1)  return a;
        if (vv[b].key < vv[a].key) //小根堆是<，否則>
            swap(a, b);
        vv[a].rc = merge(vv[a].rc, b);
        if (vv[a].lc == -1 || ((vv[a].rc == -1) && (vv[vv[a].rc].dist > vv[vv[a].lc].dist)))
            swap(vv[a].lc, vv[a].rc);
        if (vv[a].rc == -1)   vv[a].dist = 0;
        else  vv[a].dist = vv[vv[a].rc].dist + 1;
        return a;
    }
    void push(type ins){
        Node x;
        x.dist = 0, x.key = ins, x.lc = x.rc = -1;
        vv.push_back(x);
        root = merge(root, vv.size() - 1);
    }
    void pop(){
        assert(root != -1);
        root = merge(vv[root].lc, vv[root].rc);
    }
};
