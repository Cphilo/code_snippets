#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000000
typedef long long T;
T v[MAXN];
T solve(T e, T r, T n)
{
    T ans, x, nowe;
    T i, vi;
    T stk[n], top=0, a[n];
    stk[top++] = 0;
    for(i=1;i<n;i++) {
        vi = stk[top-1];
        while(v[i] > v[vi]) {
            a[vi] = i;
            top--;
            if(!top)break;
            vi = stk[top-1];
        }
        stk[top++] = i;
    }
    while(top) {
        vi = stk[top-1];
        a[vi] = -1;
        --top;
    }
    /*for(i=0;i<n;i++) {
        printf("%ld ", a[i]);
    }
    printf("\n");*/
    nowe = e;
    ans = 0;
    for(i=0;i<n;i++) {
        if(a[i] < 0) { 
            ans += nowe * v[i];
            nowe = 0;
        } else {
            x = r * (a[i] - i) + nowe;
            if(x > e) {
                if(x-e <= nowe) {
                    ans += (x-e) * v[i];
                    nowe = nowe - (x-e);
                } else {
                    ans += nowe * v[i];
                    nowe = 0;
                }
            }
        }
        nowe += r;
        if(nowe > e)nowe = e;
    } 
    return ans;
}
int main()
{
    int num_cases, t;
    T e, r, n, i, j;
    scanf("%d", &num_cases);
    for(t=1;t<=num_cases;t++) {
        scanf("%lld%lld%lld", &e, &r, &n);
        for(i=0;i<n;i++) {
            scanf("%lld", &v[i]);
        }
        printf("Case #%d: %lld\n", t, solve(e, r, n));
    }
    return 0;
}
