// gp_boy[i][j]為第i個男的的第j個喜歡的女的的編號
// gp_girl[i][j]為第i個女的對第j個男的的好感度(越有好感數字越大)
// 答案：第i個男的和第boy[i]個女的結婚，girl[boy[i]]=i
int n, gp_boy[505][505], gp_girl[505][505], boy[505], girl[505], rankl[505];
void Gale_Shapley(){
  memset(boy, 0, sizeof(boy));
  memset(girl, 0, sizeof(girl));
  for (int i = 1; i <= n; i++)  rankl[i] = 1;
  while (1){
    int flag = 0;
    for (int i = 1; i <= n; i++){
      if (!boy[i]){
        int g = gp_boy[i][rankl[i]++];
        if (!girl[g]) boy[i] = g, girl[g] = i;
        else if (gp_girl[g][i] > gp_girl[g][girl[g]])
          boy[girl[g]] = 0, girl[g] = i, boy[i] = g;
        flag = 1;
      }
    }
    if (!flag) break;
  }
}
