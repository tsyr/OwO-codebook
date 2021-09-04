#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll go[55][55][55][55];
ll dp[55][55];

int used[55][55];
string s[55];
int n, m;

bool mul(int x, int y){
	go[x][y][x][y] = s[x][y] - '0';
	for (int k = x + y + 2; k < n + m; k += 2){
		for (int i = x; i < n; ++i){
			int j = k - i;
			if (j < y) break;
			if (i > 1 && s[i-1][j] == '*'){
				go[x][y][i][j] = max(go[x][y][i][j], go[x][y][i-2][j]* (s[i][j] - '0'));
				go[x][y][i][j] = max(go[x][y][i][j], go[x][y][i-1][j-1]* (s[i][j] - '0'));
			}
			if (j > 1 && s[i][j-1] == '*'){
				go[x][y][i][j] = max(go[x][y][i][j], go[x][y][i][j-2] * (s[i][j] - '0'));
				go[x][y][i][j] = max(go[x][y][i][j], go[x][y][i-1][j-1]* (s[i][j] - '0'));
			}
			if (go[x][y][i][j] > 1e15) return 0;
		}
	}
	return 1;
}



int main(){
	cin >> n >> m;
	for (int i = 0; i< n; ++i){
		cin >> s[i];
	}
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			if (!((i+j) & 1))
				if (!mul(i, j)){
					cout << "-1" << endl;
					return 0;
				}
		}
	}

	for (int kk = n + m - 2; kk >= 0; --kk){
		for (int x = 0; x < n; ++x){
			int y = kk - x;
			if (y < 0) break;
			for (int k = x + y; k < n + m; k += 2){
				for (int i = x; i < n; ++i){
					int j = k - i;
					if (j < y) break;
					if (j + 1 < m && s[i][j+1] == '+'){
						if (j + 2 < m) dp[x][y] = max(dp[x][y], go[x][y][i][j] + dp[i][j+2]);
						dp[x][y] = max(dp[x][y], go[x][y][i][j] + dp[i+1][j+1]);
					}
					if (i + 1 < n && s[i+1][j] == '+'){
						if (i + 2 < n) dp[x][y] = max(dp[x][y], go[x][y][i][j] + dp[i+2][j]);
						dp[x][y] = max(dp[x][y], go[x][y][i][j] + dp[i+1][j+1]);
					}
					if (dp[x][y] > 1e15){
						cout << "-1" << endl;
						return 0;
					}
				}
			}
		}
	}
	cout << dp[0][0] << endl;

}
