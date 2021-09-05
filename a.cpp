#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int ans=2e9;
	for(int i=1 ; i<=sqrt(n) ; i++)
	{
		if(n%i==0)
		{

			int a=i;
			int b=n/i;
			//cout<<a<<" "<<((int)(b+2)/2)*((int)(a+2)/2)<<"\n";
			ans=min(ans,((b+2)/2)*((a+2)/2));
			swap(a,b);
			ans=min(ans,((b+2)/2)*((a+2)/2));
		}
	}
	cout<<ans<<"\n";
}
