#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define mn2 80
#define maxC 8000000
#define pb push_back
#define C(x, y) (c[x][y] - fx[x] - fy[y])

using namespace std;
int n, m, arm, ter, posArm[mn], szTer, d[mn2][mn];
int Queue[mn];
vector<int> g[mn];

int c[mn2][mn2], fx[mn2], fy[mn2], ans = 0;
int matchX[mn2], matchY[mn2], trace[mn2];
int reachX[mn2], reachY[mn2], numX, numY;
int inReachY[mn2], co = 0;

void setup()
{
    cin >> n >> m >> arm >> ter;
    FOR(i, 1, arm)
        cin >> posArm[i];
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    szTer = g[ter].size();
}

void bfs(int id, int st)
{
    FOR(i, 1, n)
        d[id][i] = maxC;
    d[id][st] = 0;
    int l = 1, r = 1;
    Queue[1] = st;
    while(l <= r)
    {
        int u = Queue[l ++];
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i];
            if (d[id][v] != maxC)
                continue;
            d[id][v] = d[id][u] + 1;
            Queue[++ r] = v;
        }
    }
}

void prepareMatch()
{
    FOR(i, 1, szTer)
        bfs(i, g[ter][i - 1]);
    FOR(i, 1, arm)
    {
        int u = posArm[i];
        FOR(j, 1, szTer)
            c[i][j] = d[j][u];
    }
}

int findArgumentPath(int s)
{
    co ++;
    numX = numY = 0;
    int l = 1, r = 1;
    Queue[1] = s;
    while(l <= r)
    {
        int u = Queue[l ++];
        reachX[++ numX] = u;
        FOR(v, 1, arm)
        if (inReachY[v] != co && C(u, v) == 0)
        {
            inReachY[v] = co;
            reachY[++ numY] = v;
            trace[v] = u;
            if (!matchY[v])
                return v;
            Queue[++ r] = matchY[v];
        }
    }
    return 0;
}

void changeEdge()
{
    int delta = maxC;
    FOR(i, 1, numX)
    {
        int u = reachX[i];
        FOR(v, 1, arm)
        if (inReachY[v] != co)
            delta = min(delta, C(u, v));
    }

    FOR(i, 1, numX)
        fx[reachX[i]] += delta;
    FOR(i, 1, numY)
        fy[reachY[i]] -= delta;
}

void Argumenting(int y)
{
    while(inReachY[y] == co)
    {
        int x = trace[y];
        int nex = matchX[x];
        matchX[x] = y;
        matchY[y] = x;
        y = nex;
    }
}

void hungarian()
{
    FOR(i, 1, arm)
    while(true)
    {
        int y = findArgumentPath(i);
        if (y)
        {
            Argumenting(y);
            break;
        }
        changeEdge();
    }

    FOR(i, 1, arm)
        ans += c[i][matchX[i]];
}

void xuly()
{
    prepareMatch();
    hungarian();
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("ATTACK.INP", "r", stdin);
    freopen("ATTACK.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
