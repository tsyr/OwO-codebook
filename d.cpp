#include <bits/stdc++.h>
using namespace std;
#define ll long long

#define maxn 16
int n;
int A;
int a[maxn];
double r[maxn],p[maxn],s[maxn];
double dp[1<<maxn];

int main(){
	cin>>n>>A;
	n--;
	for(int i=0;i<n;i++){
		int R,P,S;
		scanf("%d%d%d%d",&a[i],&R,&P,&S);
		r[i]=R*0.01;
		p[i]=P*0.01;
		s[i]=S*0.01;
	}
	dp[0]=1;
	for(int S=1;S<(1<<n);S++){
		for(int i=S-1;i>=0;i=(i-1)&S){
			bool ok=1;
			double P=1;
			for(int j=0;j<n;j++)
				if(S&(1<<j)&&a[j]>A)
					ok=0;
			if(ok&&i==0){
				double ss=1,pp=1,rr=1;
				for(int j=0;j<n;j++){
					if(S&(1<<j)) 
						pp*=p[j];
				}
				for(int j=0;j<n;j++){
					if(S&(1<<j)) 
						ss*=s[j];
				}
				for(int j=0;j<n;j++){
					if(S&(1<<j)) 
						rr*=r[j];
				}
				dp[S]=max(dp[S],ss+(1-pp-rr));
				dp[S]=max(dp[S],pp+(1-ss-rr));
				dp[S]=max(dp[S],rr+(1-pp-ss));
			}
			P=1;
			for(int j=0;j<n;j++){
				if(S&(1<<j)){
					if(!(i&(1<<j)))
						P*=s[j];
					else
						P*=r[j];
				}
			}
			dp[S]=max(dp[S],P*dp[i]);

			P=1;
			for(int j=0;j<n;j++){
				if(S&(1<<j)){
					if(!(i&(1<<j)))
						P*=r[j];
					else
						P*=p[j];
				}
			}
			dp[S]=max(dp[S],P*dp[i]);

			P=1;
			for(int j=0;j<n;j++){
				if(S&(1<<j)){
					if(!(i&(1<<j)))
						P*=p[j];
					else
						P*=s[j];
				}
			}
			dp[S]=max(dp[S],P*dp[i]);
			if(i==0) break;
		}
	}
	printf("%.10lf\n",dp[(1<<n)-1]);

}
