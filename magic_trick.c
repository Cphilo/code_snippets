#include <stdio.h>
#include <stdlib.h>

int main()
{
    int t, i, j, k, row1, row2, mt1[4][4], mt2[4][4], ans, val;
    scanf("%d", &t);
    for(i=1;i<=t;i++) {
        scanf("%d", &row1);
        for(j=0;j<4;j++) {
            for(k=0;k<4;k++) {
                scanf("%d", &mt1[j][k]);
            }
        }
        scanf("%d", &row2);
        for(j=0;j<4;j++) {
            for(k=0;k<4;k++) {
                scanf("%d", &mt2[j][k]);
            }
        }
        ans = get_cmn(mt1[row1-1], mt2[row2-1], 4, &val);
        printf("Case #%d: ", i);
        if(ans == 1) {
            printf("%d\n", val);        
        } else if(ans == 0) {
            printf("Volunteer cheated!\n");
        } else {
            printf("Bad magician!\n");
        }
    }
    return 0;
}

int get_cmn(int x[], int y[], int n, int *val)
{
    int i, j, ret=0;
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            if(x[i] == y[j]) {
                ret++;
                *val=x[i];
                break;
            }
        }
    }
    return ret;
}
