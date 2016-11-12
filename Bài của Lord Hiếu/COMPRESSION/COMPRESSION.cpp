#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define penalty(h) (1ll << (40 - (h)))

using namespace std;
int n;
string s;
long long ans = 0;

struct trie
{
    int depth;
    bool endString, selected;
    char conres;
    long long dp;
    trie* parent;
    trie* child[26];

    trie(char conres = ' ', trie* parent = NULL): conres(conres), parent(parent)
    {
        depth = (parent == NULL? 0 : parent -> depth + 1);
        endString = selected = false;
        dp = penalty(depth);
        FOR(i, 0, 25)
            child[i] = NULL;
    }

    long long dfs()
    {
        if (endString)
        {
            selected = true;
            return dp;
        }
        long long sumDp = 0;
        FOR(i, 0, 25)
        if (child[i] != NULL)
            sumDp += child[i] -> dfs();
        if (sumDp < dp)
            dp = sumDp;
        else
            selected = true;
        return dp;
    }
} t;

vector<trie*> l1;

void findL1(trie* p)
{
    if (p -> selected)
    {
        l1.pb(p);
        return;
    }
    FOR(i, 0, 25)
    if (p -> child[i] != NULL)
        findL1(p -> child[i]);
}

void reclaim(trie* p)
{
    s.resize(p -> depth);
    FORD(i, int(s.size()) - 1, 0)
    {
        s[i] = p -> conres;
        p = p -> parent;
    }
}

void setup()
{
    cin >> n;
    while(n --)
    {
        cin >> s;
        int sz = s.size();
        trie* p = &t;
        FOR(i, 0, sz - 1)
        {
            int z = s[i] - 'a';
            if(p -> child[z] == NULL)
                p -> child[z] = new trie(s[i], p);
            p = p -> child[z];
        }
        p -> endString = true;
    }
}

void xuly()
{
    FOR(i, 0, 25)
    if (t.child[i] != NULL)
    {
        ans += t.child[i] -> dfs();
        findL1(t.child[i]);
    }
    cout << ans << '\n' << l1.size() << '\n';
    FOR(i, 0, int(l1.size()) - 1)
    {
        reclaim(l1[i]);
        cout << s << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("COMPRESSION.INP", "r", stdin);
    freopen("COMPRESSION.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
