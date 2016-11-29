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
int area, best;

int belong[mn][mn], co;
int addX[] = {0, 0, 1, -1};
int addY[] = {1, -1, 0, 0};
bool done[mn][mn];
pair<int, int> nextP[mn][mn];
vector<int> val, nextV;

struct region
{
    pair<int, int> startP, lastP;
    int sizeP, root, startV, lastV, mark;
    char character;

    region(char character = 0): character(character)
    {
        startP = lastP = mp(0, 0);
        sizeP = 0;
        root = startV = lastV = mark = -1;
    }

    void addPoint(int x, int y)
    {
        pair<int, int> xy = mp(x, y);
        pair<int, int> z = lastP;
        if (!z.F)
            startP = xy;
        else
            nextP[z.F][z.S] = xy;
        nextP[x][y] = mp(0, 0);
        lastP = xy;
        sizeP ++;
    }

    void addEdge(int v)
    {
        int cur = val.size();
        val.pb(v);
        int pre = lastV;
        if (pre == -1)
            startV = cur;
        else
            nextV[pre] = cur;
        lastV = cur;
        nextV.pb(-1);
    }
};
vector<region> reg;

int getRoot(int x)
{
    if (reg[x].root == -1)
        return x;
    return (reg[x].root = getRoot(reg[x].root));
}

void merging(int a, int b)
{
    if (a == b)
        return;
    if (reg[a].sizeP < reg[b].sizeP)
        swap(a, b);
    reg[b].root = a;

    for(pair<int, int> x = reg[b].startP; x.F; x = nextP[x.F][x.S])
        belong[x.F][x.S] = a;
    pair<int, int> p1 = reg[a].lastP;
    pair<int, int> p2 = reg[b].startP;
    nextP[p1.F][p1.S] = p2;
    reg[a].lastP = reg[b].lastP;
    reg[a].sizeP += reg[b].sizeP;

    if (reg[b].startV != -1)
    {
        int v1 = reg[a].lastV;
        int v2 = reg[b].startV;
        if (v1 == -1)
            reg[a].startV = v2;
        else
            nextV[v1] = v2;
        reg[a].lastV = reg[b].lastV;
    }
}

void dfsAddPoint(int x, int y)
{
    belong[x][y] = area - 1;
    reg[area - 1].addPoint(x, y);
    FOR(i, 0, 3)
    {
        int _x = x + addX[i];
        int _y = y + addY[i];
        if (c[_x][_y] == c[x][y] && belong[_x][_y] == -1)
            dfsAddPoint(_x, _y);
    }
}

void dfsAddEdge(int x, int y, int u)
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
            if (reg[v].mark != u)
                reg[v].mark = u, reg[u].addEdge(v);
        }
        else if (!done[_x][_y])
            dfsAddEdge(_x, _y, u);
    }
}

void setup()
{
    cin >> m >> n;
    FOR(i, 1, m)
    FOR(j, 1, n)
        cin >> c[i][j], belong[i][j] = -1;
    cin >> q;
}

void prepare()
{
    FOR(x, 1, m)
    FOR(y, 1, n)
    if (belong[x][y] == -1)
    {
        area ++;
        reg.pb(region(c[x][y]));
        dfsAddPoint(x, y);
        best = max(best, reg[area - 1].sizeP);
    }

    FOR(u, 0, area - 1)
    {
        int x = reg[u].startP.F;
        int y = reg[u].startP.S;
        dfsAddEdge(x, y, u);
    }

    co = area;
}

int temp[mn2];

void query(int u, char c)
{
    if (reg[u].character == c)
        return;
    reg[u].character = c;
    reg[u].mark = ++ co;
    int r = 0, sumSz = 0;
    for(int x = reg[u].startV; x != -1; x = nextV[x])
    {
        int v = getRoot(val[x]);
        if (reg[v].mark == co)
            continue;
        reg[v].mark = co;
        temp[++ r] = v;
        sumSz += reg[v].sizeP;
    }
    area -= r, best = max(best, reg[u].sizeP + sumSz);
    reg[u].startV = reg[u].lastV = -1;
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
