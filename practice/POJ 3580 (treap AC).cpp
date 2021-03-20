// http://poj.org/problem?id=3580
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <limits.h>
#include <math.h>
#include <set>
#include <string.h>
#include <math.h>
using namespace std;
#define ll long long
typedef pair<int, int> P;
#define maxn 200005

struct Treap
{
    static Treap mem[maxn], *pmem;
    int sz, tag;
    ll val, small, add, pri;
    Treap *l, *r;
    Treap() {}
    Treap(ll _val)
    {
        small = val = _val;
        add = 0;
        pri = rand() * rand();
        sz = 1;
        l = r = NULL;
        tag = 0;
    }
} Treap::mem[maxn], *Treap::pmem = Treap::mem;
// new (Treap::pmem++) Treap(?)
// void solve(){ ... (最後清空)Treap::pmem = Treap::mem;}
void push(Treap *a)
{
    if (a->tag)
    {
        Treap *swp = a->l;
        a->l = a->r;
        a->r = swp;
        if (a->l)
            a->l->tag ^= 1;
        if (a->r)
            a->r->tag ^= 1;
        a->tag = 0;
    }
    if (a->add)
    {
        a->val += a->add;
        if (a->l)
            a->l->add += a->add;
        if (a->r)
            a->r->add += a->add;
        a->add = 0;
    }
}
int Size(Treap *a) { return a ? a->sz : 0; }
void pull(Treap *a)
{
    a->sz = Size(a->l) + Size(a->r) + 1;
    a->small = a->val;
    if (a->l)
        a->small = min(a->small, a->l->small + a->l->add);
    if (a->r)
        a->small = min(a->small, a->r->small + a->r->add);
}
Treap *merge(Treap *a, Treap *b)
{
    if (!a || !b)
        return a ? a : b;
    if (a->pri > b->pri)
    {
        push(a);
        a->r = merge(a->r, b);
        pull(a);
        return a;
    }
    else
    {
        push(b);
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}
void split(Treap *t, int k, Treap *&a, Treap *&b)
{
    if (!t)
    {
        a = b = NULL;
        return;
    }
    push(t);
    if (Size(t->l) + 1 <= k)
    {
        a = t;
        split(t->r, k - Size(t->l) - 1, a->r, b);
        pull(a);
    }
    else
    {
        b = t;
        split(t->l, k, a, b->l);
        pull(b);
    }
}

int main()
{
    //freopen("4-16.in", "r", stdin);
    //freopen("a218_09.out", "w", stdout);
    //std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n;
    scanf("%d", &n);
    Treap::pmem = Treap::mem;
    Treap *rt = NULL;
    for (int i = 1; i <= n; i++)
    {
        ll now;
        scanf("%lld", &now);
        rt = merge(rt, new (Treap::pmem++) Treap(now));
    }
    int q;
    scanf("%d", &q);
    while (q--)
    {
        char s[10];
        scanf("%s", s);
        if (s[0] == 'A')
        { //add x,y,D
            int x, y;
            ll D;
            scanf("%d%d%lld", &x, &y, &D);
            Treap *tl, *tr;
            split(rt, x - 1, tl, rt);
            split(rt, y - x + 1, rt, tr);
            rt->add += D;
            rt = merge(merge(tl, rt), tr);
        }
        else if (s[0] == 'R' && s[3] == 'E')
        { //reverse
            int x, y;
            scanf("%d%d", &x, &y);
            Treap *tl, *tr;
            split(rt, x - 1, tl, rt);
            split(rt, y - x + 1, rt, tr);
            rt->tag = 1;
            rt = merge(merge(tl, rt), tr);
        }
        else if (s[0] == 'R' && s[3] == 'O')
        { //revolve
            int x, y, T;
            scanf("%d%d%d", &x, &y, &T);
            T %= (y - x + 1);
            Treap *tl, *tr;
            split(rt, x - 1, tl, rt);
            split(rt, y - x + 1, rt, tr);
            Treap *r;
            split(rt, y - x + 1 - T, rt, r);
            rt = merge(r, rt);
            rt = merge(merge(tl, rt), tr);
        }
        else if (s[0] == 'I')
        { //insert
            int x;
            ll P;
            scanf("%d%lld", &x, &P);
            Treap *r;
            split(rt, x, rt, r);
            rt = merge(merge(rt, new (Treap::pmem++) Treap(P)), r);
        }
        else if (s[0] == 'D')
        { //delete
            int x;
            scanf("%d", &x);
            Treap *tl, *tr;
            split(rt, x - 1, tl, rt);
            split(rt, 1, rt, tr);
            rt = merge(tl, tr);
        }
        else
        { //min
            int x, y;
            scanf("%d%d", &x, &y);
            Treap *tl, *tr;
            split(rt, x - 1, tl, rt);
            split(rt, y - x + 1, rt, tr);
            push(rt);
            printf("%lld\n", rt->small);
            rt = merge(merge(tl, rt), tr);
        }
    }

    return 0;
}
