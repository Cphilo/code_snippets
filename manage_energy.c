//recursion is not easy to debug. Array length and recursion variable is im.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10
#define MAXE 5

long gen(long e, long r, long n, long v[], long nowe, long i, long x)
{
    long ans = v[i] * x, tmp, res=0, j, mc;
    mc = (nowe-x+r)>=e?e:(nowe-x+r);
    if(i == n-1) {
        return ans + v[n]*mc;
    }
    for(j=0;j<=mc;j++) {
        tmp = gen(e, r, n, v, mc, i+1, j);
        res = (tmp>res)?tmp:res;
    }
    ans += res;
    return ans;
}

int main()
{
    int num_cases, t;
    long e, r, n, v[MAXN+1], i, j;
    scanf("%d", &num_cases);
    for(t=1;t<=num_cases;t++) {
        memset(v, 0, sizeof(long)*(MAXN+1));
        scanf("%ld%ld%ld", &e, &r, &n);
        for(i=1;i<=n;i++) {
            scanf("%ld", &v[i]);
        }
        printf("Case #%d: %ld\n", t, gen(e, r, n, v, e, 0, 0));
    }
    return 0;
}
