#include <bits/stdc++.h>
using namespace std;
typedef std::chrono::high_resolution_clock Clock;

struct edge
{
    int u, v, c;
    /// edge connect u and v with cost c

    edge(int u = 0, int v = 0, int c = 0)
    {
        this->u = u;
        this->v = v;
        this->c = c;
    }

    bool operator < (const edge &T) const
    {
        return c < T.c;
    }
};

struct node
{
    int u;
    int w;

    node(int u=0,int w=0)
    {
        this->u = u;
        this->w = w;
    }

    bool operator < (const node &T) const
    {
        return w < T.w;
    }
};

struct heap
{
    vector <int> mapping;
    vector <node> h;
    heap(int n = 0){
        while (h.size() > 0) h.pop_back();
        mapping = vector <int>(n+1,-1);
    }

    void upheap(int pos)
    {
        if (pos == 0) return;
        int par = (pos-1)>>1;
        if (h[pos] < h[par])
        {
            swap(mapping[h[pos].u],mapping[h[par].u]);
            swap(h[pos],h[par]);

            ///swap
            upheap(par);
        }
    }
    void downheap(int pos)
    {
        int t = pos;
        for (int child = pos*2+1; child <= min(pos*2+2,int(h.size()-1)); child++)
        if (h[child] < h[t])
            t = child;
        if (t == pos) return;
        swap(mapping[h[pos].u],mapping[h[t].u]);
        swap(h[pos],h[t]);
        ///swap
        downheap(t);
    }

    void update(int graphnode, int value)
    {
        int pos = mapping[graphnode];
        if (pos == -1)
        {
            heappush(node(graphnode,value));
            return;
        }
        if (h[pos].w < value) return;
        h[pos].w = value;
        upheap(pos);
    }

    void heappush(node p)
    {
        h.push_back(p);
        mapping[p.u] = h.size()-1;
        upheap(h.size()-1);
    }

    void heappop()
    {
        mapping[h[0].u] = -1;
        swap(h[0],h[h.size()-1]);
        mapping[h[0].u] = 0;
        h.pop_back();
        downheap(0);
    }

    bool empty()
    {
        return h.size() == 0;
    }

    node heaptop()
    {
        return h[0];
    }
};

struct dsu
{
    vector <int> par;
    dsu(int n)
    {
        par = vector <int>(n+2,-1);
    }

    int getroot(int u)
    {
        if (par[u] < 0) return u;
        par[u] = getroot(par[u]);
        return par[u];
    }

    bool union_sets(int u,int v)
    {
        u = getroot(u);
        v = getroot(v);
        if (u != v)
        {
            if (par[u] > par[v])
            {
                par[v] += par[u];
                par[u] = v;
            }
            else
            {
                par[u] += par[v];
                par[v] = u;
            }
            return true;
        }
        return false;
    }
};


int n,m;
vector <edge> e;
fstream fi;
vector <node> adj[100000];
vector <bool> visited(100000,false);


void inp()
{
    fi >> n >> m;
    e.clear();
    for (int i = 0; i < m; i++)
    {
        int u,v,c;
        fi >> u >> v >> c;
        e.push_back(edge(u,v,c));
    }
}


void kruskal()
{
    long long ans = 0;
    dsu d(n);
    sort(e.begin(),e.end());
    int cnt = 0;
    for (int i = 0; i < m; i++)
    {
        if (d.union_sets(e[i].u,e[i].v))
        {
            ans += e[i].c;
            cnt++;
        }
    }
    if (cnt != n-1)
    {
        cout << "Graph not connected\n";
        return;
    }
    cout <<"Result(Kruskal's algorithm): " << ans << '\n';
}


void init()
{
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        adj[i].clear();
    }
}

void prim2(int st=0)
{
    /// Input: starting node for prim
    /// prim's algorithm using adjacency list and heap with decrease-key method
    long long ans = 0;
    init();

    for (edge t:e)
    {
        int u,v,w;
        u = t.u;
        v = t.v;
        w = t.c;
        adj[u].push_back(node(v,w));
        adj[v].push_back(node(u,w));
    }

    heap h(n);
    h.heappush(node(st,0));
    int cnt = -1;
    while (!h.empty())
    {
        int u,w;
        node tmp = h.heaptop();
        h.heappop();
        u = tmp.u;
        w = tmp.w;
        ans += w;
        cnt++;
        visited[u] = true;
        for (node v:adj[u])
        if (!visited[v.u])
            h.update(v.u, v.w);
    }
    if (cnt != n-1)
    {
        cout << "Graph not connected\n";
        return;
    }
    cout << "Result(Prim's algorithm with adjacency list): " << ans << '\n';
}


void proc()
{
    /// Kruskal's algorithm
    auto start_time = Clock::now();
    kruskal();
    auto end_time = Clock::now();
    double runtime = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count()/1000.0;
    cout << fixed << setprecision(2) << "Kruskal's algorithm run time: " << runtime << " microseconds\n\n";


    /// Prim's algorithm with adjacency list
    start_time = Clock::now();
    prim2();
    end_time = Clock::now();
    cout << fixed << setprecision(2) << "Prim's algorithm run time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count()/1000.0 << " microseconds\n\n";
}


void empirical_test()
{
    fi.open("sparse_connected_graph.txt");
    cout << "Sparse connected graph:\n";
    inp();
    proc();
    fi.close();

    fi.open("dense_connected_graph.txt");
    cout << "Dense connected graph:\n";
    inp();
    proc();
    fi.close();
}


int main()
{
    empirical_test();
    return 0;
}
