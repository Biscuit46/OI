# FFT总结

标签（空格分隔）： 多项式

---

# 前言
其实很早之前就写过FFT,但是发现自己都是靠背板子记忆的,一会儿就忘了,没怎么深刻理解.
所以再写一次总结来加深影响

# 引入
考虑两个多项式的乘法:
$a_1*x^0+a_2*x+a_3*x^2+...+a_n*x^{n-1}$
$b_1*x^0+b_2*x+b_3*x^2+...+b_n*x^{n-1}$

乘起来就是系数相乘,然后指数相加的得到的新的式子.
考虑实现:
```cpp
for(i=0;i<=n;i++)f[i]=gi();
for(i=0;i<=m;i++)g[i]=gi();
for(i=0;i<=n;i++)
    for(j=0;j<=m;j++)
        ans[i+j]+=f[i]*g[j];
```

在[洛谷3803](https://www.luogu.org/problemnew/show/P3803)跑了55分.

显然这样子直接相乘是无法满足我们的要求的.

考虑优化.

# 点值表示多项式
我们可以根据平面上的$n$个点唯一确定一个n次的多项式,然后考虑乘两个多项式,这样子肯定是$\Theta(n+m)$的可以计算,但是转换乘点表示多项式是$\Theta((n+m)^2)$的,完全过不了不是吗?

# 画风清晰的优化
考虑到我们在系数表示多项式的方面已经不能够再进一步往前推进了,只能够在点值上面找一点**!!!优化!!!**.

令**系数下标为偶数**的多项式转换为$A1(x)=\sum_{i=0}^{n/2}a_{i*2}*x^i$

同理可令**系数下标为奇数**的多项式为$A1(x)=\sum_{i=0}^{n/2}a_{i*2}*x^i$
则多项式为:$A(x)=A1(x^2)+x*A2(x^2)$
那么我们考虑我们取一些点令这个多项式变得优秀对吧.

取什么呢?有平方果断选取相反数,这样子可以让东西缩小一半.
$<x0,x1,x2,x3,x4,...,-x0,-x1,-x2,-x3,-x4,...>$
然后平方之后点集就成了:
$<x_0^2,x_1^2,x_2^2,x_3^2,...>$
当然记住是取n>>1个了!!

# 优化变得诡异
但是考虑到平方之后突然一下失去了性质,不能再一次减半,这...要命qwq
这就需要我们引入一个**n次单位复根**的玩意

## n次平方复根
### 定义
令$W_n=cos\frac{2\Pi}{n}+i*sin\frac{2\Pi}{n}\ (i=\sqrt{-1})$
那么$W_n^k=cos\frac{2\Pi*k}{n}+i*sin\frac{2\Pi*k}{n}$
一个形如
$$
<W_n^1,W_n^2,W_n^3,W_n^4,W_n^5,...,W_n^n>
$$
的n元组就叫做n次平方复根

### 引理
#### 消去引理
$W_{p*n}^{k*p}=W_n^k$

这个很简单啊,基本不需要证明

你代入到上面的式子就好了.

#### 折半引理

**P.S:最为重要同时也是最难的**
1. $k<=(n>>1)$
$(W_n^k)^2=(W_n^{k+(n>>1)})^2=W_{n>>1}^k$
2. $(n>>1)<k<=n$
$(W_n^k)^2=(W_n^{k-(n>>1)})^2=W_{n>>1}^{k-n>>1}$


## 最终优化
由于上面说过
$$
A(x)=A1(x^2)+x*A2(x^2)
$$
考虑对于n次平方复根的折半引理,发现:
对于这个式子
$$
A(x)=A1((W_n^k)^2)+W_n^kA2((W_n^k)^2)
    =A1(W_{n>>1}^{k\ mod\ n>>1})+W_n^kA2(W_{n>>1}^{k\ mod\ n>>1})
$$

欸,怎么和之前式子是一样的形式啊!

这样就可以分治的方法处理了!

# 坑点

至此,FFT的基本都已经介绍完毕.学习告一段落.



But,真的结束了?

考虑到分治的常数很大,我们不得不用迭代的方法代替分治.(真棒啊qwq)

---------

这一次就真的结束了

-----------

# 代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<queue>
#include<algorithm>
#define ll long long
#define file(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
using namespace std;
inline int gi(){
    int sum=0,f=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
    return f*sum;
}
inline ll gl(){
    ll sum=0,f=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
    return f*sum;
}
const int maxn=5000010;
const double Pi=acos(-1.0);
struct node{
    double x,y;
    node operator+(const node b)const{return (node){x+b.x,y+b.y};}
    node operator-(const node b)const{return (node){x-b.x,y-b.y};}
    node operator*(const node b)const{return (node){x*b.x-y*b.y,x*b.y+y*b.x};}
}f[maxn],g[maxn];
int r[maxn],limit;
void FFT(node *A,int type){
    for(int i=0;i<limit;i++)
        if(i<r[i])swap(A[i],A[r[i]]);
    for(int mid=1;mid<limit;mid<<=1){
        node Root=(node){cos(Pi/mid),type*sin(Pi/mid)};
        for(int R=mid<<1,j=0;j<limit;j+=R){
            node Mi=(node){1,0};
            for(int k=0;k<mid;k++,Mi=Mi*Root){
                node X=A[j+k],Y=Mi*A[j+mid+k];
                A[j+k]=X+Y;
                A[j+mid+k]=X-Y;
            }
        }
    }
        
}
int main(){
    int i,j,k,n,m;
    n=gi();m=gi();
    for(i=0;i<=n;i++)f[i].x=gi();
    for(i=0;i<=m;i++)g[i].x=gi();
    limit=1;int l=0;
    while(limit<=(n+m))limit<<=1,l++;
    for(i=0;i<limit;i++)
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    FFT(f,1);FFT(g,1);
    for(i=0;i<limit;i++)f[i]=f[i]*g[i];
    FFT(f,-1);
    for(i=0;i<=n+m;i++)printf("%d ",(int)(f[i].x/limit+0.5));
    puts("");
    return 0;
}
```



未完待续:
[NTT与任意模数NTT]()
[分治FFT]()
[狄利克雷卷积]()
[莫比乌斯函数]()

# 参考资料
[wuhan2005的博客](http://wuhan2005.ml/2018/10/01/xg-fft/)

# 图片来源
我有图片吗?只有公式啊!!!





