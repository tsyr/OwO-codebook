struct Trie{
  int ch[maxnode][sigma_size]; 
//Total number of nodes / total number of characters
  int val[maxnode];
  int sz;
  int fail[maxnode]; //Failure function
  int last[maxnode]; //Suffix link
  void init(){
    sz = 1;
    memset(ch[0], 0, sizeof(ch[0]));
  }
  int idx(char c) { return c - 'a'; } //The number representing the character c may need to be changed
  void insert(char *s, int vv){
    int u = 0, nn = strlen(s);
    for (int i = 0; i < nn; i++){
      int c = idx(s[i]);
      if (!ch[u][c]){
        memset(ch[sz], 0, sizeof(ch[sz]));
        val[sz] = 0;
        ch[u][c] = sz++;
      }
      u = ch[u][c];
    }
    val[u] = vv;
  }
  void getfail(){
    queue<int> q;
    fail[0] = 0;
    for (int c = 0; c < sigma_size; c++){
      int u = ch[0][c];
      if (u){
        fail[u] = 0;
        q.push(u);
        last[u] = 0;
      }
    }
    while (!q.empty()){
      int r = q.front();
      q.pop();
      for (int c = 0; c < sigma_size; c++)  {
        int u = ch[r][c];
        if (!u){
          ch[r][c] = ch[fail[r]][c];
          continue;
        }
        q.push(u);
        int vv = fail[r];
        while (vv & !ch[vv][c])
          vv = fail[vv];
        fail[u] = ch[vv][c];
        last[u]=val[fail[u]]? fail[u]:last[fail[u]];
//走到結點u可能代表找到很多種以u為結尾的字串，沿著last[u]這種邊走可以找出所有這種字串。
      }
    }
  }
  void print(int j){
    if (j){
      //do something
      print(last[j]);
    }
  }
  void find(char *T){
    int nn = strlen(T);
    int j = 0;
    for (int i = 0; i < nn; i++){
      int c = idx(T[i]);
      while (j && !ch[j][c])
        j = fail[j];
      j = ch[j][c];
      if (val[j])
        print(j);
      else if (last[j])
        print(last[j]);
    }
  }
} ac;
