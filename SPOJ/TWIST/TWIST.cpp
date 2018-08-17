#include<bits/stdc++.h>
#define FOR(i, j, k) for(int i = j; i <= k; i ++)
#define FORD(i, j, k) for(int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define mp make_pair

using namespace std;
bool srandSet = false;

long long getRandom(long long low, long long high)
{
    if (!srandSet)
    {
        srand(time(NULL));
        srandSet = true;
    }
    long long val = 1ll * rand() * rand() * rand() * rand();
    long long range = high - low + 1;
    return ((val % range) + range) % range;
}

template <typename T> class Treap
{
    private:
        class TreapNode
        {
            public:
                T value;
                int priority, cnt;
                bool rev;
                TreapNode *lc, *rc;

                TreapNode() {}

                TreapNode(T value): value(value)
                {
                    priority = getRandom(1, maxC);
                    cnt = 1;
                    lc = rc = NULL;
                }
        };

        void push(TreapNode* node)
        {
            if (node->rev)
            {
                swap(node->lc, node->rc);
                if (node->lc)
                    node->lc->rev ^= true;
                if (node->rc)
                    node->rc->rev ^= true;
                node->rev = false;
            }
        }

        int getCount(TreapNode* node)
        {
            return (node? node->cnt : 0);
        }

        void updateCount(TreapNode* node)
        {
            if (node)
                node->cnt = getCount(node->lc) + getCount(node->rc) + 1;
        }

        TreapNode* merge(TreapNode* l, TreapNode* r)
        {
            if (!l || !r)
                return (l? l : r);
            push(l);
            push(r);
            TreapNode* re = NULL;
            if (l->priority > r->priority)
            {
                l->rc = merge(l->rc, r);
                re = l;
            }
            else
            {
                r->lc = merge(l, r->lc);
                re = r;
            }
            updateCount(re);
            return re;
        }

        void split(TreapNode* node, TreapNode*& l, TreapNode*& r, int pos, int add = 0)
        {
            if (!node)
            {
                l = r = NULL;
                return;
            }
            push(node);
            int currentPos = add + getCount(node->lc);
            if (pos <= currentPos)
            {
                split(node->lc, l, node->lc, pos, add);
                r = node;
            }
            else
            {
                split(node->rc, node->rc, r, pos, currentPos + 1);
                l = node;
            }
            updateCount(node);
        }

        TreapNode* get(TreapNode* node, int pos, int add = 0)
        {
            if (!node)
                return NULL;
            push(node);
            int currentPos = add + getCount(node->lc);
            if (pos == currentPos)
                return node;
            if (pos < currentPos)
                return get(node->lc, pos, add);
            return get(node->rc, pos, currentPos + 1);
        }

        void erase(TreapNode*& node, int pos, int add = 0)
        {
            if (!node)
                return;
            push(node);
            int currentPos = add + getCount(node->lc);
            if (pos == currentPos)
                node = merge(node->lc, node->rc);
            else if (pos < currentPos)
                erase(node->lc, pos, add);
            else
                erase(node->rc, pos, currentPos + 1);
            updateCount(node);
        }

        void print(TreapNode* node)
        {
            if (!node)
                return;
            push(node);
            print(node->lc);
            cout << node->value << ' ';
            print(node->rc);
        }

        TreapNode* root;

    public:
        Treap()
        {
            root = NULL;
        }

        int size()
        {
            return getCount(root);
        }

        void insert(T value, int pos)
        {
            TreapNode *l = NULL, *r = NULL;
            split(root, l, r, pos);
            TreapNode* newItem = new TreapNode(value);
            root = merge(merge(l, newItem), r);
        }

        void insert(T value)
        {
            insert(value, size());
        }

        void reverse(int from, int to)
        {
            TreapNode *root1, *root2, *root3;
            split(root, root2, root3, to + 1);
            split(root2, root1, root2, from);
            root2->rev ^= true;
            root = merge(merge(root1, root2), root3);
        }

        T get(int pos)
        {
            return get(root, pos)->value;
        }

        void erase(int pos)
        {
            erase(root, pos);
        }

        void print()
        {
            print(root);
            cout << '\n';
        }
};
int n, q;
Treap<int> treap;

void setup()
{
    cin >> n >> q;
    FOR(i, 1, n)
        treap.insert(i);
    int l, r;
    FOR(i, 1, q)
    {
        cin >> l >> r;
        l --, r --;
        treap.reverse(l, r);
    }
    treap.print();
}

void xuly()
{

}

int main()
{
    iostream::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    setup();
    xuly();
    return 0;
}