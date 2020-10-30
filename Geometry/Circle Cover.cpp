#define N 1021
struct CircleCover{
  int C;
  Circle c[N];
  bool g[N][N], overlap[N][N];
  // Area[i] : area covered by at least i circles
  double Area[N];
  void init(int _C) { C = _C; }
  bool CCinter(Circle &a, Circle &b, P &p1, P &p2){
    P o1 = a.c, o2 = b.c;
    double r1 = a.r, r2 = b.r;
    if (len(o1 - o2) > r1 + r2)
      return {};
    if (len(o1 - o2) < max(r1, r2) - min(r1, r2))
      return {};
    double d2 = (o1 - o2) * (o1 - o2);
    double d = sqrt(d2);
    if (d > r1 + r2)
      return false;
    P u = 0.5 * (o1 + o2) + ((r2 * r2 - r1 * r1) / (2 * d2)) * (o1 - o2);
    double A = sqrt((r1 + r2 + d) * (r1 - r2 + d) * (r1 + r2 - d) * (-r1 + r2 + d));
    P v = A * P(o1.Y - o2.Y, -o1.X + o2.X) / (2 * d2);
    p1 = u + v;
    p2 = u - v;
    return true;
  }
  struct Teve{
    P p;
    double ang;
    int add;
    Teve() {}
    Teve(P _a, double _b, int _c) : p(_a), ang(_b), add(_c) {}
    bool operator<(const Teve &a) const{
      return ang < a.ang;
    }
  } eve[N * 2];
  // strict: x = 0, otherwise x = -1
  bool disjuct(Circle &a, Circle &b, int x){
    return dcmp(len(a.c - b.c) - a.r - b.r) > x;
  }
  bool contain(Circle &a, Circle &b, int x){
    return dcmp(a.r - b.r - len(a.c - b.c)) > x;
  }
  bool contain(int i, int j) {
    /* c[j] is non-strictly in c[i]. */
    return (dcmp(c[i].r - c[j].r) > 0 ||
            (dcmp(c[i].r - c[j].r) == 0 && i < j)) &&
           contain(c[i], c[j], -1);
  }
  void solve(){
    for (int i = 0; i <= C + 1; i++)
      Area[i] = 0;
    for (int i = 0; i < C; i++)
      for (int j = 0; j < C; j++)
        overlap[i][j] = contain(i, j);
    for (int i = 0; i < C; i++)
      for (int j = 0; j < C; j++)
        g[i][j] = !(overlap[i][j] || overlap[j][i] ||
                    disjuct(c[i], c[j], -1));
    for (int i = 0; i < C; i++) {
      int E = 0, cnt = 1;
      for (int j = 0; j < C; j++)
        if (j != i && overlap[j][i])
          cnt++;
      for (int j = 0; j < C; j++)
        if (i != j && g[i][j]) {
          P aa, bb;
          CCinter(c[i], c[j], aa, bb);
          double A = atan2(aa.Y - c[i].c.Y, aa.X - c[i].c.X);
          double B = atan2(bb.Y - c[i].c.Y, bb.X - c[i].c.X);
          eve[E++] = Teve(bb, B, 1);
          eve[E++] = Teve(aa, A, -1);
          if (B > A)
            cnt++;
        }
      if (E == 0)
        Area[cnt] += pi * c[i].r * c[i].r;
      else{
        sort(eve, eve + E);
        eve[E] = eve[0];
        for (int j = 0; j < E; j++){
          cnt += eve[j].add;
          Area[cnt] += (eve[j].p ^ eve[j + 1].p) * .5;
          double theta = eve[j + 1].ang - eve[j].ang;
          if (theta < 0)
            theta += 2. * pi;
          Area[cnt] +=
              (theta-sin(theta)) * c[i].r*c[i].r*.5;
        }
      }
    }
  }
};
