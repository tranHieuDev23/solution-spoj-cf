#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, cur = 1, pre = 0;
int num[mn], in[mn], rig = 0;
string s[2];
vector<char> g[mn];
queue<int> q;

bool input()
{
    swap(cur, pre);
    cin >> s[cur];
    int szCur = s[cur].size();
    int szPre = s[pre].size();
    FOR(i, 0, szCur - 1)
    {
        if (i == szPre)
            return true;
        char a = s[pre][i];
        char b = s[cur][i];
        if (a != b)
        {
            g[int(a)].pb(b);
            in[int(b)] ++;
            return true;
        }
    }
    return szPre == szCur;
}

void setup()
{
    cin >> n >> s[cur];
    FOR(i, 2, n)
    if (!input())
    {
        cout << "No solution";
        exit(0);
    }
}

bool check(char u)
{
    num[int(u)] = ++ rig;
    FOR(i, 0, int(g[int(u)].size()) - 1)
    {
        char v = g[int(u)][i];
        if (num[int(v)])
        {
            if (num[int(v)] < num[int(u)])
                return false;
            continue;
        }
        bool get = check(v);
        if (!get)
            return false;
    }
    num[int(u)] = maxC;
    return true;
}

void printAns()
{
    FOR(i, 'a', 'z')
    if (!in[i])
        q.push(i);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << char(u);
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i];
            if (-- in[v] == 0)
                q.push(v);
        }
    }
}

void xuly()
{
    FOR(i, 'a', 'z')
    if (!num[i])
        if (!check(i))
        {
            cout << "No solution";
            return;
        }
    printAns();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("KEY.INP", "r", stdin);
    freopen("KEY.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
