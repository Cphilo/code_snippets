#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define MOD 1000000007
#define MAGIC 12347
#define MAXC 10

typedef long T;
typedef struct {
    T cost;
    int cnt;
    int *childs;
    int level;
} Node;
Node *tree[MAXN];
Node *nq[MAXN];
int head, tail, n;
void create_tree(int p[], int n)
{
    Node *nd, *pt;
    int i;
    for(i=0;i<n;i++) {
        nd = (Node *)malloc(sizeof(Node));
        tree[i] = nd;
        nd->cost = 0, nd->cnt = 0;
        if(p[i]-1 != i) {
            pt = tree[p[i]-1];
            if(pt->cnt % MAXC == 0) {
                pt->childs = (int *)realloc(pt->childs, sizeof(int)*(pt->cnt+MAXC));
            }
            pt->childs[pt->cnt++] = i;
            nd->level = pt->level + 1;
        } else {
            nd->level = 1;
        }
    } 
}

void update_tree(int u, int l, int r, int delta)
{
    Node *root = tree[u-1], *nd, *cd;
    head = 0, tail=0;
    int i;
    nq[tail++] = root;  
    while(head < tail) {    
        nd = nq[head++];
        if(nd->level >= l && nd->level <= r) {
            nd->cost += delta;
        }
        for(i=0;i<nd->cnt;i++) {
            cd = tree[nd->childs[i]];
            if(cd->level >= l && cd->level <= r) {
                nq[tail++] = cd;
            }
        }
    }
}

void print_tree() {
    int i, j;
    Node *nd;
    for(i=0;i<n;i++) {
        nd = tree[i];
        printf("cost: %ld, cnt: %d, level: %d, childs: ", nd->cost, nd->cnt, nd->level);
        for(j=0;j<nd->cnt;j++)
            printf("%d ", nd->childs[j]);
        printf("\n");
    }
}

int main()
{
    int kase, t, q, i, j;
    int p[MAXN], u, l, r;
    long delta;
    long long ans;
    
    Node *nd;

    scanf("%d", &t);
    for(kase=1;kase<=t;kase++) {
        scanf("%d", &n);
        p[0] = 1;
        for(i=1;i<n;i++) {
            scanf("%d", &p[i]);
        }
        create_tree(p, n);
        print_tree();      
        scanf("%d", &q);
        for(i=0;i<q;i++) {
            scanf("%d%d%d%ld", &u, &l, &r, &delta);
            update_tree(u, l, r, delta);            
            print_tree();
        }
        ans = 0;
        for(i=0;i<n;i++) {
            ans = (ans * MAGIC + tree[i]->cost) % MOD;
        }
        printf("Case %d: %lld\n", kase, ans);
    }
    return 0;
}
