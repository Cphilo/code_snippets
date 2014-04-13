#include <stdio.h>
#include <stdlib.h>

#define MAXN 5
int check_full(int path[][MAXN], int m, int n)
{
    int i, j, ccnt = 0, rcnt = 0; 
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
            if(path[i][j]) { rcnt++;break; }
        }
    }
    for(j=0;j<n;j++) {
        for(i=0;i<m;i++) {
            if(path[i][j]) { ccnt++;break; }
        }
    }
    if(ccnt == n && rcnt == m)return 1;
    return 0;
}

int check_repeated(int path[][MAXN], int m, int n)
{
    int i, j, rows[m], cols[n];
    memset(rows, 0, sizeof(int)*m);
    memset(cols, 0, sizeof(int)*n);
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
            if(path[i][j]) {
                rows[i]++;
                cols[j]++;
            }
        }
    }
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
            if(rows[i]>=2 && cols[j] >= 2 && path[i][j])return 1;
        }
    }
    return 0;
}

void test()
{
    int path[MAXN][MAXN], m = 2, n=2;
    path[0][0] = 1;
    path[0][1] = 1;
    path[0][2] = 1;
    path[1][0] = 1;
    path[1][1] = 0;
    path[1][2] = 0;
    printf("check repeated true: %d\n", check_repeated(path, 2, 3));
    //printf("check full true: %d\n", check_full(path, m, n));
    path[0][0] = 0;
    //printf("check full false: %d\n", check_full(path, m, n));
    printf("check repeated false: %d\n", check_repeated(path, 2, 3));
}

void print_path(int path[][MAXN], int m, int n)
{
    int i, j;
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
            printf("%d ", path[i][j]);
        }
        printf("\n");
    }
}

void get_path(int mt[][MAXN], int m, int n, int path[][MAXN], long * ans)
{
    int col, row, i, j, ccnt, rcnt;
    int tmp_path[MAXN][MAXN];
    long res; 
    res = 0;
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
            if(path[i][j]) {
                res += mt[i][j];
            }
        }
    }
    if(res >= *ans)return;
    if(check_repeated(path, m, n))return;
    if(check_full(path, m, n)) {    
        *ans=res; 
        return;
    }
    memset(tmp_path, 0, sizeof(int)*MAXN*MAXN);
    for(row=0;row<m;row++) {
        for(col=0;col<n;col++) {
            if(path[row][col] == 0) {
                memcpy(tmp_path, path, sizeof(int)*MAXN*MAXN);
                tmp_path[row][col] = 1;
                get_path(mt, m, n, tmp_path, ans);
            }
        } 
    }
}

//when m < n, change mt to m > n.
void change_mt(int mt[][MAXN], int nmt[][MAXN], int m, int n) 
{
    int i, j;
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
            nmt[j][i] = mt[i][j];
        }
    }
}
 
int main()
{
    int t, i, j, k, mt[MAXN][MAXN], m, n;
    int nmt[MAXN][MAXN], path[MAXN][MAXN];
    long ans;
    int mrow, mcol;
    //test();
    scanf("%d", &t);
    for(i=1;i<=t;i++) {
        scanf("%d%d", &m, &n);
        for(j=0;j<m;j++) {
            mrow = 10005;
            for(k=0;k<n;k++) {
                scanf("%d", &mt[j][k]);
                path[j][k] = 0;
            }
        }
        ans = 0;
        for(j=0;j<n;j++) {
            mcol = 10005;
            for(k=0;k<m;k++) {
                if(mt[k][j] < mcol)mcol=mt[k][j];
            }
            ans += mcol;
        }
        for(j=0;j<m;j++) {
            mrow = 10005;
            for(k=0;k<n;k++) { 
                if(mt[j][k] < mrow)mrow = mt[j][k];
            }
            ans += mrow;
        }
        //printf("%ld\n", ans);
        if(m<n) {
            change_mt(mt, nmt, m, n);
            get_path(nmt, n, m, path, &ans);
        } else {
            get_path(mt, m, n, path, &ans);
        }
        printf("Case %d: %ld\n", i, ans);
    }
    return 0;
}

