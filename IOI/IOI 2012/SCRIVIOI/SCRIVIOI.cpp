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
struct trie
{
    int h;
    char c;
    trie* child[26];
    vector<trie*> p;

    trie(trie* pa = NULL, char c = ' '): c(c)
    {
        FOR(i, 0, 25)
            child[i] = NULL;
        p = vector<trie*>();
        if (pa == NULL)
        {
            h = -1;
            return;
        }
        h = pa -> h + 1;
        p.pb(pa);
        int id = 0;
        while(int(p[id] -> p.size()) > id)
        {
            p.pb(p[id] -> p[id]);
            id ++;
        }
    }
};

char getChar(trie* p, int x)
{
    int dif = (p -> h) - x, id = 0;
    while(dif)
    {
        if (dif & 1)
            p = p -> p[id];
        dif >>= 1;
        id ++;
    }
    return p -> c;
}

int n;
vector<trie*> root;

void setup()
{
    cin >> n;
    char t, c;
    int x;
    root.pb(new trie());
    FOR(i, 0, n - 1)
    {
        cin >> t;
        if (t == 'T')
        {
            cin >> c;
            x = c - 'a';
            if (root[i] -> child[x] == NULL)
                root[i] -> child[x] = new trie(root[i], c);
            root.pb(root[i] -> child[x]);
            continue;
        }
        cin >> x;
        if (t == 'U')
            root.pb(root[i - x]);
        else
        {
            cout << getChar(root[i], x) << '\n';
            i --, n --;
        }
    }
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
