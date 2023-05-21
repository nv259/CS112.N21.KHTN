#include <bits/stdc++.h>
using namespace std;




struct node
{
    node* child[2];
    float w;
    char c;
    node(float w = 0, char c = '\0')
    {
        this->w = w;
        this->c = c;
        child[0] = nullptr;
        child[1] = nullptr;
    }

    bool isleaf()
    {
        return c != '\0';
    }

    bool operator < (node const &T) const
    {
        return w > T.w || (w == T.w && c > T.c);
    }
};

struct heapnode
{
    node* rep;
    heapnode(float w = 0, char c = '\0')
    {
        rep = new node(w,c);
    }
    bool operator < (heapnode const &T) const
    {
        return (*rep) < (*T.rep);
    }
};

priority_queue <heapnode> q;
node* root = nullptr;
string codeword[256];

void init()
{
    q.push(heapnode(0.4,'A'));
    q.push(heapnode(0.1,'B'));
    q.push(heapnode(0.2,'C'));
    q.push(heapnode(0.15,'D'));
    q.push(heapnode(0.15,'_'));
}

void dfs(node *p, string s)
{
    if (p->isleaf())
    {
        codeword[int(p->c)] = s;
        cout << p->c << ' ' << s << '\n';
    }
    else
    {
        for (int i = 0; i < 2; i++)
            dfs(p->child[i],s + char('0'+i));
    }
}

void build()
{
    while (q.size() > 1)
    {
        heapnode u,v;
        u = q.top();q.pop();
        v = q.top();q.pop();
        heapnode t(u.rep->w + v.rep->w);
        t.rep->child[0] = u.rep;
        t.rep->child[1] = v.rep;
        q.push(t);
    }
    root = q.top().rep;
    dfs(root,"");
}

void encode()
{
    string s = "ABACABAD";
    string res = "";
    for (char c:s)
        res += codeword[int(c)];
    cout << "Encoded string of '" << s <<"' is: " << res << '\n';
}

void decode()
{
    string s = "100010111001010";
    string res = "";
    node* p = root;
    for(char c:s)
    {
        int val = c - '0';
        if (p->child[val] != nullptr)
            p = p->child[val];
        else
        {
            cout << "Can't decode\n";
            return;
        }
        if (p->isleaf())
        {
            res += p->c;
            p = root;
        }
    }
    cout << "Decoded string of '100010111001010' is: " <<  res << '\n';
}

int main()
{
    init();
    build();
    encode();
    decode();
    return 0;
}
