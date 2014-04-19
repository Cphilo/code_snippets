//try to be clear about the problem first, then code.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100000
typedef struct {
    long x;
    long y;
} Point;

Point v[MAXN];
int n;
double get_sum(double x) {
    double s = 0;
    int k;
    for(k=0;k<n;k++) {
        s += (x-v[k].x)/sqrt((x-v[k].x)*(x-v[k].x)+v[k].y*v[k].y);
    }
    return s;
}
double find_x(double x1, double x2) {
    double ls = get_sum(x1);
    double s = get_sum((x1+x2)/2);
    double rs = get_sum(x2);
    if((x2-x1)*1000000 < 1) {
        return (x1+x2)/2;
    } else if(rs*s < 0) {
        return find_precx((x1+x2)/2, x2);
    } else if(ls*s < 0){
        return find_precx(x1, (x1+x2)/2);
    }
}

int main()
{
    int t, kase, i;
    Point p;
    scanf("%d", &t);
    for(kase=1;kase<=t;kase++) {
        scanf("%d", &n);
        for(i=0;i<n;i++) {
            scanf("%ld%ld", &p.x, &p.y);
            v[i] = p;
        }
        printf("Case %d: %.6f\n", kase, find_x(v[0].x, v[n-1].x));
    }
    return 0;
}
