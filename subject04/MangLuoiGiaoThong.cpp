#include <bits/stdc++.h>
using namespace std;
/// Mang luoi giao thong
/// Nhom 15

const int MAXN = 100000;

int n,m;

/// Danh sach ke
vector <int> adj[MAXN+1];

///Mang danh dau nut da tham
bool visited[MAXN+1];


int cnt = 0;
long long ans = 0;

void Nhap()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int u)
{
    if (visited[u]) return;

    visited[u] = true;
    cnt++;

    for (int v:adj[u])
        dfs(v);
}

void Tinh()
{
    for (int u = 1; u <= n; u++)
    if (!visited[u])
    {
        /// Khoi tao lai bien dem cnt
        cnt = 0;
        dfs(u);

        /// Voi thanh phan lien thong co k dinh, so cap khong di duoc la k*(n-k)
        ans += 1LL*cnt*(n-cnt);
    }
}

void Xuat()
{
    /// Vi thuat toan dem ca cap a - b va b - a nen ta chia ket qua cho 2
    ans /= 2;
    cout << ans;
}


int main()
{
    Nhap();
    Tinh();
    Xuat();
    return 0;
}
