#include <bits/stdc++.h>
#include <iostream>
#define INF 1000000007
#define ll long long int
using namespace std;
ll min(ll, ll);
class Segtree
{
    vector<ll> ptr;
    ll size;

private:
    ll query_min(ll ql, ll qr, ll l, ll r, ll x)
    {
        if (ql == l && qr == r)
        {
            return ptr[x];
        }
        else if ((qr < l || ql > r))
        {
            return INF;
        }
        ll mid = (l + r) / 2;
        ll a, b;
        if (ql <= mid && mid <= qr)
        {
            a = query_min(ql, mid, l, mid, 2 * x);
            b = query_min(mid + 1, qr, mid + 1, r, 2 * x + 1);
        }
        else
        {
            a = query_min(ql, qr, l, mid, 2 * x);
            b = query_min(ql, qr, mid + 1, r, 2 * x + 1);
        }

        return min(a, b);
    }

public:
    ll build(ll l, ll r, vector<ll> &vec, vector<ll> &ptr, ll x)
    {
        if (l == r)
        {
            ptr[x] = vec[l];
            return vec[l];
        }
        ll mid = (l + r) / 2;
        ll a = build(l, mid, vec, ptr, 2 * x);
        ll b = build(mid + 1, r, vec, ptr, 2 * x + 1);
        ptr[x] = min(a, b); // range sum:: a+b;
        return ptr[x];
    }
    Segtree(ll n, vector<ll> &vec)
    {
        size = n;
        ptr.resize(4 * n);
        build(0, n - 1, vec, ptr, 1);
    }
    ll range_min(ll ql, ll qr) { return query_min(ql, qr, 0, size - 1, 1); }
};

ll main()
{
    ll n;
    cin >> n;
    vector<ll> vec(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    class Segtree A(n, vec);
    ll l, r;
    cin >> l >> r;
    cout << A.range_min(l, r);
    return 0;
}
ll min(ll a, ll b)
{
    if (a > b)
    {
        return b;
    }
    return a;
}