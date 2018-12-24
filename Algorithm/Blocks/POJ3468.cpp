#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;
inline int gi()
{
	int sum=0,f=1;char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return f*sum;
}
const int N=200010;
#define int long long
int n,m,B,a[N],bl[N],sum[N],atag[N];
void Add(int l,int r,int k)
{
	for(int i=l;i<=min(r,bl[l]*B);i++)
	{
		sum[bl[l]]+=k;a[i]+=k;
	}
	if(bl[l]!=bl[r])
		for(int i=(bl[r]-1)*B+1;i<=r;i++)
		{
			sum[bl[r]]+=k;a[i]+=k;
		}
	for(int i=bl[l]+1;i<=bl[r]-1;i++)
	{
		sum[i]+=B*k;
		atag[i]+=k;
	}
}
int query(int l,int r)
{
	int ans=0;
	for(int i=l;i<=min(r,bl[l]*B);i++)
		ans+=atag[bl[l]]+a[i];
	if(bl[l]!=bl[r])
		for(int i=(bl[r]-1)*B+1;i<=r;i++)
			ans+=atag[bl[r]]+a[i];
	for(int i=bl[l]+1;i<=bl[r]-1;i++)
		ans+=sum[i];
	return ans;
}
signed main()
{
	n=gi();m=gi();B=sqrt(n);
	for(int i=1;i<=n;i++)a[i]=gi();
	for(int i=1;i<=n;i++){
		bl[i]=(i-1)/B+1;sum[bl[i]]+=a[i];
	}
	while(m--)
	{
		char ch=getchar();
		while(ch!='Q' && ch!='C')ch=getchar();
		int l=gi(),r=gi();
		if(ch=='Q')
		{
			printf("%lld\n",query(l,r));continue;
		}
		int k=gi();Add(l,r,k);
	}
	return 0;
}
