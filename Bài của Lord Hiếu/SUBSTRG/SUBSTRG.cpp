#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define mn2 100
#define maxC 1000000007
#define pb push_back

using namespace std;
string t, p;
int n, m, T[mn], P[mn], preT[mn][mn2], preP[mn][mn2];
int f[mn], valR[mn2], valB[mn2];
vector<int> ans;

void setup()
{
    cin >> t >> p;
    n = t.size();
    m = p.size();
}

void prepare()
{
    FOR(i, 1, n)
    {
        T[i] = t[i - 1] - 32;
        FOR(j, 1, 94)
            preT[i][j] = preT[i - 1][j];
        preT[i][T[i]] = i;
    }
    FOR(i, 1, m)
    {
        P[i] = p[i - 1] - 32;
        FOR(j, 1, 94)
            preP[i][j] = preP[i - 1][j];
        preP[i][P[i]] = i;
    }
}

bool check(int id, int val)
{
    int x = valR[val];
    int y = valB[P[id + 1]];
    if (x && x != P[id + 1])
        return false;
    if (y && y != val)
        return false;
    return true;
}

void lowerId(int& id, int (&mang)[mn][mn2], int pos, bool includePos)
{
    id = f[id];
    int low = pos - id + includePos;
    memset(valR, 0, sizeof(valR));
    memset(valB, 0, sizeof(valB));
    FOR(i, 1, 94)
    {
        int x = mang[pos - (!includePos)][i];
        if (x < low)
            continue;
        int y = x - low + 1;
        valR[i] = P[y];
        valB[P[y]] = i;
    }
}

void buildF()
{
    f[0] = -1, f[1] = 0;
    int id = 0;
    FOR(i, 2, m)
    {
        while(!check(id, P[i]))
            lowerId(id, preP, i, false);
        f[i] = ++ id;
        valR[P[i]] = P[id];
        valB[P[id]] = P[i];
    }
}

void findOccurance()
{
    memset(valR, 0, sizeof(valR));
    memset(valB, 0, sizeof(valB));
    int id = 0;
    FOR(i, 1, n)
    {
        while(!check(id, T[i]))
            lowerId(id, preT, i, false);
        if (++ id == m)
        {
            ans.pb(i - m + 1);
            lowerId(id, preT, i, true);
        }
        valR[T[i]] = P[id];
        valB[P[id]] = T[i];
    }
}

void xuly()
{
    prepare();
    buildF();
    findOccurance();
    cout << ans.size() << '\n';
    FOR(i, 0, int(ans.size()) - 1)
        cout << ans[i] << ' ';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("SUBSTRG.INP", "r", stdin);
    freopen("SUBSTRG.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
