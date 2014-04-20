#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100000
#define MAXL 11
typedef long long T;
char rs1[MAXN][MAXL], rs2[MAXN][MAXL];
T cal_row(char *s, int l)
{
    char *c = s;
    T ans = 0;
    char num[10];
    int cnt=0;
    while(*c) {
        if(*c >= '0' && *c <= '9') {
            num[cnt++] = *c;
        } else {
            num[cnt] = '\0';
            ans += atol(num);
            cnt = 0;
        }
        c++;
    }
    return ans/l;
}

void get_r(char *s, T r, char rs[][MAXL], T rnum, int l)
{ 
    char *c = s;
    T total = 0, now, i;
    char num[10];
    int cnt=0;
    int rcnt=0;
    while(*c) {
        if(*c >= '0' && *c <= '9') {
            num[cnt++] = *c;
        } else {
            num[cnt] = '\0';
            now = atol(num);
            cnt = 0;
            for(i=total;i<total+now;i++) {
                rs[i%rnum][i/rnum] = *c; 
            }
            total += now;
        }
        c++;
    }
}

int main()
{
    int t, kase, l;
    T r1, r2, rl1, rl2;
    char s1[MAXN], s2[MAXN];
    int visited[MAXN], tag;
    T i, j;
    scanf("%d", &t);
    for(kase=1;kase<=t;kase++) {
        memset(visited, 0, sizeof(int)*MAXN);
        scanf("%d", &l);
        scanf("%s%s", s1, s2);
        rl1 = cal_row(s1, l);   
        rl2 = cal_row(s2, l); 
        for(i=0;i<rl1;i++) {
            rs1[i][l]  = 0;
            rs2[i][l] = 0;
        }
        get_r(s2, r2, rs2, rl2, l);
        get_r(s1, r2, rs1, rl1, l);
        if(rl1 == rl2) {
            for(r1=1;r1<=rl1;r1++) {
                tag = 0;
                for(r2=1;r2<=rl2;r2++) {
                    if(!visited[r2] && strcmp(rs1[r1-1], rs2[r2-1]) == 0) {
                        visited[r2] = 1;
                        tag = 1;
                        break;
                    }
                }
                if(tag == 0) {
                    printf("No\n");
                    goto L;
                }
            }
            printf("Yes\n");  
            L:
                ;
        } else {
            printf("No\n");
        }  
    }
    return 0;
}
