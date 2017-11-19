/*
  - Subtask 1 : Cứ tìm cặp số (a1, an), (a2, an - 1), ... mất (n + 1) / 2 lần tìm kiếm
  - Subtask 2 : Gọi dis khoảng cách 2 thằng max nhất và min nhất (Tìm mất N + 1). Khi đó kết quả sẽ lớn hơn hoặc bằng k = (dis - 1) / (N - 1) + 1.
                Từ đây tìm kiếm trên k đoạn liên tiếp không giao nhau tìm max, min, bô lô ba la...
*/
#include <iostream>
#include "gap.h"
#define n 100010
long long a[n];
 
long long max(long long a, long long b) {
    return a > b ? a : b;
}
 
long long findGap(int T, int N)
{
    if (T == 1) {
        MinMax(0, 1e18, &a[1], &a[N]);
        for(int i = 2; i <= (N + 1) / 2; i++) {
            MinMax(a[i - 1] + 1, a[N - i + 2] - 1, &a[i], &a[N - i + 1]);
        }
        long long ans = a[2] - a[1];
        for (int i = 2; i<N; i++) ans = max(ans, a[i + 1] - a[i]);
        return ans;
 
    }
	long long mn, mx, last, ans = -1;
    MinMax(0, 1e18, &mn, &mx);
    last = mn;
    long long BLOCKSIZE = (mx - mn) / (N - 1);
    if ((mx - mn) % (N - 1)) BLOCKSIZE++;
    bool ok = false;
    for (long long sBLOCK = mn + 1; sBLOCK <= mx;) {
        long long fBLOCK = sBLOCK + BLOCKSIZE - 1;
        if (fBLOCK >= mx) {
            fBLOCK = mx - 1;
            ok = true;
        }
        long long minNow, maxNow;
        if (fBLOCK < sBLOCK) break;
        MinMax(sBLOCK, fBLOCK, &minNow, &maxNow);
        if (minNow == -1) {
            sBLOCK = fBLOCK + 1;
            if (ok) break;
            continue;
        }
        if (minNow == maxNow) ans = max(ans, maxNow - last);
        else ans = max(ans, max(maxNow - minNow, minNow - last));
        last = maxNow;
        sBLOCK = fBLOCK + 1;
        if (ok) break;
    }
    ans = max(ans, mx - last);
    return ans;
}
