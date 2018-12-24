#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
int gi(){
    int x;scanf("%d",&x);
    return x;
}
#define ll long long
struct node{
    int l,r,id;
    ll a,b;
}a[50010];
int c[50010],s[50010];
int ans,bl[50010],n,m,B;
bool cmp(node a,node b){
    if(bl[a.l]==bl[b.l])return a.r<b.r;
    return a.l<b.l;
}
bool cmp2(node a,node b){
    return a.id<b.id;
}
void update(int x,int add){
    ans-=s[c[x]]*s[c[x]];
    s[c[x]]+=add;
    ans+=s[c[x]]*s[c[x]];
}
ll gcd(ll a,ll b){
    if(!b)return a;
    return gcd(b,a%b);
}
int main(){
    n=gi();m=gi();B=sqrt(n);
    for(int i=1;i<=n;i++)bl[i]=(i-1)/B+1;
    for(int i=1;i<=n;i++)c[i]=gi();
    for(int i=1;i<=m;i++){
        a[i].l=gi();a[i].r=gi();a[i].id=i;
    }
    sort(&a[1],&a[m],cmp);
    for(int i=1,l=1,r=0;i<=m;i++){
        for(;r<a[i].r;r++)update(r+1,1);
        for(;r>a[i].r;r--)update(r,-1);
        for(;l<a[i].l;l++)update(l,-1);
        for(;l>a[i].l;l--)update(l-1,1);
        if(a[i].l==a[i].r){
            a[i].a=0;a[i].b=1;continue;
        }
        a[i].a=ans-(a[i].r-a[i].l+1);
        a[i].b=(a[i].r-a[i].l+1)*1ll*(a[i].r-a[i].l);
        ll g=gcd(a[i].a,a[i].b);
        a[i].a/=g;a[i].b/=g;
    }
    sort(&a[1],&a[m],cmp2);
    for(int i=1;i<=m;i++)printf("%lld/%lld\n",a[i].a,a[i].b);
    return 0;
}
