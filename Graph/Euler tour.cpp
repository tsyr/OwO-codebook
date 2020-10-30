//求歐拉回路或歐拉路，鄰接陣形式，複雜度o（n^2）
//返回路徑長度，path返回路徑(有向圖是得到的是反向路徑)
//傳入圖的大小n和鄰接陣mat，不相交鄰點邊權0
//可以有自環與重邊，分為無向圖和有向圖
#define MAXN 100
void find_path(int n, int mat[][MAXN], int now, int &step, int *path){
    int i;
    for (i = n - 1; i >= 0; i--)
        while (mat[now][i]){
            mat[now][i]--; //無向圖加上mat[i][now]--;
            find_path(n, mat, i, step, path);
        }
    path[step++] = now;
}
int euclid_path(int n, int mat[][MAXN], int start, int *path){
    int ret = 0;
    find_path(n,mat,start,ret,path);
    return ret;
}
