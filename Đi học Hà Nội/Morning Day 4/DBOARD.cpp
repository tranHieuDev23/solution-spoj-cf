#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define maxC 100000000000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int r, c;
char a[mn][mn];

struct trie
{
    int num;
    trie* child[26];

    trie()
    {
        num = 0;
        FOR(i, 0, 25)
            child[i] = NULL;
    }
} t;
vector<trie*> pos;

void setup()
{
    cin >> r >> c;
    FOR(i, 1, r)
    FOR(j, 1, c)
        cin >> a[i][j];
}

void xuly()
{
    FOR(i, 1, c)
        pos.pb(&t);
    FORD(i, r, 1)
    {
        bool ok = true;
        FOR(j, 1, c)
        {
            int z = a[i][j] - 'a';
            if (pos[j - 1] -> child[z] == NULL)
                pos[j - 1] -> child[z] = new trie();
            pos[j - 1] = pos[j - 1] -> child[z];
            if (++ pos[j - 1] -> num == 2)
                ok = false;
        }
        if (ok)
        {
            cout << i - 1;
            return;
        }
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
