#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, ans;
string s[mn], x;

struct trie
{
    int best;
    trie* child[26];

    trie()
    {
        best = 0;
        FOR(i, 0, 25)
            child[i] = NULL;
    }
} t;

bool com(string& a, string& b)
{
    if (a.size() != b.size())
        return a.size() < b.size();
    return a > b;
}

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> s[i];
    s[0] = "IMPOSSIBLE";
    sort(s + 1, s + n + 1, com);
    FOR(i, 1, n)
    {
        x = s[i];
        sort(x.begin(), x.end());
        trie* p = &t;
        FOR(j, 0, int(x.size()) - 1)
        {
            int z = x[j] - 'a';
            if (p -> child[z] == NULL)
                p -> child[z] = new trie;
            p = p -> child[z];
        }
        p -> best = i;
    }
}

void dfs(trie* p, int pos)
{
    int z = x[pos] - 'a';
    if (p -> child[z] == NULL)
        return;
    p = p -> child[z];
    ans = max(ans, p -> best);
    FOR(i, pos + 1, int(x.size()) - 1)
        dfs(p, i);
}

void xuly()
{
    cin >> x;
    sort(x.begin(), x.end());
    ans = 0;
    FOR(i, 0, int(x.size()) - 1)
        dfs(&t, i);
    cout << s[ans] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("DICTIONARY.INP", "r", stdin);
    freopen("DICTIONARY.OUT", "w", stdout);
    setup ();
    int t; cin >> t;
    while(t --)
        xuly ();
    return 0;
}
