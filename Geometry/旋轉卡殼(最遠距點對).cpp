    pt = ConvexHull(pt), n = pt.size();
    double ans = 0;
    int j = 0;
    for (int i = 0; i < n; i++){
        while (1){
            double ang=angle(pt[(i+1)%n]-pt[i],pt[(j+1)%n]-pt[j]);
            if (ang < pi)  j = (j + 1) % n;
            else  break;
        }
        ans = max(ans, len(pt[j] - pt[i]));
        ans = max(ans, len(pt[j] - pt[(i + 1) % n]));
    }
