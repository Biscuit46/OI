[本文Link http://pmycqacf.ml/index.php/archives/lucas-exlucas.html](http://pmycqacf.ml/index.php/archives/lucas-exlucas.html)
其实这一次作业部落也有,但是宣传一下自己博客吧(这一次)

强烈推荐大家在这里看[http://pmycqacf.ml/index.php/archives/lucas-exlucas.html](http://pmycqacf.ml/index.php/archives/lucas-exlucas.html)

## 前言
数学真的伤脑经,如果一些东西不互质就有什么扩展定理.
在食用本文之前请先食用[这一篇](http://pmycqacf.ml/index.php/archives/crt-excrt.html)


<!--more-->


## Lucas
给出$n,m$,求出$C_n^m%p$.(p是质数):n,m比较大,p<=$10^5$

---------

考虑下面这个式子:
$C_n^m=C_{n\%p}^{m\%p}*C_{n/p}^{m/p}\%p$
这个我也不会证(挖坑),反正不长,~~记一记就好了~~.
然后就可以递归的搞了.
```cpp
int C(int m,int n){
	if(m>n)return 0;
	return (ll)(a[n]*qpow(a[m],p-2)*qpow(a[n-m],p-2))%p;
}
int Lucas(int m,int n){
	if(!m)return 1;
	return (1ll*C(m%p,n%p)*Lucas(m/p,n/p))%p;
}
```
练手题
[【模板】卢卡斯定理](https://www.luogu.org/problemnew/show/P3807)
直接套模板就好了,注意开ll.

## 扩展卢卡斯(exlucas)
给出$n,m,p$,求$C_n^m%p$,p不一定是质数.

这个怎么办呢?
考虑一下把p分解质因数,发现可以转换成k个同余方程的形式,然后crt可以合并.
所以现在的问题就是求出$n!%a_k^{p_k}$(为什么).
因为$C_n^m$可以变成$\frac{n!}{m!*(n-m)!}$.
所以就是这样子.
然后就用一大堆变换(挖坑待补)得出下面的一大堆代码:
```cpp
ll qpow(ll a,ll b,ll mod){
	ll ret=1;
	while(b){
		if(b&1)ret=(ret*a)%mod;
		b>>=1;a=(a*a)%mod;
	}
	return ret;
}
ll exgcd(ll a,ll b,ll&x,ll&y){
	if(!b){
		x=1;y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);y-=a/b*x;
	return d;
}
ll inv(ll a,ll b){
	ll x,y;
	ll d=exgcd(a,b,x,y);
	return (x+b)%b;
}
ll crt(){
	ll M=1,ret=0;
	for(int i=1;i<=num;i++)M*=number[i];
	for(int i=1;i<=num;i++){
		ll m=M/number[i];
		ret=(ret+m*inv(m,number[i])*r[i])%M;
	}
	return ret;
}
ll multi(ll n,ll pi,ll pk){
	if(!n)return 1;
	ll ans=1;
	for(ll i=2;i<=pk;i++)if(i%pi)ans=ans*i%pk;
	ans=qpow(ans,n/pk,pk);
	for(ll i=2;i<=n%pk;i++)if(i%pi)ans=ans*i%pk;
	return ans*multi(n/pi,pi,pk)%pk;
}
ll exlucas(ll n,ll m,ll pi,ll pk){
	if(m>n)return 0;
	ll a=multi(n,pi,pk),b=multi(m,pi,pk),c=multi(n-m,pi,pk);
	ll k=0;
	for(ll i=n;i;i/=pi)k+=i/pi;
	for(ll i=m;i;i/=pi)k-=i/pi;
	for(ll i=n-m;i;i/=pi)k-=i/pi;
	return a*inv(b,pk)%pk*inv(c,pk)%pk*qpow(pi,k,pk)%pk;
}
ll exall(ll n,ll m,ll p){
	for(int i=1;i<=num;i++)r[i]=exlucas(n,m,prime[i],number[i]);
	return crt();
}
void fz(ll n){
	num=0;
	for(ll i=2;i*i<=n;i++){
		if(n%i==0){
			ll pk=1;
			while(n%i==0)pk*=i,n/=i;
			++num;
			number[num]=pk;
			prime[num]=i;
		}
	}
	if(n>1){++num;number[num]=n;prime[num]=n;}
}
```
还是2道练手题
[【模板】扩展卢卡斯](https://www.luogu.org/problemnew/show/P4720)
[礼物](https://www.lydsy.com/JudgeOnline/problem.php?id=2142)


## 后话
以上题目的题解会陆续公布.(当然不算模板题,所以只有一道)
