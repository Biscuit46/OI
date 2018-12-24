#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
int n,m,B,id;
int v[50010],bl[50010];
map<int,int>M;
int val[50010],cnt[50010];
int f[510][510];
vector<int>g[50010];
void pre(int x){
    memset(cnt,0,sizeof(cnt));
    int mx=0,ans=0;
    for(int i=(x-1)*B+1;i<=n;i++){
	cnt[v[i]]++;
	int t=bl[i];
	if(cnt[v[i]]>mx || (cnt[v[i]]==mx && val[v[i]]<val[ans]))ans=v[i],mx=cnt[v[i]];
	f[x][t]=ans;
    }
}
int query(int l,int r,int x){
    int t=upper_bound(g[x].begin(),g[x].end(),r)-lower_bound(g[x].begin(),g[x].end(),l);
    return t;
}
int query(int a,int b){
    int ans,mx;
    ans=f[bl[a]+1][bl[b]-1];
    mx=query(a,b,ans);
    for(int i=a;i<=min(bl[a]*B,b);i++){
	int t=query(a,b,v[i]);
	if(t>mx || (t==mx && val[v[i]]<val[ans]))ans=v[i],mx=t;
    }
    if(bl[a]!=bl[b])
	for(int i=(bl[b]-1)*B+1;i<=b;i++){
	    int t=query(a,b,v[i]);
	    if(t>mx || (t==mx && val[v[i]]<val[ans]))ans=v[i],mx=t;
	}
    return ans;
}
int main(){
    scanf("%d%d",&n,&m);B=sqrt(n);
    for(int i=1;i<=n;i++){
	scanf("%d",&v[i]);
	if(M.find(v[i])==M.end()){
	    M[v[i]]=++id;val[id]=v[i];
	}
	v[i]=M[v[i]];
	g[v[i]].push_back(i);
    }
    for(int i=1;i<=n;i++)bl[i]=(i-1)/B+1;
    for(int i=1;i<=bl[n];i++)pre(i);
    int ans=0;
    while(m--){
	int a,b;scanf("%d%d",&a,&b);
	a=(a+ans-1)%n+1,b=(b+ans-1)%n+1;
	if(a>b)swap(a,b);
	ans=val[query(a,b)];
	printf("%d\n",ans);
    }
    return 0;
}
