#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define mn2 500005
#define maxC 100000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int k, sz[mn], allVal[mn2], n = 0;
int num[mn2], dif = 0, ans = -1;
vector<int> g[mn];
priority_queue< pair<int, int> > p;

void setup()
{
    cin >> k;
    FOR(i, 1, k)
    {
        cin >> sz[i];
        if (sz[i] == 0)
        {
            cout << 'x';
            exit(0);
        }
    }

    int x;
    FOR(i, 1, k)
    FOR(j, 1, sz[i])
    {
        cin >> x;
        g[i].pb(x);
        allVal[++ n] = x;
    }
}

int Map(int x)
{
    return lower_bound(allVal + 1, allVal + n + 1, x) - allVal;
}

void add(int x, int id)
{
    p.push(mp(-x, id));
    dif += (++ num[x] == 1);
}

int del()
{
    int x = -p.top().F;
    int id = p.top().S;
    p.pop();
    dif -= (-- num[x] == 0);
    return id;
}

void prepare()
{
    sort(allVal + 1, allVal + n + 1);
    FOR(i, 1, k)
    {
        sort(g[i].begin(), g[i].end(), greater<int>());
        FOR(j, 0, sz[i] - 1)
            g[i][j] = Map(g[i][j]);
        add(g[i][sz[i] - 1], i);
    }
}

bool check()
{
    if (dif == 1)
    {
        ans = -p.top().F;
        return false;
    }
    int id = del();
    if (-- sz[id] == 0)
        return false;
    add(g[id][sz[id] - 1], id);
    return true;
}

void xuly()
{
    prepare();
    while(check());
    if (ans == -1)
        cout << 'x';
    else
        cout << allVal[ans];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("PTC.INP", "r", stdin);
    freopen("PTC.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
