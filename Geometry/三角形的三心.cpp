P inCenter( P &A,  P &B,  P &C) { // 内心
    double a = len(B-C), b = len(C-A), c = len(A-B);
    return (A * a + B * b + C * c) / (a + b + c);
}
P circumCenter( P &a,  P &b,  P &c) { // 外心
    P bb = b - a, cc = c - a;
    double db=bb.X*bb.X+bb.Y*bb.Y, dc=cc.X*cc.X+cc.Y*cc.Y, d=2*(bb ^ cc);
    return a-P(bb.Y*dc-cc.Y*db, cc.X*db-bb.X*dc) / d;
}
P othroCenter( P &a,  P &b,  P &c) { // 垂心
    P ba = b - a, ca = c - a, bc = b - c;
    double Y = ba.Y * ca.Y * bc.Y,
      A = ca.X * ba.Y - ba.X * ca.Y,
      x0= (Y+ca.X*ba.Y*b.X-ba.X*ca.Y*c.X) / A,
      y0= -ba.X * (x0 - c.X) / ba.Y + ca.Y;
    return P(x0, y0);
}
