#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 2003
#define mn2 200005
#define st 1001
#define maxC 100000000000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
struct table
{
    int a[mn][mn], ans[6];
    pair<int, int> position[mn2];

    pair<int, int> next(pair<int, int> pos, int dir)
    {
        if (dir == 0)
            return mp(pos.F - 1, pos.S);
        if (dir == 1)
        {
            if (pos.S & 1)
                return mp(pos.F, pos.S + 1);
            return mp(pos.F - 1, pos.S + 1);
        }
        if (dir == 2)
        {
            if (pos.S & 1)
                return mp(pos.F + 1, pos.S + 1);
            return mp(pos.F, pos.S + 1);
        }
        if (dir == 3)
            return mp(pos.F + 1, pos.S);
        if (dir == 4)
        {
            if (pos.S & 1)
                return mp(pos.F + 1, pos.S - 1);
            return mp(pos.F, pos.S - 1);
        }
        if (pos.S & 1)
            return mp(pos.F, pos.S - 1);
        return mp(pos.F - 1, pos.S - 1);
    }

    void build(int s, int num, pair<int, int> pos, int dir)
    {
        int t = s + num - 1;
        while(true)
        {
            a[pos.F][pos.S] = s;
            position[s] = pos;
            if (s == t || s == mn2 - 1)
                break;
            s ++;
            pos = next(pos, dir);
        }
        if (s == mn2 - 1)
            return;
        int nexDir = (dir + 1) % 6;
        pair<int, int> nexPos;
        if (nexDir == 4)
        {
            num ++;
            nexPos = next(pos, 3);
        }
        else
            nexPos = next(pos, nexDir);
        build(s + 1, num, nexPos, nexDir);
    }

    table()
    {
        a[st][st] = 1;
        position[1] = mp(st, st);
        build(2, 1, mp(st + 1, st), 4);
    }

    void query()
    {
        int x; cin >> x;
        pair<int, int> p = position[x];
        FOR(i, 0, 5)
        {
            pair<int, int> q = next(p, i);
            ans[i] = a[q.F][q.S];
        }
        sort(ans, ans + 6);
        FOR(i, 0, 5)
            cout << ans[i] << ' ';
        cout << '\n';
    }
} t;
int n;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        t.query();
}

void xuly()
{

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
