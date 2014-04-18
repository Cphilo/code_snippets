//A way to avoid big integer. Of course python is a secure way.
//sometimes double may not be correct for the precision.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
typedef uint64_t T;

T find_x(T s, T e, T t, T r) {
    if(e == s+1)return s;
    T m = (s+e)/2;
    T tmp = m*(2*m+2*r-1);
    if(tmp <= t) return find_x(m, e, t, r);
    return find_x(s, m, t, r);
}

int  main()
{
    int n, kase;
    T r, t, ans, i, tmp, s, e;
    scanf("%d", &n);
    for(kase=1;kase<=n;kase++) {
        scanf("%llu%llu", &r, &t);
        s = 0, e = 1;
        tmp = e*(2*e+2*r-1);
        while(tmp <= t) {
            e *= 2;
            tmp = e*(2*e+2*r-1); 
        }
        ans = find_x(s, e, t, r);
        printf("Case #%d: %llu\n", kase, ans);
    }
    return 0;
}

