#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, j, k, l;
    int seq[200];
    scanf("%d", &n);
    //printf("n: %d\n", n);
    for(i=0;i<n;i++) {
        scanf("%d", &seq[i]);
        //printf("%d ", seq[i]);
    }
    //printf("\n");
    for(i=n/2;i>0;i--) {
        for(j=0;j<n;j++) {
            for(k=0, l=0;j+i+k<n && l<i;k++) {
                if(seq[j+l] != seq[j+i+k]) {
                    l = 0;
                } else {
                    l++;
                }
            }
            if(l == i) {
                printf("%d\n", i);
                return 0;
            }
        }
    }
    printf("0\n");
    return 0;
}
