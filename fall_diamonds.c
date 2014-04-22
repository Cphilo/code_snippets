#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MIN(x, y) (((x) < (y))?(x):(y))

double solve(long level, long n, int x, int y)
{
    int total = 1<<n;
    int ans = 0;
    int l = 2*(level -1), r = n-l;
    while(l>=1) {
        if(r>=1 && r<=2*(level-1)) {
            if(l>=(y+1)) {
                ans += 1<<MIN(l, r);
                if(l != r)ans += 1<<MIN(l, r);
            }
        }
        l--;
        r++;
    }
    if(n <= 2 * (level-1)) {
        if(n >= (y+1)) {
            ans++;
        }
    }  
    //printf("n: %ld, ans: %d, total: %d\n", n, ans, total);
    return ans/(double)total;
}

int main()
{
    int t, kase, x, y;
    long level, low, high, n;
    double ans;
    scanf("%d", &t);
    for(kase=1;kase<=t;kase++) {
        scanf("%ld%d%d", &n, &x, &y);
        if(x < 0)x = -x;
        level = (x+y)/2+1;
        high = 2*(level-1)*(level-1)+3*(level-1)+1;
        low = high - 4*(level-1)-1;
        if(high <= n) {
            ans = 1.0;
        } else if(low >= n) {
            ans = 0.0;
        } else {
            ans = solve(level, n-low, x, y);
        }
        printf("Case #%d: %.6f\n", kase, ans);
    }
    return 0;
}
