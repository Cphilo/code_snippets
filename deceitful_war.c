#include <stdio.h>
#include <stdlib.h>

int cmp(const double *a, const double *b)
{
    if(*a > * b)return 1;
    return -1;
}

int war_score(double blk1[], double blk2[], int n)
{
    int i, j;
    int visited[n], ans;
    memset(visited, 0, sizeof(visited));
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            if(!visited[j] && blk1[i] < blk2[j]) {
                visited[j] = 1;break;
            }
        }
    }
    ans = 0;   
    for(i=0;i<n;i++) {
        ans += visited[i];
    }
    return n-ans;
}

int get_fail_cnt(double blk1[], double blk2[], int n)
{ 
    if(n==0)return 0;
    int less_cnt = 0, more_cnt = 0, fail_cnt, dx, i;
    for(i=0;i<n;i++) {
        if(blk1[i] < blk2[0])
            less_cnt++;
    }
    for(i=n-1-less_cnt;i>=0;i--) {
        if(blk2[i] > blk1[n-1]) {
            more_cnt++;
        }
    }
    fail_cnt = less_cnt + more_cnt;
    dx = 0;
    for(i=n-1;i>=fail_cnt;i--) {
        if(blk1[i]>blk2[n-1-fail_cnt])dx++;
    }
    double nblk1[n-fail_cnt-dx], nblk2[n-fail_cnt-dx];
    for(i=0;i<n-fail_cnt-dx;i++) { 
        nblk1[i] = blk1[fail_cnt+i];
        nblk2[i] = blk2[i];
    }
    fail_cnt += get_fail_cnt(nblk1, nblk2, n-fail_cnt-dx);
    return fail_cnt;
}

int main()
{
    int t, kase, n, i; 
    double blk1[1000], blk2[1000];
    scanf("%d", &t);
    for(kase=1;kase<=t;kase++) {
        scanf("%d", &n);
        for(i=0;i<n;i++) {
            scanf("%lf", &blk1[i]);
        }
        for(i=0;i<n;i++) {  
            scanf("%lf", &blk2[i]);
        }
        qsort(blk1, n, sizeof(double), cmp);
        qsort(blk2, n, sizeof(double), cmp);
        
        /*printf("blk1:");
        for(i=0;i<n;i++)printf("%.3lf ", blk1[i]);
        printf("\nblk2:");
        for(i=0;i<n;i++)printf("%.3lf ", blk2[i]);
        printf("\n");*/

        printf("Case #%d: %d %d\n", kase, n-get_fail_cnt(blk1, blk2, n), war_score(blk1, blk2, n));            
    }
    return 0;
}

