給你很多平面上的矩形，請求出它們覆蓋的總表面積。
有n<=100,000個矩形。
接下來有n列， L,R,D,U(0<=L<R<=1,000,000；0<=D<U<=1,000,000)代表矩形的左、右、下、上四個邊界座標。
const int maxn=1000000+10 ;

struct P{
    int x,d,u,val ;
    bool operator < (const P &rhs) const { return x<rhs.x ; }
}a[200000+10];

int ST[5*maxn],tag[5*maxn] ;

void modify(int l,int r,int L,int R,int id,int val){
    if(l==L && r==R) { tag[id]+=val ; return ; }
    int mid=(L+R)/2 ;
    if(r<=mid) modify(l,r,L,mid,2*id,val) ;
    else if(l>mid) modify(l,r,mid+1,R,2*id+1,val) ;
    else
        modify(l,mid,L,mid,2*id,val) ,
        modify(mid+1,r,mid+1,R,2*id+1,val) ;
    ST[id]= (tag[2*id] ? mid-L+1 : ST[2*id]) +
            (tag[2*id+1] ? R-mid : ST[2*id+1]) ;
}
main(){
    int n ; scanf("%d",&n) ;
    for(int i=0;i<n;i++) {
        int x1,y1,x2,y2 ;
        scanf("%d%d%d%d",&x1,&x2,&y1,&y2) ;
        a[2*i]=(P){x1,y1,y2-1,1} ;
        a[2*i+1]=(P){x2,y1,y2-1,-1} ;
    }
    sort(a,a+2*n) ;
    int x=0 , val=0 ;
    ll ans=0ll ;
    for(int i=0;i<2*n;i++) {
        ans+= (ll) (a[i].x-x)*val ;
        modify(a[i].d,a[i].u,0,maxn-1,1,a[i].val) ;
        x=a[i].x ;
        val=ST[1] ;
    }
    printf("%lld\n",ans) ;
}
