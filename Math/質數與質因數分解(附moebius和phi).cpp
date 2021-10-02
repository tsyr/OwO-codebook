bool notprime[MAX];
int first[MAX]; //first[n]為n的最小質因數
int p[MAX], u[MAX], phi[MAX]; 
  //存質數,moebius函數,euler_phi
int top = 0;    //質數個數
void build(){
    u[1] = 1; phi[1] = 1;
    for (int i = 2; i < MAX; i++){
        if (!notprime[i]){
            first[i] = i; u[i] = -1; phi[i] = i – 1;
            p[top] = i;    top++;
        }
        for (int j = 0; i * p[j] < MAX && j < top;j++){
            first[i * p[j]] = p[j];
            notprime[i * p[j]] = 1;
		if (i % p[j]) {
        u[i * p[j]] = -u[i];
        phi[i * p[j]] = (p[j] - 1) * phi[i];
    }
		else { phi[i*p[j]]=p[j]*phi[i]; break;}
        }
    }
}

f(n)=∑_(d|n)▒g(d) ↔g(n)=∑_(d|n)▒u(n/d)f(d) 
 (這些質數p兩兩相異)
∑_(d|n)▒u(d)/d=ϕ(n)/n
∑_(d|n)▒ϕ(d) =n
