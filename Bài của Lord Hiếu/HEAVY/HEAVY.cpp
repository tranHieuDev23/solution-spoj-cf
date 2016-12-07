#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 5003
#define mn2 15003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
struct trie
{
    int val;
    trie* child[26];

    trie()
    {
        val = 0;
        FOR(i, 0, 25)
            child[i] = NULL;
    }
} t1, t2;

trie* getTrie(string s, trie* root)
{
    FOR(i, 0, int(s.size()) - 1)
    {
        int z = s[i] - 'A';
        if (root -> child[z] == NULL)
            root -> child[z] = new trie();
        root = root -> child[z];
    }
    return root;
}

int n, k, pre[mn], suf[mn], rig1 = 0, rig2 = 0;
string str;

struct edge
{
    int v, c, f;

    edge(int v = 0, int c = 0): v(v), c(c) {f = 0;}
};

int s, t, q[mn2], h[mn2];
int mark[mn2], co = 0, cur[mn2];
vector<int> g[mn2], group[mn2];
vector<edge> e;
bool allowPre[mn];

void addEdge(int u, int v, int c)
{
    g[u].pb(e.size());
    e.pb(edge(v, c));
    g[v].pb(e.size());
    e.pb(edge(u, 0));
}

void setup()
{
    cin >> n >> k;
    trie* p = NULL;
    FOR(i, 1, n)
    {
        cin >> str;

        p = getTrie(str.substr(0, k), &t1);
        if (!p -> val)
            p -> val = ++ rig1;
        pre[i] = p -> val;

        p = getTrie(str.substr(str.size() - k, k), &t2);
        if (!p -> val)
            p -> val = ++ rig2;
        suf[i] = p -> val;
    }
}

void prepareGraph()
{
    s = 0, t = rig1 + n + rig2 + 1;
    FOR(i, 1, rig1)
        addEdge(s, i, 1);
    FOR(i, rig1 + n + 1, t - 1)
        addEdge(i, t, 1);
    FOR(u, 1, n)
    {
        addEdge(pre[u], rig1 + u, maxC);
        addEdge(rig1 + u, rig1 + n + suf[u], maxC);
    }
}

bool bfs()
{
    int l = 1, r = 1;
    mark[s] = ++ co, q[1] = s, h[s] = 0;
    while(l <= r)
    {
        int u = q[l ++];
        cur[u] = 0;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int id = g[u][i];
            int v = e[id].v;
            if (mark[v] == co || e[id].f == e[id].c)
                continue;
            mark[v] = co;
            h[v] = h[u] + 1;
            q[++ r] = v;
        }
    }
    return mark[t] == co;
}

int dfs(int u, int low)
{
    if (u == t || low == 0)
        return low;
    for(; cur[u] < int(g[u].size()); cur[u] ++)
    {
        int id = g[u][cur[u]];
        int v = e[id].v;
        if (h[v] != h[u] + 1 || e[id].f == e[id].c)
            continue;
        int get = dfs(v, min(low, e[id].c - e[id].f));
        if (get)
        {
            e[id].f += get;
            e[id ^ 1].f -= get;
            return get;
        }
    }
    return 0;
}

int maxFlow()
{
    int ret = 0;
    while(bfs())
        while(int x = dfs(s, maxC))
            ret += x;
    return ret;
}

void buildGroup()
{
    FOR(u, 1, rig1)
    if (mark[u] != co)
        allowPre[u] = true;

    FOR(u, 1, n)
    {
        if (allowPre[pre[u]])
            group[pre[u]].pb(u);
        else
            group[rig1 + suf[u]].pb(u);
    }
}

void xuly()
{
    prepareGraph();
    cout << maxFlow() << '\n';
    buildGroup();
    FOR(u, 1, rig1 + rig2)
    if (group[u].size())
    {
        cout << group[u].size();
        FOR(i, 0, int(group[u].size()) - 1)
            cout << ' ' << group[u][i];
        cout << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("HEAVY.INP", "r", stdin);
    freopen("HEAVY.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
