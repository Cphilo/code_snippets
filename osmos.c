#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

int cmp(const void *a, const void*b) {
    if(*(long *)a > *(long *)b) return 1;
    return -1;
}


int solve(long v[], int n, int s, long a)
{   
    int ans = 0;
    while(s < n && v[s] < a) {
        a+=v[s];s++;
    }
    if(s == n)return 0;
    if(a <= 1)return n-s;
    else {    
        ans = solve(v, n, s, 2*a-1);
        if(ans+1 > n-s) {
            return n-s;
        } else {
            return ans+1;
        }
    }
}

int main()
{
    int t, kase, n, i, ans;
    long a, v[MAXN], x;
    scanf("%d", &t);
    for(kase=1;kase<=t;kase++) {
        scanf("%ld%d", &a, &n);
        for(i=0;i<n;i++) {  
            scanf("%ld", &v[i]);
        }
        qsort(v, n, sizeof(long), cmp);
        printf("Case #%d: %d\n", kase, solve(v, n, 0, a));
    }
    return 0;
}
