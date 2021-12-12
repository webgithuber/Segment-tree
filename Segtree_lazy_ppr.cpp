#include <bits/stdc++.h>
#include <iostream>
#define INF 1000000007
#define ll long long int
using namespace std;
ll min(ll, ll);
class Segtree
{
private:
  vector<ll> segtree, lazy;
  ll size;
  ll query_sum(ll ql, ll qr, ll l, ll r, ll x)
  {
    if (ql == l && qr == r)
    {
      return segtree[x];
    }
    else if ((qr < l || ql > r))
    {
      return 0;
    }
    ll mid = (l + r) / 2;
    ll a, b;
    if (ql <= mid && mid <= qr)
    {
      a = query_sum(ql, mid, l, mid, 2 * x);
      b = query_sum(mid + 1, qr, mid + 1, r, 2 * x + 1);
    }
    else
    {
      a = query_sum(ql, qr, l, mid, 2 * x);
      b = query_sum(ql, qr, mid + 1, r, 2 * x + 1);
    }

    return a + b;
  }

  ll range_update_sum(ll ql, ll qr, ll val, ll l, ll r, ll x)
  {
    if (lazy[x] != 0)
    {
      segtree[x] += (r - l + 1) * lazy[x];
      if (l != r)
      {
        lazy[2 * x] += lazy[x];
        lazy[2 * x + 1] += lazy[x];
      }
      lazy[x] = 0;
    }
    if (ql == l && qr == r)
    {
      segtree[x] += (r - l + 1) * val;
      if (l != r)
      {
        lazy[2 * x] += val;
        lazy[2 * x + 1] += val;
      }
      return segtree[x];
    }

    if ((qr < l || ql > r))
    {
      return segtree[x];
    }
    ll mid = (l + r) / 2;
    ll a, b;
    if (ql <= mid && mid <= qr)
    {
      a = range_update_sum(ql, mid, val, l, mid, 2 * x);
      b = range_update_sum(mid + 1, qr, val, mid + 1, r, 2 * x + 1);
    }
    else
    {
      a = range_update_sum(ql, qr, val, l, mid, 2 * x);
      b = range_update_sum(ql, qr, val, mid + 1, r, 2 * x + 1);
    }
    segtree[x] = a + b;
    return a + b;
  }
  ll build(ll l, ll r, vector<ll> &vec, vector<ll> &segtree, ll x)
  {
    if (l == r)
    {
      segtree[x] = vec[l];
      return vec[l];
    }
    ll mid = (l + r) / 2;
    ll a = build(l, mid, vec, segtree, 2 * x);
    ll b = build(mid + 1, r, vec, segtree, 2 * x + 1);
    segtree[x] = a + b; // range min/max:: min(a,b);
    return segtree[x];
  }

public:
  Segtree(ll n, vector<ll> &vec)
  {
    size = n;
    segtree.resize(4 * n);
    lazy.resize(4 * n, 0);
    build(0, n - 1, vec, segtree, 1);
  }
  ll range_sum(ll ql, ll qr)
  {
    return query_sum(ql, qr, 0, size - 1, 1);
  }
  void range_update(ll ql, ll qr, ll val)
  {
    range_update_sum(ql, qr, val, 0, size - 1, 1);
  }
};
ll main()
{

  ll n;
  cin >> n;

  vector<ll> vec(n);
  for (ll i = 0; i < n; i++)
  {
    vec[i] = i;
  }
  class Segtree A(n, vec);
  ll l, r, val;
  cin >> l >> r;
  cout << A.range_sum(l, r);
  A.range_update(l, r, val);
  return 0;
}
