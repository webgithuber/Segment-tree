#include <bits/stdc++.h>
#include <iostream>
#define INF 1000000007
#define ll long long int
using namespace std;
ll min(ll, ll);
class Merge_srt_tree
{
private:
  vector<vector<ll>> merge_tree;
  ll size;
  void merge(vector<ll> &a, vector<ll> &b, vector<ll> &c)
  {
    auto it_a = a.begin();
    auto it_b = b.begin();
    auto it_c = c.begin();
    while (!(it_a == a.end() && it_b == b.end()))
    {
      if (it_a != a.end() && it_b != b.end())
      {
        if (*it_a <= *it_b)
        {
          *it_c = *it_a;
          it_a++;
          it_c++;
        }
        else
        {
          *it_c = *it_b;
          it_b++;
          it_c++;
        }
      }
      else if (it_a != a.end())
      {
        *it_c = *it_a;
        it_a++;
        it_c++;
      }
      else
      {
        *it_c = *it_b;
        it_b++;
        it_c++;
      }
    }
  }
  vector<ll> &build(vector<ll> &vec, ll l, ll r, ll x)
  {

    if (l == r)
    {
      merge_tree[x].push_back(vec[l]);

      return merge_tree[x];
    }
    ll mid = (l + r) / 2;
    vector<ll> &a = build(vec, l, mid, 2 * x);
    vector<ll> &b = build(vec, mid + 1, r, 2 * x + 1);

    merge_tree[x].resize(r - l + 1);

    merge(a, b, merge_tree[x]);
    return merge_tree[x];
  }
  ll min_no(ll ql, ll qr, ll l, ll r, ll k, ll x)
  {
    if (ql == l && qr == r)
    {
      return upper_bound(merge_tree[x].begin(), merge_tree[x].end(), k - 1) - merge_tree[x].begin();
    }
    else if ((qr < l || ql > r))
    {
      return 0;
    }

    ll mid = (l + r) / 2;
    ll a, b;
    if (ql <= mid && mid <= qr)
    {
      a = min_no(ql, mid, l, mid, k, 2 * x);
      b = min_no(mid + 1, qr, mid + 1, r, k, 2 * x + 1);
    }
    else
    {
      a = min_no(ql, qr, l, mid, k, 2 * x);
      b = min_no(ql, qr, mid + 1, r, k, 2 * x + 1);
    }

    return a + b;
  }

public:
  Merge_srt_tree(ll n, vector<ll> &vec)
  {
    merge_tree.resize(4 * n);
    size = n;
    build(vec, 0, n - 1, 1);
  }
  ll min_query_range(ll ql, ll qr, ll k)
  {
    return min_no(ql, qr, 0, size - 1, k, 1);
  }
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
  Merge_srt_tree A(n, vec);
  cout << A.min_query_range(0, 10, 6);
  return 0;
}
