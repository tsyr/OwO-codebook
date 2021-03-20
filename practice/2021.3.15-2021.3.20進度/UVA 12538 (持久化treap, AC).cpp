// https://vjudge.net/problem/UVA-12538
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
#define maxn 30000005

struct Treap
{
    static Treap mem[maxn], *pmem;
    int sz, pri, tag;
    char val;
    Treap *l, *r;
    Treap() {}
    Treap(char _val)
    {
        val = _val;
        sz = 1;
        pri = rand();
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
        a->l = a->r, a->r = swp;
        if (a->l)
            a->l->tag ^= 1;
        if (a->r)
            a->r->tag ^= 1;
        a->tag = 0;
    }
}
int Size(Treap *a) { return a ? a->sz : 0; }
void pull(Treap *a)
{
    a->sz = Size(a->l) + Size(a->r) + 1;
}
Treap *merge(Treap *a, Treap *b)
{
    if (!a || !b)
        return a ? a : b;
    if (a->pri > b->pri)
    {
        push(a);
        Treap *t = new (Treap::pmem++) Treap(*a);
        t->r = merge(a->r, b);
        pull(t);
        return t;
    }
    else
    {
        push(b);
        Treap *t = new (Treap::pmem++) Treap(*b);
        t->l = merge(a, b->l);
        pull(t);
        return t;
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
        a = new (Treap::pmem++) Treap(*t);
        split(t->r, k - Size(t->l) - 1, a->r, b);
        pull(a);
    }
    else
    {
        b = new (Treap::pmem++) Treap(*t);
        split(t->l, k, a, b->l);
        pull(b);
    }
}

Treap *rt[500005];
string s;

void print(Treap *t)
{
    if (!t)
        return;
    print(t->l);
    s.push_back(t->val);
    print(t->r);
}

int main()
{
    //freopen("4-16.in", "r", stdin);
    //freopen("a218_09.out", "w", stdout);
    //std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int q;
    scanf("%d", &q);
    Treap::pmem = Treap::mem;
    rt[0] = NULL;
    int ver = 0, d = 0;
    while (q--)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int p;
            char s[105];
            scanf("%d%s", &p, s);
            p -= d;
            Treap *a, *b;
            split(rt[ver], p, a, b);
            Treap *c = NULL;
            int l = strlen(s);
            for (int i = 0; i < l; i++)
                c = merge(c, new (Treap::pmem++) Treap(s[i]));
            rt[++ver] = merge(merge(a, c), b);
        }
        else if (type == 2)
        {
            int p, c;
            scanf("%d%d", &p, &c);
            p -= d, c -= d;
            Treap *l, *m, *r;
            split(rt[ver], p - 1, l, m);
            split(m, c, m, r);
            rt[++ver] = merge(l, r);
        }
        else
        {
            int v, p, c;
            scanf("%d%d%d", &v, &p, &c);
            v -= d, p -= d, c -= d;
            Treap *l, *m, *r;
            split(rt[v], p - 1, l, m);
            split(m, c, m, r);
            s.clear();
            print(m);
            cout << s << "\n";
            for (int i = 0; i < s.length(); i++)
                if (s[i] == 'c')
                    d++;
        }
    }

    return 0;
}
