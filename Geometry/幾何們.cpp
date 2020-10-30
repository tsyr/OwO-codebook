#define X first
#define Y second
#define pi acos(-1.0)
#define eps 1e-8
typedef double type;
typedef pair<type, type> P;
int dcmp(double x){
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}
struct Line{P p, v;};
//atan2的範圍是-pi~pi
bool operator<(Line l1, Line l2) { return atan2(l1.v.Y, l1.v.X) < atan2(l2.v.Y, l2.v.X); }
bool equal(type x, type y) { return fabs(x - y) < eps; }
bool less(type x, type y) { return x < y - eps; }
bool greater(type x, type y) { return x > y + eps; }
P operator+(P p1, P p2) { return P(p1.X + p2.X, p1.Y + p2.Y); }
P operator-(P p1, P p2) { return P(p1.X - p2.X, p1.Y - p2.Y); }
type operator*(P p1, P p2) { return p1.X * p2.X + p1.Y * p2.Y; }
P operator*(double t, P p) { return P(t * p.X, t * p.Y); } P operator/(P p, double t) { return P(p.X / t, p.Y / t); }
type operator^(P p1, P p2) { return (p1.X * p2.Y - p1.Y * p2.X); }
double len(P p) { return sqrt(1.0*p.X*p.X+p.Y*p.Y); }
double angle(P p1, P p2){ //p1轉到p2，範圍是0~2*pi
    if ((p1 ^ p2) < 0)   return 2 * pi - acos((double)(p1 * p2) / len(p1) / len(p2));
    return acos((double)(p1 * p2) / len(p1) / len(p2));
}
bool on(P a, P p1, P p2) { return ((dcmp((p1 - a) * (p2 - a)) <= 0) &&dcmp((p1 - a) ^ (p2 - a)) == 0); }
bool in(P a, P p1, P p2) { return dcmp((p1 ^ a) * (p2 ^ a)) < 0; }
bool cross(P p1, P p2, P p3, P p4)
{ //p1-p2線段和p3-p4線段是否相交
    if (on(p3, p1, p2) || on(p4, p1, p2) || on(p1, p3, p4) || on(p2, p3, p4))
        return 1;
    if (in(p2 - p1, p3 - p1, p4 - p1) && in(p4 - p3, p1 - p3, p2 - p3))
        return 1;
    return 0;
}
double torad(double deg) { return pi * deg / 180.0; }
P rotate(P p, double rad) { return P(p.X * cos(rad) - p.Y * sin(rad),
                                     p.X * sin(rad) + p.Y * cos(rad)); }
double dist(P p, Line l) { return fabs((p - l.p) ^ l.v) / len(l.v); }
P LineIntersect(Line l1, Line l2){//兩直線平行時不能叫
    double t = 1.0 * ((l2.p - l1.p) ^ l2.v) / (l1.v ^ l2.v);
    return l1.p + t * l1.v;
}
bool SegLineIntersect(P p1, P p2, Line l)
{ //線段p1-p2和直線l有沒有相交
    Line l1;
    l1.p = p1, l1.v = p2 - p1;
    if (dcmp(l.v ^ (l.p - p1)) == 0 || dcmp(l.v ^ (l.p - p2)) == 0)
        return 1;
    return in(l.v, p1 - l.p, p2 - l.p);
}
type area2(vector<P> ps) { //兩倍多邊形面積
    type res = 0;
    for (int i = 0; i < ps.size(); i++)
        res += (ps[i] ^ ps[(i + 1) % ps.size()]);
    if (res < 0)
        res = -res;
    return res;
}
bool inPolygon(P p, vector<P> poly){
    int wn = 0;
    int n = poly.size();

    for (int i = 0; i < n; i++){
        if (on(p, poly[i], poly[(i + 1) % n]))
            return -1; //在邊界
        int k = dcmp((poly[(i + 1) % n] - poly[i]) ^ (p - poly[i]));
        int d1 = dcmp(poly[i].Y - p.Y);
        int d2 = dcmp(poly[(i + 1) % n].Y - p.Y);
        if (k > 0 && d1 <= 0 && d2 > 0)
            wn++;
        if (k < 0 && d2 <= 0 && d1 > 0)
            wn--;
    }
    if (wn != 0)
        return 1; //內部
    return 0;     //外部
}
vector<P> ConvexHull(vector<P> ps){
    int nn = ps.size();
    sort(ps.begin(), ps.end());
    vector<P> res;
    int k = 0;
    for (int i = 0; i < nn; i++){
        while (k > 1 && dcmp((ps[i] - res[k - 2]) ^ (res[k - 1] - res[k - 2])) >= 0) {
            res.pop_back();
            k--;
        }
        res.push_back(ps[i]);
        k++;
    }
    int t = k;
    for (int i = nn - 2; i >= 0; i--){
        while (k > t && dcmp((ps[i] - res[k - 2]) ^ (res[k - 1] - res[k - 2])) >= 0){
            res.pop_back();
            k--;
        }
        res.push_back(ps[i]);
        k++;
    }
    if (nn > 1)
        res.pop_back();
    return res;
};
struct Half_Plane_Intersection
{ //半平面交(所有直線左側的交集)
    const static int MAXN = 100005;
    int n;
    Line L[MAXN], s[MAXN];
    vector<P> a; //結果存在這，是一個凸包
    void init() { n = 0; }
    void add_Line(Line l) { L[n++] = l; }
    bool OnLeft(Line l, P p) { return dcmp(l.v ^ (p - l.p)) >= 0; }
    int solve(){
        a.clear();
        sort(L, L + n); //sort
        int first, last;
        P *p = new P[n];
        Line *q = new Line[n];
        q[first = last = 0] = L[0];
        for (int i = 1; i < n; i++){
            while (first < last && !OnLeft(L[i], p[last - 1]))
                last--;
            while (first < last && !OnLeft(L[i], p[first]))
                first++;
            q[++last] = L[i];
            if (dcmp(q[last].v ^ q[last - 1].v) == 0){
                last--;
                if (OnLeft(q[last], L[i].p))
                    q[last] = L[i];
            }
            if (first < last)
                p[last - 1] = LineIntersect(q[last - 1], q[last]);
        }
        while (first < last && !OnLeft(q[first], p[last - 1]))
            last--;
        if (last - first <= 1)
            return 0;
        p[last] = LineIntersect(q[last], q[first]);

        for (int i = first; i <= last; i++)
            a.push_back(p[i]);
        return a.size();
    }
} hpi;
struct Circle{
    P c;
    type r;
    P point(double a) { return P(c.X + cos(a) * r, c.Y + sin(a) * r); }
};
int LineCircleIntersect(Line L, Circle C, vector<P> &sol){ //返回交點個數，sol存交點們
    type a = L.v.X, b = L.p.X - C.c.X, c = L.v.Y, d = L.p.Y - C.c.Y;
    type e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - C.r * C.r;
    type delta = f * f - 4 * e * g;
    if (dcmp(delta) < 0)
        return 0;
    if (dcmp(delta) == 0)
    {
        sol.push_back(L.p - (f / (2 * e)) * L.v);
        return 1;
    }
    double t1 = (-f - sqrt(delta)) / (2 * e);
    sol.push_back(L.p + t1 * L.v);
    double t2 = (-f + sqrt(delta)) / (2 * e);
    sol.push_back(L.p + t2 * L.v);
    return 2;
}
int CircleIntersect(Circle C1, Circle C2, vector<P> &sol){
    double d = len(C1.c - C2.c);
    if (dcmp(d) == 0){
        if (dcmp(C1.r - C2.r) == 0)
            return -1; //兩圓重合
        return 0;
    }
    if (dcmp(C1.r + C2.r - d) < 0)
        return 0;
    if (dcmp(fabs(C1.r - C2.r) - d) > 0)
        return 0;
    double a = atan2(C2.c.Y - C1.c.Y, C2.c.X - C1.c.X);
    double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));//最好判一下括號裡面是否在[-1,1]
    P p1 = make_pair(C1.c.X + cos(a - da) * C1.r, C1.c.Y + sin(a - da) * C1.r);
    P p2 = make_pair(C1.c.X + cos(a + da) * C1.r, C1.c.Y + sin(a + da) * C1.r);
    sol.push_back(p1);
    if (p1 == p2)
        return 1;
    sol.push_back(p2);
    return 2;
}
int PointCircleTangents(P p, Circle C, vector<P> &sol)
{ //返回切線條數，sol存切線向量們
    P u = C.c - p;
    double dist = len(u);
    if (dist < C.r)
        return 0;
    if (dcmp(dist - C.r) == 0)
    {
        sol.push_back(rotate(u, pi / 2));
        return 1;
    }
    double ang = asin(C.r / dist);
    sol.push_back(rotate(u, -ang));
    sol.push_back(rotate(u, ang));
    return 2;
}
double Circle_Segment_Intersect_area(P A, P B, Circle C)
{ //<圓心和線段兩端點圍成的三角形>與<圓>的交集面積
    P CA = C.c - A, CB = C.c - B;
    double da = len(CA), db = len(CB);
    da = dcmp(da - C.r);
    db = dcmp(db - C.r);

    if (da <= 0 && db <= 0)
        return fabs((CA ^ CB)) * 0.5;

    vector<P> sol;
    int num = LineCircleIntersect(Line{A, B - A}, C, sol);
    double cnt = C.r * C.r;
    P q;

    if (da <= 0 && db > 0){
        q = on(sol[0], A, B) ? sol[0] : sol[1];
        double area = fabs((CA ^ (C.c - q))) * 0.5;
        double ang = acos((CB * (C.c - q)) / len(CB) / len(C.c - q));
        return area + cnt * ang * 0.5;
    }
    if (db <= 0 && da > 0){
        q = on(sol[0], A, B) ? sol[0] : sol[1];
        double area = fabs((CB ^ (C.c - q))) * 0.5;
        double ang = acos((CA * (C.c - q)) / len(CA) / len(C.c - q));
        return area + cnt * ang * 0.5;
    }
    if (num == 2){
        double big_area = cnt * acos((CA * CB) / len(CA) / len(CB)) * 0.5;
        double small_area = cnt * acos(((C.c - sol[0]) * (C.c - sol[1])) / len(C.c - sol[0]) / len(C.c - sol[1])) * 0.5;
        double delta_area = fabs((C.c - sol[0]) ^ (C.c - sol[1])) * 0.5;
        if (!on(sol[0], A, B))
            return big_area;
        return big_area + delta_area - small_area;
    }
    return cnt * acos((CA * CB) / len(CA) / len(CB)) * 0.5;
}

double Circle_Polygon_Intersect_area(vector<P> ps, Circle C)
{ //<多邊形>與<圓>的交集面積
    double res = 0;
    int sz = ps.size();
    for (int i = 0; i < sz; i++) {
        double tmp = Circle_Segment_Intersect_area(ps[i], ps[(i + 1) % sz], C);
        if (((ps[i]-C.c)^(ps[(i + 1) % sz]-C.c)) < 0)
            tmp = -tmp;
        res += tmp;
    }
    if (res < 0)
        res = -res;
    return res;
}
int CircleTangents(Circle A, Circle B, vector<P> &a, vector<P> &b)
{ //返回切線條數，-1表示無窮條切線。a[i]和b[i]分別是第i條切線在圓A與B上的交點
    int cnt = 0;
    if (A.r < B.r) {
        swap(A, B);
        swap(a, b);
    }
    type d2 = (A.c.X - B.c.X) * (A.c.X - B.c.X) + (A.c.Y - B.c.Y) * (A.c.Y - B.c.Y);
    type rdiff = A.r - B.r;
    type rsum = A.r + B.r;
    if (dcmp(d2 - rdiff * rdiff) < 0)
        return 0; //内含

    double base = atan2(B.c.Y - A.c.Y, B.c.X - A.c.X);
    if (dcmp(d2) == 0 && dcmp(A.r - B.r) == 0)
        return -1; //無限多條切線
    if (dcmp(d2 - rdiff * rdiff) == 0)
    { //内切，1條切線
        a.push_back(A.point(base));
        b.push_back(B.point(base));
        cnt++;
        return 1;
    }
    //有外共切線
    double ang = acos((A.r - B.r) / sqrt(d2));
    a.push_back(A.point(base + ang));
    b.push_back(B.point(base + ang));
    cnt++;
    a.push_back(A.point(base - ang));
    b.push_back(B.point(base - ang));
    cnt++;
    if (d2 == rsum * rsum)
    { //一條公切線
        a.push_back(A.point(base));
        b.push_back(B.point(pi + base));
        cnt++;
    }
    else if (d2 > rsum * rsum)
    { //兩條內公切線
        double ang = acos(rsum / sqrt(d2));
        a.push_back(A.point(base + ang));
        b.push_back(B.point(pi + base + ang));
        cnt++;
        a.push_back(A.point(base - ang));
        b.push_back(B.point(pi + base - ang));
        cnt++;
    }
    return cnt;
}
