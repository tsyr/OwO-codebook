struct Mec{
  // return pair of center and r
  type norm2(P x) { return x.X * x.X + x.Y * x.Y; }
  static const int N = 101010;
  int n;
  P p[N], cen;
  double r2;
  void init(int _n, P _p[]) {
    n = _n;
    memcpy(p, _p, sizeof(P) * n);
  }
  double sqr(double a) { return a * a; }
  P center(P p0, P p1, P p2) {
    P a = p1 - p0;
    P b = p2 - p0;
    double c1 = norm2(a) * 0.5;
    double c2 = norm2(b) * 0.5;
    double d = a ^ b;
    double x = p0.X + (c1 * b.Y - c2 * a.Y) / d;
    double y = p0.Y + (a.X * c2 - b.X * c1) / d;
    return P(x, y);
  }
  pair<P, double> solve() {
    random_shuffle(p, p + n);
    r2 = 0;
    for (int i = 0; i < n; i++){
      if (norm2(cen - p[i]) <= r2)
        continue;
      cen = p[i];
      r2 = 0;
      for (int j = 0; j < i; j++){
        if (norm2(cen - p[j]) <= r2)
          continue;
        cen=P((p[i].X+p[j].X)/2,(p[i].Y+p[j].Y)/ 2);
        r2 = norm2(cen - p[j]);
        for (int k = 0; k < j; k++){
          if (norm2(cen - p[k]) <= r2)
            continue;
          cen = center(p[i], p[j], p[k]);
          r2 = norm2(cen - p[k]);
        }
      }
    }
    return {cen, sqrt(r2)};
  }
} mec;
