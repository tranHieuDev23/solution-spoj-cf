#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
vector< pair<int, int> > row[mn], col[mn], dia1[mn << 1], dia2[mn << 1];
int m, n, ans[mn][mn];
char c[mn][mn];
stack< pair<int, int> > st;

void addPoint(pair<int, int> point)
{
    row[point.F].pb(point);
    col[point.S].pb(point);
    dia1[point.F + point.S].pb(point);
    dia2[point.F - point.S + mn].pb(point);
}

void setup()
{
    cin >> m >> n;
    FOR(i, 0, n + 1)
        c[0][i] = '#', addPoint(mp(0, i));
    FOR(i, 1, m)
    {
        c[i][0] = '#', addPoint(mp(i, 0));
        FOR(j, 1, n)
        {
            cin >> c[i][j];
            addPoint(mp(i, j));
        }
        c[i][n + 1] = '#', addPoint(mp(i, n + 1));
    }
    FOR(i, 0, n + 1)
        c[m + 1][i] = '#', addPoint(mp(m + 1, i));
}

void dealWith(vector< pair<int, int> >& vec)
{
    FOR(i, 0, int(vec.size()) - 1)
    {
        int x = vec[i].F;
        int y = vec[i].S;
        if (c[x][y] == '.')
            st.push(vec[i]);
        else
        {
            int val = st.size();
            while(!st.empty())
            {
                x = st.top().F, y = st.top().S;
                ans[x][y] += val;
                st.pop();
            }
        }
    }
}

void xuly()
{
    FOR(i, 1, m)
        dealWith(row[i]);
    FOR(i, 1, n)
        dealWith(col[i]);
    FOR(i, 2, m + n)
        dealWith(dia1[i]);
    FOR(i, 1 - n + mn, m - 1 + mn)
        dealWith(dia2[i]);
    FOR(i, 1, m)
    {
        FOR(j, 1, n)
        {
            if (c[i][j] == '#')
                cout << "0 ";
            else
                cout << ans[i][j] - 3 << ' ';
        }
        cout << '\n';
    }
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
