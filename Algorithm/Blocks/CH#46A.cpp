#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;
#define int long long
inline int gi(){
	int sum=0,f=1;char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return f*sum;
}
const int N=250010;
struct node{
	int x,y,m,p,r;
	int d;
}mg[N];
queue<int>Q;
int n,bl[N],md[510],B=500,vis[N];
struct block{
	int l,r;
}blo[510];
bool cmpm(node a,node b){
	return a.m<b.m;
}
bool cmpd(node a,node b){
	return a.d<b.d;
}
signed main(){
	mg[0].x=gi();
	mg[0].y=gi();
	mg[0].p=gi();
	mg[0].r=gi();mg[0].r*=mg[0].r;
	n=gi();B=sqrt(n);
	for(int i=1;i<=n;i++){
		mg[i].x=gi();mg[i].y=gi();
		mg[i].m=gi();mg[i].p=gi();
		mg[i].r=gi();mg[i].r*=mg[i].r;
		mg[i].d=(mg[i].x-mg[0].x)*(mg[i].x-mg[0].x)+(mg[i].y-mg[0].y)*(mg[i].y-mg[0].y);
	}
	sort(&mg[1],&mg[n+1],cmpd);int all=0;
	for(int i=1;i<=n;i+=B){
		blo[++all].l=i;blo[all].r=min(n,i+B-1);
		md[all]=mg[blo[all].r].d;
		sort(mg+i,mg+blo[all].r+1,cmpm);
	}
	Q.push(0);int ans=0;vis[0]=1;
	while(!Q.empty()){
		ans++;
		node now=mg[Q.front()];Q.pop();
		for(int i=1;i<=all;i++)
			if(md[i]<=now.r){
				for(int &j=blo[i].l;j<=blo[i].r && mg[j].m<=now.p;j++)
					if(!vis[j])vis[j]=1,Q.push(j);
			}
			else{
				for(int j=blo[i].l;j<=blo[i].r;j++){
					if(vis[j])continue;
					if(now.r>=mg[j].d && now.p>=mg[j].m){
						Q.push(j);vis[j]=1;
					}
				}
				break;
			}
	}
	printf("%lld\n",ans-1);
	return 0;
}
