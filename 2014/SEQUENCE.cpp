#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
#define N 100100
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) ((S >> i) & 1)
template<typename T> inline void read(T &x) {
    char c;
    bool neg = false;
    while (!isdigit(c = getchar()) && c != '-');
    x = 0;
    if (c == '-') {
        neg = true;
        c = getchar();
    }
    do {
        x = x * 10 + c - '0';
    } while (isdigit(c = getchar()));
    if (neg) x = -x;
}
template<typename T> inline void write(T x) {
    if (x < 0) {
        putchar('-');
        write(-x);
        return;
    }
    if (x < 10) putchar(char(x + 48));
    else {
        write(x/10);
        putchar(char(48 + x%10));
    }
}
template<typename T> inline void writeln(T x) {
    write(x);
    putchar('\n');
}
using namespace std;
int n, k;
long long a[N], s[N];

struct ConvexHull {
    vector<long long> a, b;
    vector<double> x;
    vector<int> p;
    int start, last;
    ConvexHull() {}
    void reset(int n) {
        a.clear();
        b.clear();
        x.clear();
        p.clear();
        a.resize(n);
        b.resize(n);
        x.resize(n);
        p.resize(n);
        start = 1; last = 0;
    }

    void add(long long aNew, long long bNew, int pNew) {
        double xNew = -1e18;
        while (start <= last) {
            if (aNew == a[last]) {
                if (bNew >= b[last]) {
                    b[last] = bNew;
                    p[last] = pNew;
                }
                return;
            }
            xNew = 1.0 * (bNew - b[last]) / (a[last] - aNew);
            if (start == last || xNew >= x[last]) break;
            --last;
        }
        a[++last] = aNew;
        b[last] = bNew;
        x[last] = xNew;
        p[last] = pNew;
    }

    long long Get(long long xQuery, int &pos) {
        if (start > last) return 0;
        while (start < last && x[start + 1] <= xQuery) ++start;
        pos = p[start];
        return a[start] * xQuery + b[start];
    }

}CH[2];
#define K 205
long long f[2][N];
int pre[K][N];
void trace(int k, int n) {
    if (k == 1) return;
    trace(k - 1, pre[k][n]);
    write(pre[k][n]);
    putchar(' ');
}
int main() {
   // freopen("E:\\input.txt","r",stdin);
   // freopen("E:\\out.txt","w",stdout);
    IO;
    read(n); read(k);
    FOR(i, 1, n) read(a[i]);
    s[0] = 0;
    FOR(i, 1, n) s[i] = s[i - 1] + a[i];
    CH[1].reset(n); CH[0].reset(n);
    int d = 0;
    FOR(j, 1, k + 1) {
        d = 1 - d;
        CH[1 - d].reset(n + 1);
        FOR(i, 1, n) {
            CH[1 - d].add(s[i - 1], f[1 - d][i - 1] - s[i - 1] * s[n], i - 1);
            f[d][i] = CH[1 - d].Get(s[i], pre[j][i]) + s[i] * (s[n] - s[i]);
        }
    }
    writeln(f[d][n]);
    trace(k + 1, n);
}
