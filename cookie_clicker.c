#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int t, i;
    long l, j, k;
    double c, f, x, ans, now_res, last_res;
    scanf("%d", &t);
    for(i=1;i<=t;i++) {
        scanf("%lf%lf%lf", &c, &f, &x);
        l = ceil(x/c);
        now_res = x / 2;
        ans = now_res;
        last_res = now_res;
        for(j=2;j<=l;j++) {
            now_res = last_res + (c - x)/((j-2)*f+2)+x/((j-1)*f+2);
            if(now_res < ans) ans = now_res;
            last_res = now_res;
        }
        printf("Case #%d: %.7lf\n", i, ans);
    }
    return 0;
}
