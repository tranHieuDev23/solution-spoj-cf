#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 500005
#define mn2 20
#define pb push_back
#define bitPos(x, i) (((x) >> (i)) & 1)

using namespace std;
struct trie
{
    int cnt;
    bool full;
    trie* child[2];

    trie()
    {
        cnt = 0;
        full = false;
        child[0] = child[1] = NULL;
    }
};

trie* null = new trie();

trie* newTrie()
{
    trie* ret = new trie();
    ret -> child[0] = ret -> child[1] = null;
    return ret;
}

struct setTree
{
    trie* root;
    bool flip[mn2];

    setTree()
    {
        root = newTrie();
        memset(flip, 0, sizeof(flip));
    }

    void insert(int val, int h, trie* &cur)
    {
        if (h == -1)
        {
            cur -> cnt = 1;
            cur -> full = true;
            return;
        }

        int z = bitPos(val, h) ^ flip[h];
        if (cur -> child[z] == null)
            cur -> child[z] = newTrie();
        insert(val, h - 1, cur -> child[z]);

        cur -> cnt = (cur -> child[0] -> cnt) + (cur -> child[1] -> cnt);
        cur -> full = (cur -> child[0] -> full) & (cur -> child[1] -> full);
    }

    void insert(int val)
    {
        insert(val, mn2 - 1, root);
    }

    int getMex(int h, trie* cur)
    {
        if (cur == null)
            return 0;

        int z0 = flip[h], z1 = flip[h] ^ 1;
        if (cur -> child[z0] -> full)
            return getMex(h - 1, cur -> child[z1]) + (cur -> child[z0] -> cnt);
        return getMex(h - 1, cur -> child[z0]);
    }

    int getMex()
    {
        return getMex(mn2 - 1, root);
    }

    void modAll(int val)
    {
        FOR(i, 0, mn2 - 1)
            flip[i] ^= bitPos(val, i);
    }
};

int n, p[mn], out[mn];
int grudy[mn], ans = 0;
vector<int> g[mn];
setTree* Set[mn];
queue<int> q;

void scanVal(setTree* &u, setTree* &v, trie* &cur, int h, int val)
{
    if (h == -1)
    {
        u -> insert(val);
        return;
    }

    int z0 = v -> flip[h], z1 = v -> flip[h] ^ 1;

    if (cur -> child[z0] -> cnt)
        scanVal(u, v, cur -> child[z0], h - 1, val);
    if (cur -> child[z1] -> cnt)
        scanVal(u, v, cur -> child[z1], h - 1, val | (1 << (h)));
}

void merging(setTree* &a, setTree* &b)
{
    if (a -> root -> cnt < b -> root -> cnt)
        swap(a, b);
    scanVal(a, b, b -> root, mn2 - 1, 0);
}

void setup()
{
    cin >> n;
    FOR(u, 2, n)
    {
        cin >> p[u];
        out[p[u]] ++;
        g[p[u]].pb(u);
    }
}

void calc(int u)
{
    int grudy0 = 0;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        grudy0 ^= grudy[v];
    }
    ans += (grudy0 != 0);

    Set[u] = new setTree();
    Set[u] -> insert(grudy0);
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        int grudyOther = grudy0 ^ grudy[v];
        Set[v] -> modAll(grudyOther);
        merging(Set[u], Set[v]);
    }

    grudy[u] = Set[u] -> getMex();
}

void xuly()
{
    FOR(u, 1, n)
    if (!out[u])
        q.push(u);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        calc(u);
        if (-- out[p[u]] == 0)
            q.push(p[u]);
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("GAME.INP", "r", stdin);
    freopen("GAME.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
