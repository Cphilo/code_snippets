#include <stdio.h>
#include <stdlib.h>

int main() 
{
    char line[80];
    int n, i, x, y, ans;
    double curd, dmin;
    char op;
    gets(line);
    sscanf(line, "%d", &n);
    dmin = -1;
    for(i=0;i<n;i++) {
        gets(line);
        sscanf(line, "%d %c %d", &x, &op, &y);
        //printf("%d%c%d\n", x, op, y);
        if(op == '/') {
            curd = x / (double)y - 9;
        } else if(op == '*') {
            curd = x*y-9;
        } else if(op == '+') {
            curd = x+y-9;
        } else {
            curd = x-y-9;
        }
        if(curd < 0) curd = -curd;
        if(dmin < 0 || curd < dmin) {
            ans = i+1;
            dmin = curd;
        }
        //printf("curd: %f\n", curd);
    }
    printf("%d\n", ans);
    return 0;
}
