#include <bits/stdc++.h>
using namespace std;

int t[9];
int effect[9][9];
string color;
int ans = 1e9;
bool found = 0;
int state[9];
int sum[9];

void Nhap()
{
    string s;
    for (int i = 0; i < 9; i++)
    {
        cin >> t[i] >> s;
        for (char c:s)
            effect[i][int(c-'1')] = 1;
    }
    cin >> color;
    for (int i = 0; i < 9; i++)
    {
        if (color[i] == 'X')
            state[i] = 0;
        if (color[i] == 'V')
            state[i] = 1;
        if (color[i] == 'D')
            state[i] = 2;
    }
}

void Tinh()
{
    int lim = int(pow(3,9));
    for (int msk = 0; msk < lim; msk++)
    {
        int res = 0;
        int tmp = msk;

        for (int i = 0; i < 9; i++)
            sum[i] = 0;

        for (int i = 0; i < 9; i++)
        {
            int x = tmp%3;
            if (x == 0)
            {
                tmp /= 3;
                continue;
            }

            int waittime = x*t[i];
            res += waittime;

            for (int j = 0; j < 9; j++)
                sum[j] += effect[i][j] * x % 3;

            tmp/=3;
        }

        bool flag = true;
        for (int j = 0; j < 9; j++)
            if ((sum[j] + state[j])%3 != 0) flag = false;

        if (flag)
        {
            found = true;
            ans = min(ans,res);
        }
    }
}

void Xuat()
{
    if (!found)
        cout << -1;
    else
        cout << ans;
}


int main()
{
    Nhap();
    Tinh();
    Xuat();
    return 0;
}
