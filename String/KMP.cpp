int fail[maxn]; //Failure function
void getfail(char *P, int *fail){
  int mm = strlen(P);
  fail[0] = 0;
  fail[1] = 0;
  for (int i = 1; i < mm; i++){
    int j = fail[i];
    while (j && P[i] != P[j])
      j = fail[j];
    fail[i + 1] = (P[i] == P[j]) ? j + 1 : 0;
  }
}
void find(char *T, char *P, int *fail){ //T裡面找P
  int nn = strlen(T), mm = strlen(P);
  getfail(P, fail);
  int j = 0;
  for (int i = 0; i < nn; i++){
    while (j && T[i] != P[j])
      j = fail[j];
    if (T[i] == P[j])
      j++;
    if (j == mm)
    { //do something  }
  }
}
// string a,b;  
// a.find(b, pos)回傳a在pos後第一次出現b的位置，找不到回傳a.npos。
