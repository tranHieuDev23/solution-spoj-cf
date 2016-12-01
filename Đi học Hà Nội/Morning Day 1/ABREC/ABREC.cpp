#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 60004
#define mn2 252
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define mid (l + ((r - l + 1) >> 1) - 1)
#define lc (id << 1)
#define rc (lc + 1)

using namespace std;

void scanInt(int& x)
{
    char c = ' ';
    while(c == ' ' || c == '\n')
        c = getchar();
    if (c == EOF)
        return;
    x = c - '0';
    while(true)
    {
        c = getchar();
        if (c == ' ' || c == '\n' || c == EOF)
            return;
        x = x * 10 + c - '0';
    }
}

void printInt(int x)
{
    if (!x)
    {
        putchar('0');
        return;
    }
    bool okZero = false;
    for(int i = 1000000000; i; i /= 10)
    {
        int digit = x / i;
        x %= i;
        if (digit)
            okZero = true, putchar('0' + digit);
        else if (okZero)
            putchar('0');
    }
}

int m, n, k, a[mn2][mn];
int sum[mn2][mn], sub = 0, ans;

struct interval
{
    int tree[mn << 3];

    void update(int l, int r, int id, int x, int v)
    {
        if (l > x || r < x)
            return;
        if (l == r)
        {
            tree[id] = min(tree[id], v);
            return;
        }
        update(l, mid, lc, x, v);
        update(mid + 1, r, rc, x, v);
        tree[id] = min(tree[lc], tree[rc]);
    }

    int get(int l, int r, int id, int x, int y)
    {
        if (l > y || r < x)
            return mn;
        if (x <= l && r <= y)
            return tree[id];
        int a = get(l, mid, lc, x, y);
        int b = get(mid + 1, r, rc, x, y);
        return min(a, b);
    }
} t;

void setup()
{
    scanInt(m), scanInt(n), scanInt(k);
    char c;
    if (m < n)
    {
        FOR(i, 1, m)
        {
            FOR(j, 1, n)
            {
                c = getchar();
                a[i][j] = (c == 'A'? 1 : -1);
            }
            getchar();
        }
    }
    else
    {
        FOR(i, 1, m)
        {
            FOR(j, 1, n)
            {
                c = getchar();
                a[n - j + 1][i] = (c == 'A'? 1 : -1);
            }
            getchar();
        }
        swap(m, n);
    }
}

void prepare()
{
    ans = 0;

    FOR(i, 1, m)
    FOR(j, 1, n)
        sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
}

void deal(int u, int d)
{
    sub -= n + 1;
    int high = (d - u + 1) * n;
    t.update(-high, high, 1, 0, 0 + sub);
    FOR(r, 1, n)
    {
        int val = sum[d][r] - sum[u - 1][r];
        int l = t.get(-high, high, 1, val - k, val + k) - sub;
        if (l < r)
            ans = max(ans, (d - u + 1) * (r - l));
        t.update(-high, high, 1, val, r + sub);
    }
}

void xuly()
{
    prepare();
    FOR(i, 1, m)
    FOR(j, i, m)
        deal(i, j);
    printInt(ans), putchar('\n');
}

int main()
{
    freopen("ABREC.INP", "r", stdin);
    freopen("ABREC.OUT", "w", stdout);
    int t; scanInt(t);
    while(t --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
