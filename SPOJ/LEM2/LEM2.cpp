#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 2000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, k, d[mn], allOne, beg, fin, change[21];
queue<int> q;

void setup()
{
    cin >> n >> k;
    allOne = (1 << n) - 1;
    fin = 1 << (k - 1);
    int s, x;
    FOR(i, 1, n)
    {
        cin >> s;
        change[i] = allOne;
        FOR(j, 1, s)
        {
            cin >> x;
            change[i] ^= 1 << (x - 1);
        }
    }
    FOR(i, 1, n)
    {
        cin >> x;
        beg |= x << (i - 1);
    }
}

int nex(int state, int x)
{
    state &= change[x];
    state |= 1 << (x - 1);
    return state;
}

void xuly()
{
    memset(d, 60, sizeof(int) * (allOne + 1));
    d[beg] = 0;
    q.push(beg);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        if (u == fin)
        {
            cout << d[u];
            return;
        }
        FOR(i, 1, n)
        {
            int v = nex(u, i);
            if (d[v] > d[u] + 1)
            {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    cout << -1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    setup ();
    xuly ();
    return 0;
}
