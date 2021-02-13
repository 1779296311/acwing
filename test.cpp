#include <bits/stdc++.h>
using ll = long long;
#define lowbit(x) x&(-x)
const ll N = 501000;
struct line_tree
{
    ll l,r,dat;
    #define l(x) (x)<<1
    #define r(x) ((x)<<1)+1
} t[N<<2];
ll a[N],c[N],b[N],i,j,n,m;
ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
}
ll sum(ll x)
{
    ll ans=0;
    for(;x;x-=lowbit(x))
        ans+=c[x];
    return ans;
}
void add(ll x,ll y)
{
    for(;x<=n;x+=lowbit(x))
        c[x]+=y;
}
void build(ll p,ll l,ll r)
{
    t[p].l=l;
    t[p].r=r;
    if (l==r)
    {
        t[p].dat=b[l];
        return ;
    }
    ll mid=(l+r)>>1;
    build(l(p),l,mid);
    build(r(p),mid+1,r);
    t[p].dat=gcd(t[l(p)].dat,t[r(p)].dat);
}
void change(ll p,ll x,ll v)
{
    if (t[p].l==t[p].r)
    {
        t[p].dat+=v;
        return ;
    }
    ll mid=(t[p].l+t[p].r)>>1;
    if (x<=mid)
        change(l(p),x,v);
    else
        change(r(p),x,v);
    t[p].dat=gcd(t[l(p)].dat,t[r(p)].dat);
}
ll ask(ll p,ll l,ll r)
{
    if (l<=t[p].l && r>=t[p].r)
        return t[p].dat;
    ll mid=(t[p].l+t[p].r)>>1;
    ll val=0;
    if (l<=mid)
        val=gcd(val,ask(l(p),l,r));
    if (r>mid)
        val=gcd(val,ask(r(p),l,r));
    return abs(val);
}
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        b[i]=a[i]-a[i-1];
    }
    build(1,1,n);
    while(m--)
    {
        char str[2]; 
        scanf("%s", str);
        ll l,r,x;
        scanf("%lld%lld",&l,&r);
        if (str[0]=='C')
        {
            scanf("%lld\n",&x);
            change(1,l,x);
            if (r<n)
                change(1,r+1,-x);
            add(l,x);
            add(r+1,-x);
        }
        else
        {
            scanf("\n");
            ll ans=a[l]+sum(l);
            ll ans_2=l<r ? ask(1,l+1,r):0;
            printf("%lld\n",gcd(ans,ans_2));
        }
    }
    return 0;
}
