#include <bits/stdc++.h>
using namespace std;


const int MAXN = 1000;


int n,m;
int a[MAXN+1];
int ans = 5000;

void Nhap()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
}


void bubblesort()
{
    for (int i = 1; i < n; i++)
    for (int j = 1; j <= n-i; j++)
    if (a[j] > a[j+1]) swap(a[j],a[j+1]);
}


void Tinh()
{
    /// Sap xep lai toa do
    bubblesort();

    /// duyet qua tung ban kinh
    int maxdist = a[n] - a[1]+1;
    for (int r = 1; r <= maxdist; r++)
    {
        int last = a[1]-1;
        int light = m;
        for (int i = 1; i <= n; i++)
        {
            if (a[i] <= last) continue;

            light--;
            last = a[i] + 2*r;
        }
        if (light >= 0)
        {
            ans = r;
            return;
        }
    }
}

void Xuat()
{
    cout << ans;
}


int main()
{
    Nhap();
    Tinh();
    Xuat();
    return 0;
}
