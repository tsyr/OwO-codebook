3.11 	Burnside’s lemma
對於一個置換f，若一個染色方案s經過置換後不變(ex.轉?度是一樣的)，稱s為f的不動點。將f的不動點數目記為C(f)，則可以證明等價類數目為所有C(f)的平均值。
3.12 	Lucas’s theorem
Lucas’ Theorem:
  For non-negative integer n,m and prime P,
  C(m,n) mod P = C(m/M,n/M) * C(m%M,n%M) mod P
  = mult_i ( C(m_i,n_i) )
  where m_i is the i-th digit of m in base P, and note that when m_i < n_i, C(m_i,n_i)=0.
3.13 	Sum of Two Squares Thm (Legendre)
  For a given positive integer N, let
  D1 = (# of d \in \N dividing N that d=1(mod 4))
  D3 = (# of d \in \N dividing N that d=3(mod 4))
  then N can be written as a sum of two squares in
  exactly R(N) = 4(D1-D3) ways.
3.14 	Difference of D1-D3 Thm
  let N=2^t * [p1^e1 *...* pr^er] * [q1^f1 *...* qs^fs]
              <-mod 4 = 1 prime->   <-mod 4 = 3 prime->
  then D1 - D3 = (e1+1)(e2+1)...(er+1) if fi all even
                 0                     if any fi is odd
