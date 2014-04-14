#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5
void is_click_win(int mt[][MAXN], int mcnt[][MAXN], int r, int c, int cx, int cy, int *ans)
{
    int i, j, cnt=0;
    for(i=cx-1;i<=cx+1;i++) {
        for(j=cy-1;j<=cy+1;j++) {
            if(i>=0 && i<r && j>=0 && j<c && mt[i][j]==0) {
                mt[i][j] = 1;
                if(mcnt[i][j] == 0) {
                    is_click_win(mt, mcnt, r, c, i, j, ans);
                }
            }
        }
    }
    for(i=0;i<r;i++) {
        for(j=0;j<c;j++) {
            cnt += mt[i][j];
        }
    }
    if(cnt == r*c) {
        *ans=1;
    }
}



//check if the mt can click all.
int check_valid(int mt[][MAXN], int r, int c) 
{
    int mcnt[MAXN][MAXN], blank_cnt, blank_x, blank_y;
    int tmp_mt[MAXN][MAXN];
    int i, j, x, y;
    int cx = -1, cy = -1, tmp;
    memset(mcnt, 0, sizeof(int)*MAXN*MAXN);
    blank_cnt = 0;
    for(i=0;i<r;i++) {
        for(j=0;j<c;j++) {
            mcnt[i][j] = 0;
            for(x=i-1;x<=i+1;x++) {
                for(y=j-1;y<=j+1;y++) {
                    if(x >= 0 && x < r && y>= 0 && y < c) {
                        mcnt[i][j] += mt[x][y];
                    }
                }
            }
            if(mt[i][j]==0) {
                blank_cnt++;
                blank_x = i, blank_y = j;
            }
            if(mcnt[i][j] == 0) {
                cx = i, cy = j;
            }
        }
    }
    if(blank_cnt == 1) {
        mt[blank_x][blank_y] = 2;
        return 1;
    }
    if(cx >= 0 && cy >= 0) {
        tmp = 0;
        memcpy(tmp_mt, mt, sizeof(int)*MAXN*MAXN);
        is_click_win(tmp_mt, mcnt, r, c, cx, cy, &tmp);
        if(tmp) {
            mt[cx][cy] = 2;
            return 1;
        }
    }
    return 0;
}

/*void test()
{
    int mt[3][3] = {{0, 0, 1}, {0, 0, 0}, {1, 0, 0}}, tmp_mt[3][3];
    int mcnt[3][3] = {{0, 1, 1}, {1,1,1}, {1,1,0}};
    int ans = 0;
    is_click_win(mt, mcnt, 3, 3, 0, 0, &ans);
    printf("is_click_win, false: %d\n", ans);
    memcpy(tmp_mt, mt, sizeof(int)*3*3);
    ans = check_valid(tmp_mt, 3, 3);
    printf("check valid, false: %d\n", ans);
    int mt2[3][3] = {{0, 0, 1}, {0, 0, 1}, {1, 1,1}};
    int mcnt2[3][3] = {{0, 2, 2}, {2, 5, 4}, {2, 4, 4}};
    ans = 0;
    memcpy(tmp_mt, mt2, sizeof(int)*3*3); 
    is_click_win(tmp_mt, mcnt2, 3, 3, 0, 0, &ans);
    printf("is_click_win true:%d\n", ans); 
    ans = check_valid(mt2, 3, 3);
    printf("check valid, true: %d\n", ans);
}*/

void print_mt(int mt[][MAXN], int r, int c)
{
    int x, y;
    for(x=0;x<r;x++) {
        for(y=0;y<c;y++) {
            if(mt[x][y] == 0) {
                printf(".");
            } else if(mt[x][y] == 1) {
                printf("*");
            } else {
                printf("c");
            }
        }
        printf("\n");
    }
}

void find_path(int mt[][MAXN], int r, int c, int m, int *found, int sx, int sy)
{
    int tmp_mt[MAXN][MAXN], i, j, nsx, nsy;
    if(*found)return;
    if(m == 0) {
        if(check_valid(mt, r, c)) {
            print_mt(mt, r, c);
            *found = 1;
        }
        return;
    }
    if(sy < c-1) {
        nsy = sy+1;
        nsx = sx;
    } else if(sx < r-1) {
        nsx = sx + 1;
        nsy = 0;
    } else {
        return;
    }
    memcpy(tmp_mt, mt, sizeof(int)*MAXN*MAXN);
    find_path(tmp_mt, r, c, m, found, nsx, nsy);
    tmp_mt[nsx][nsy] = 1;
    find_path(tmp_mt, r, c, m-1, found, nsx, nsy);
}

int main()
{
    int t, i, found;
    int r, c, m;
    int mt[MAXN][MAXN];
    //test();
    scanf("%d", &t);
    for(i=1;i<=t;i++) {
        scanf("%d%d%d", &r, &c, &m);
        memset(mt, 0, sizeof(int)*MAXN*MAXN);
        found = 0;
        printf("Case #%d:\n", i);
        mt[0][0] = 1;
        find_path(mt, r, c, m-1, &found, 0, 0);
        if(found == 0) {
            mt[0][0] = 0;
            find_path(mt, r, c, m, &found, 0, 0);
            if(found == 0)printf("Impossible\n"); 
        }
    }
    return 0;
}

