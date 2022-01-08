#include <bits/stdc++.h>
#include <iostream>
#define INF 1000000007
#define ll long long int
using namespace std;
 
ll min(ll x , ll y){if(x>y){return y;}return x;}

struct build_helper//return type in quering finction;
{
    ll min=INT64_MAX,max=0,sum=0,Xor=0;
};
 
class Segtree
{
private:
  vector<ll> segtree,max_seg,min_seg,Xoor;
  ll size;
 
  build_helper query_all(ll ql, ll qr, ll l, ll r, ll x)//min , max , sum ,xor  range quering function;
  {
    if (ql == l && qr == r)
    {build_helper z;
    z.sum=segtree[x];
    z.min=min_seg[x];
    z.max=max_seg[x];
    z.Xor=Xoor[x];
      return z;
    }
    else if ((qr < l || ql > r))
    {
        build_helper z;
    z.sum=0;
    z.min=INT64_MAX;
    z.max=0;
    z.Xor=0;
      return z;
    }
    ll mid = (l + r) / 2;
    build_helper a, b;
    if (ql <= mid && mid <= qr)
    {
      a = query_all(ql, mid, l, mid, 2 * x);
      b = query_all(mid + 1, qr, mid + 1, r, 2 * x + 1);
    }
    else
    {
      a = query_all(ql, qr, l, mid, 2 * x);
      b = query_all(ql, qr, mid + 1, r, 2 * x + 1);
    }
 
     a.sum=a.sum+b.sum;
     a.min=min(a.min,b.min);
     a.max=-1*min(-1*a.max,-1*b.max);
     a.Xor=a.Xor ^ b.Xor;
    return a;
  }
 
  
  build_helper build(ll l, ll r, vector<ll> &vec, ll x)// buiding all segment tree;
  {
    if (l == r)
    {build_helper z;
    max_seg[x]=vec[l];
    min_seg[x]=vec[l];
      segtree[x] = vec[l];
      Xoor[x]=vec[l];
      z.max=max_seg[x];
      z.min=min_seg[x];
      z.sum=segtree[x];
      z.Xor=Xoor[x];
      return z;
    }
    ll mid = (l + r) / 2;
    build_helper a = build(l, mid, vec, 2 * x);
    build_helper b = build(mid + 1, r, vec, 2 * x + 1);
    segtree[x] = a.sum + b.sum; 
    min_seg[x]=min(a.min,b.min);
    max_seg[x]=-1*min(-1*a.max,-1*b.max);
    Xoor[x]=a.Xor ^ b.Xor;
    a.Xor=Xoor[x];
    a.sum=segtree[x];
    a.min=min_seg[x];
    a.max=max_seg[x];
    return a;
  }
 
public:
  Segtree(){}
  Segtree(ll n, vector<ll> &vec)//building sum,min,max,xor segment tree;
  
  {
    size = n;
    segtree.resize(4 * n);
    max_seg.resize(4*n);
    min_seg.resize(4*n);
    Xoor.resize(4*n,0);
    build(0, n - 1, vec, 1);
  }
 
  build_helper query(ll ql, ll qr)// sum,min,max querying ,0 based (l,r);
  {
    return query_all(ql, qr, 0, size - 1, 1);
  }
  
};
 

int main()
{
 ll t,l,r;
 cin>>t;
    vector<ll>vec(n);
    for (int i = 0; i < q; i++)
    {cin>>vec[i];}
    Segtree A(n,vec);
    cin>>l>>r;
    cout<<A.query(l,r).sum<<" "<<A.query(l,r).max<<" "<<A.query(l,r).min;
  return 0;
}
