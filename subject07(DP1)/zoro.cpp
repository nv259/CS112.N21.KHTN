#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9+7;
long long dp[3000005][3];
long long fact[3000005];
long long invfact[3000005];
int n,q,k;

void inp()
{
    cin >> n;
    cin >> q;
}

long long pwr(long long x, long long y)
{
    if (y == 0) return 1;
    long long t = pwr(x,y/2);
    t = t*t%mod;
    if (y%2 == 1) t = t*x%mod;
    return t;
}

long long combination(int n,int k)
{
    if (k > n || k < 0) return 0;
    if (k == 0) return 1;
    if (n == k) return 1;
    return fact[n]*invfact[k]%mod*invfact[n-k]%mod;
}

void init()
{
    fact[0] = 1;
    for (int i = 1; i <= 3*n+1; i++)
        fact[i] = fact[i-1]*i%mod;
    invfact[3*n+1] = pwr(fact[3*n+1],mod-2);
    for (int i = 3*n; i > 0; i--)
        invfact[i] = invfact[i+1]*(i+1)%mod;

    dp[3*n][0] = 1;
    for (int i = 3*n-1; i >= 1; i--)
    {
        dp[i][0] = (dp[i+1][1] - dp[i+1][0] + combination(3*n+1,i+1) + mod*mod)%mod;
        dp[i][1] = (dp[i+1][2] - dp[i+1][1] + mod*mod)%mod;
        dp[i][2] = (dp[i+1][0] - dp[i+1][2] + mod*mod)%mod;
    }
}

void proc()
{
    while (q--)
    {
        cin >> k;
        cout << dp[k][0] << '\n';
    }
}

int main()
{
    inp();
    init();
    proc();
    return 0;
}
