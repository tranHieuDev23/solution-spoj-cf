#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 2003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, k, d[mn], way[mn];
string s[mn];
vector<int> g[mn];
queue<int> q;

void setup()
{
    cin >> n >> k;
    cin >> s[0] >> s[n + 1];
    k = s[0].size();
    FOR(i, 1, n)
        cin >> s[i];
}

bool difOne(int a, int b)
{
    int dem = 0;
    FOR(i, 0, k - 1)
    if (s[a][i] != s[b][i])
        if (++ dem == 2)
            return false;
    return dem == 1;
}

void prepare()
{
    FOR(i, 0, n)
    FOR(j, i + 1, n + 1)
    if (difOne(i, j))
    {
        g[i].pb(j);
        g[j].pb(i);
    }

    memset(d, 60, sizeof(int) * (n + 2));
    d[0] = 0, way[0] = 1;
}

void calc()
{
    q.push(0);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i];
            if (d[v] == d[u] + 1)
                way[v] = (way[v] + way[u]) % maxC;
            if (d[v] > d[u] + 1)
            {
                d[v] = d[u] + 1;
                way[v] = way[u];
                q.push(v);
            }
        }
    }
}

void xuly()
{
    if (s[0] == s[n + 1])
    {
        cout << "0 1";
        return;
    }
    prepare();
    calc();
    if (way[n + 1] == 0)
        cout << "-1 -1";
    else
        cout << d[n + 1] << ' ' << way[n + 1];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("STRING.INP", "r", stdin);
    freopen("STRING.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
