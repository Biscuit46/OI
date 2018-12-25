[本文Link https://www.zybuluo.com/Biscuit46/note/1375354](https://www.zybuluo.com/Biscuit46/note/1375354)

# 前言
在看本文之前,需要确保您已经会了[FFT(总结在此)](https://www.zybuluo.com/Biscuit46/note/1375083)并且对于数学的掌握十分的好!  

当然,数学公式也很多,希望大家能够前往[这里看](https://www.zybuluo.com/Biscuit46/note/1375354)

# 优化
我们考虑一下为什么FFT特别的慢,但是怎么优化呢?

FFT慢的原因是:用了许多的实数导致运算复杂,而且容易出现精度问题,所以怎么解决?

发现一个神奇的东西:

$(W_n)^n=1,(W_n)^{n/2}=-1$

有了这个不就是和原根很相同吗?

下面有高能预警:
引用yyb的话语:(主要是我自己说不清楚qwq)

> 假设p的原根是g
> 再膜p意义下：
> $g^{\phi(p)}=1->g^{\phi(p)/2}=\sqrt{1}$
> 因为原根不存在一个比$\phi(p)$小的数使得$g^k=1$
> 所以$g^{\phi(p)/2}=−1$
> 我们发现上面的性质也可以满足
> 所以，把n次单位复根可以替换成原根的$\phi(p)/(2^n)$来做
> 这样就解决了小数精度的问题

--------

但是非常遗憾的是NTT没有什么需要补充的,所以到此结束了qwq.

--------

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;
#define ll long long
#define file(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
inline int gi(){
    int sum=0,f=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
    return f*sum;
}
const int P=998244353,G=3,N=5000010;
int f[N],g[N],limit,r[N],n,m;
int Pow(int a,int b){
    int  ret=1;
    while(b){
        if(b&1)ret=(1ll*ret*a)%P;
        a=(1ll*a*a)%P;b>>=1;
    }
    return ret%P;
}
void ntt(int*A,int flag){
    for(int i=0;i<limit;i++)if(i<r[i])swap(A[i],A[r[i]]);
    for(int mid=1;mid<limit;mid<<=1){
        int root=Pow(G,(P-1)/(mid<<1));
        for(int R=mid<<1,j=0;j<limit;j+=R){
            int w=1;
            for(int k=0;k<mid;k++,w=1ll*w*root%P){
                int x=A[j+k],y=1ll*w*A[mid+j+k]%P;
                A[j+k]=(x+y)%P;A[mid+j+k]=(x-y+P)%P;
            }
        }
    }
    if(flag==-1)reverse(&A[1],&A[limit]);
}
int main(){
    n=gi();m=gi();
    for(int i=0;i<=n;i++)f[i]=gi();
    for(int i=0;i<=m;i++)g[i]=gi();
    limit=1;int l=0;
    while(limit<=(n+m))limit<<=1,l++;
    for(int i=0;i<limit;i++)
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    ntt(f,1);ntt(g,1);
    for(int i=0;i<limit;i++)f[i]=1ll*f[i]*g[i]%P;
    ntt(f,-1);
    int inv=Pow(limit,P-2);
    for(int i=0;i<limit;i++)f[i]=1ll*f[i]*inv%P;
    for(int i=0;i<=n+m;i++)printf("%d ",f[i]);
    puts("");
    return 0;
}
```








