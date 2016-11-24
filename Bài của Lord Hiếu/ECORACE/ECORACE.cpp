#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 202
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define epsilon 0.000000001
#define pi 3.1415926535

using namespace std;
struct TPoint
{
    long long x, y;

    TPoint(long long x = 0, long long y = 0): x(x), y(y) {};

    TPoint(TPoint& a, TPoint& b)
    {
        x = b.x - a.x;
        y = b.y - a.y;
    }

    long long squareLength()
    {
        return x * x + y * y;
    }

    double length()
    {
        return sqrt(1.0 * squareLength());
    }
};
typedef TPoint TVector;

double Distance(TPoint& a, TPoint& b)
{
    return TVector(a, b).length();
}

double Cos(TPoint& a, TPoint& b, TPoint& c)
{
    TVector vecAB = TVector(a, b);
    TVector vecBC = TVector(b, c);
    long long numerator = vecAB.x * vecBC.x + vecAB.y * vecBC.y;
    double denominator = vecAB.length() * vecBC.length();
    return 1.0 / denominator * numerator;
}

int n, m, d;
TPoint point[mn];
vector< pair<int, double> > g[mn];
priority_queue< pair< double, pair<int, int> > > p;
double best[mn][mn];

void setup()
{
    cin >> n >> m >> d;
    FOR(i, 1, n)
        cin >> point[i].x >> point[i].y;
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        g[u].pb(mp(v, Distance(point[u], point[v])));
    }
}

bool check(double x)
{
    FOR(i, 1, n)
    FOR(j, 1, n)
        best[i][j] = epsilon + d;
    while(!p.empty())
        p.pop();

    FOR(i, 0, int(g[1].size()) - 1)
    {
        int v = g[1][i].F;
        double w = g[1][i].S;
        if (best[v][1] > w)
        {
            best[v][1] = w;
            p.push(mp(-w, mp(v, 1)));
        }
    }

    while(!p.empty())
    {
        int u = p.top().S.F;
        int z = p.top().S.S;
        double w = - p.top().F;
        p.pop();
        if (w != best[u][z])
            continue;
        if (u == n)
            return w <= d;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            double cosZUV = Cos(point[z], point[u], point[v]);
            if (cosZUV < x)
                continue;
            double e = g[u][i].S;
            if (best[v][u] <= w + e)
                continue;
            best[v][u] = w + e;
            p.push(mp(- best[v][u], mp(v, u)));
        }
    }
    return false;
}

double arccos(double x)
{
    double rad = acos(x);
    double ret = (rad / pi) * 180;
    if (abs(ret - 0) <= epsilon)
        ret = 180;
    return ret;
}

void xuly()
{
    if (!check(-1))
    {
        cout << -1;
        return;
    }
    double l = -1.0, r = 1.0 + epsilon;
    while(r - l > epsilon)
    {
        double g = (l + r) / 2;
        if (check(g))
            l = g;
        else
            r = g;
    }
    cout << fixed << setprecision(7) << arccos(l);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("ECORACE.INP", "r", stdin);
    freopen("ECORACE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
