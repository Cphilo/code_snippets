#include <stdio.h>
#include <stdlib.h>

int *myqsort(int x[], int n)
{
    int pivot = x[0], i, j;
    int left[n], right[n], lcnt=0, rcnt=0;
    int *ltmp, *rtmp, *ans;
    //printf("nothing happens!\n");
    ans = malloc(sizeof(int) * n);
    if(n == 1) {
        //printf("here!\n");
        return x;
    }
    for(i=1;i<n;i++) {
        if(x[i]<pivot) {
            left[lcnt++] = x[i];
        } else {
            right[rcnt++] = x[i];
        }
        //printf("%d ", x[i]);
    }
    if(lcnt > 0) {
        ltmp = malloc(sizeof(int) * lcnt);
        ltmp = myqsort(left, lcnt);
    }
    if(rcnt > 0) {
        rtmp = malloc(sizeof(int) * rcnt);
        rtmp = myqsort(right, rcnt);
    }
    ans[lcnt] = pivot;
    for(i=0;i<n;i++) {
        if(i<lcnt) {
            ans[i] = ltmp[i];
        }
        else if(i>lcnt) {
            ans[i] = rtmp[i-lcnt-1];
        }
        //printf("%d ", ans[i]);
    }
    //printf("\n");
    return ans;
}
int main()
{
    int test[] = {1, 3, 4, 8, 7, 4, 9, 6, 100}, n = 9;
    int *y = malloc(sizeof(int) * n);
    y = myqsort(test, n);
    int i;
    for(i=0;i<n;i++) {
        printf("%d ", y[i]);
    }
    printf("\n");
    return 0;
}

