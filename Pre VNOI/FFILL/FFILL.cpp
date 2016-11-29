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
int belong[mn][mn], co;
int addX[] = {0, 0, -1, 1};
int addY[] = {-1, 1, 0, 0};
bool done[mn][mn];

struct linkedInt
{
    int val;
    linkedInt* next;

    linkedInt(int val = 0): val(val)
    {
        next = NULL;
    }
};

struct region
{
    int rootA, mark, sizeP;
    linkedInt* startV;
    linkedInt* lastV;
    char character;

    region(char character = 0): character(character)
    {
        rootA = mark = -1;
        sizeP = 0;
        startV = lastV = NULL;
    }

    void addEdge(int v)
    {
        linkedInt* cur = new linkedInt(v);
        if (startV == NULL)
            startV = cur;
        else
            lastV -> next = cur;
        lastV = cur;
    }
};

vector<region> reg;

int getRoot(int x)
{
    if (reg[x].rootA == -1)
        return x;
    return (reg[x].rootA = getRoot(reg[x].rootA));
}

void setup()
{
    cin >> m >> n;
    FOR(x, 1, m)
    FOR(y, 1, n)
    {
        cin >> c[x][y];
        belong[x][y] = -1;
    }
    cin >> q;
}

void dfsAddPoint(int x, int y)
{
    belong[x][y] = area - 1;
    reg[area - 1].sizeP ++;
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

    FOR(x, 1, m)
    FOR(y, 1, n)
    if (!done[x][y])
        dfsAddEdge(x, y, belong[x][y]);

    co = area;
}

int temp[mn2];

void combine(int a, int b)
{
    reg[b].rootA = a;
    reg[a].sizeP += reg[b].sizeP;

    if (reg[b].startV != NULL)
    {
        if (reg[a].startV == NULL)
            reg[a].startV = reg[b].startV;
        else
            reg[a].lastV -> next = reg[b].startV;
        reg[a].lastV = reg[b].lastV;
    }
}

void query(int u, char c)
{
    if (c == reg[u].character)
        return;
    reg[u].character = c;
    reg[u].mark = ++ co;
    int r = 0, sumSz = 0;
    for(linkedInt* x = reg[u].startV; x != NULL; x = x -> next)
    {
        int v = getRoot(x -> val);
        if (reg[v].mark == co)
            continue;
        reg[v].mark = co;
        temp[++ r] = v;
        sumSz += reg[v].sizeP;
    }
    area -= r, best = max(best, reg[u].sizeP + sumSz);
    reg[u].startV = reg[u].lastV = NULL;
    FOR(i, 1, r)
        combine(u, temp[i]);
}

void xuly()
{
    prepare();
    char c;
    int x, y;
    while(q --)
    {
        cin >> c >> x >> y;
        query(getRoot(belong[x][y]), c);
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
