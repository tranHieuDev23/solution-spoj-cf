#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define mn2 1000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int m, n, q;
char c[mn][mn];
int area = 0, best = 0;

int belong[mn][mn];
int addX[] = {0, 0, 1, -1};
int addY[] = {1, -1, 0, 0};
vector<int> sizP;
vector<char> charArea;
vector< pair<int, int> > startP, lastP;
pair<int, int> nextP[mn][mn];

vector<int> startV, lastV, root;
vector<int> val, nextV, mark;
bool done[mn][mn];

int temp[mn2], co, r;

void setup()
{
    cin >> m >> n;
    FOR(i, 1, m)
    FOR(j, 1, n)
        cin >> c[i][j], belong[i][j] = -1;
    cin >> q;
}

void prepareArea(char& c)
{
    root.pb(area ++);
    charArea.pb(c);
    sizP.pb(0);
    startP.pb(mp(0, 0)), lastP.pb(mp(0, 0));
    startV.pb(-1), lastV.pb(-1);
    mark.pb(-1);
}

void addPoint(int x, int y, int u)
{
    belong[x][y] = u;
    pair<int, int> xy = mp(x, y);
    pair<int, int> z = lastP[u];
    if (!z.F)
        startP[u] = lastP[u] = xy;
    else
        nextP[z.F][z.S] = xy;
    lastP[u] = xy;
    nextP[x][y] = mp(0, 0);
    sizP[u] ++;
}

void dfs(int x, int y)
{
    addPoint(x, y, area - 1);
    FOR(i, 0, 3)
    {
        int _x = x + addX[i];
        int _y = y + addY[i];
        if (c[_x][_y] == c[x][y] && belong[_x][_y] == -1)
            dfs(_x, _y);
    }
}

void addEdge(int u, int v)
{
    int cur = val.size();
    val.pb(v);
    nextV.pb(-1);
    int pre = lastV[u];
    if (pre == -1)
        startV[u] = lastV[u] = cur;
    else
        nextV[pre] = cur;
    lastV[u] = cur;
}

void dfs(int x, int y, int u)
{
    done[x][y] = true;
    FOR(i, 0, 3)
    {
        int _x = x + addX[i];
        int _y = y + addY[i];
        if (c[_x][_y] == 0)
            continue;
        if (c[_x][_y] != c[x][y])
        {
            int v = belong[_x][_y];
            if (mark[v] != u)
                mark[v] = u, addEdge(u, v);
        }
        else if (!done[_x][_y])
            dfs(_x, _y, u);
    }
}

void prepare()
{
    FOR(x, 1, m)
    FOR(y, 1, n)
    if (belong[x][y] == -1)
    {
        prepareArea(c[x][y]);
        dfs(x, y);
        best = max(best, sizP[area - 1]);
    }
    FOR(u, 0, area - 1)
    {
        int x = startP[u].F;
        int y = startP[u].S;
        dfs(x, y, u);
    }
    co = area;
}

int getRoot(int x)
{
    if (root[x] == x)
        return x;
    return (root[x] = getRoot(root[x]));
}

void merging(int a, int b)
{
    if (sizP[a] < sizP[b])
        swap(a, b);
    root[b] = a;
    for(pair<int, int> x = startP[b]; x.F; x = nextP[x.F][x.S])
        belong[x.F][x.S] = a;

    pair<int, int> x1 = lastP[a];
    pair<int, int> x2 = startP[b];
    nextP[x1.F][x1.S] = x2;
    lastP[a] = lastP[b];
    sizP[a] += sizP[b];

    if (lastV[b] != -1)
    {
        int v1 = lastV[a];
        int v2 = startV[b];
        if (v1 == -1)
            startV[a] = v2;
        else
            nextV[v1] = v2;
        lastV[a] = lastV[b];
    }
}

void query(int u, char c)
{
    if (c == charArea[u])
        return;
    charArea[u] = c;
    mark[u] = ++ co;
    r = 0;
    int sumSz = 0;
    for(int x = startV[u]; x != -1; x = nextV[x])
    {
        int v = getRoot(val[x]);
        if (mark[v] != co)
        {
            mark[v] = co;
            temp[++ r] = v;
            sumSz += sizP[v];
        }
    }
    area -= r, best = max(best, sizP[u] + sumSz);
    startV[u] = lastV[u] = -1;
    FOR(i, 1, r)
        merging(getRoot(u), temp[i]);
}

void xuly()
{
    prepare();
    char c;
    int x, y;
    while(q --)
    {
        cin >> c >> x >> y;
        query(belong[x][y], c);
        cout << area << ' ' << best << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("FFILL.INP", "r", stdin);
    freopen("FFILL.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
