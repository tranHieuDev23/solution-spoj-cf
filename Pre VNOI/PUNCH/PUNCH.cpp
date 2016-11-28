#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define bitPos(i) (1 << (i))
#define isOne(x, i) (((x) >> (i)) & 1)

using namespace std;
int n, num[1 << 16], next[1 << 16];
bool mark[1 << 16];
int a[4][4] = {
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 10, 11},
    {12, 13, 14, 15}
};
int b[4][4] = {
    {3, 7, 11, 15},
    {2, 6, 10, 14},
    {1, 5, 9, 13},
    {0, 4, 8, 12}
};

void calcNext(int x)
{
    if (mark[x])
        return;
    mark[x] = true;
    FOR(i, 0, 3)
    FOR(j, 0, 3)
    if (isOne(x, a[i][j]))
        next[x] |= bitPos(b[i][j]);
    calcNext(next[x]);
}

void setup()
{
    FOR(i, 0, (1 << 16) - 1)
        calcNext(i);
    cin >> n;
    int x;
    FOR(i, 1, n)
    {
        cin >> x;
        num[x] ++;
    }
}

int pierce(int x, int i, int j)
{
    int re = 2, cur = x;
    while(true)
    {
        re = min(re, (isOne(cur, i) ^ 1) + (isOne(cur, j) ^ 1));
        cur = next[cur];
        if (cur == x)
            break;
    }
    return re * num[x];
}

void xuly()
{
    int ans = maxC;
    FOR(i, 0, 14)
    FOR(j, i + 1, 15)
    {
        int sum = 0;
        FOR(k, 0, (1 << 16) - 1)
        if (num[k])
            sum += pierce(k, i, j);
        ans = min(ans, sum);
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("PUNCH.INP", "r", stdin);
    freopen("PUNCH.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
