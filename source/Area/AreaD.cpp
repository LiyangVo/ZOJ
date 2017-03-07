
#include <stdio.h>

double det(double x1,double y1,double x2,double y2,double x3,double y3)
{
        return x1*y2+x2*y3+x3*y1-x2*y1-x3*y2-x1*y3;
}


int main()
{
        int n,i,j,count=0,temp;
        double x[1000],y[1000],area;
        while(1)
        {
                scanf("%d",&n);
                if (n==0) return 0;
                count++;
                if (count>1) printf("\n");
                printf("Figure %d: ",count);
                for(i=0;i<n;i++) scanf("%lf%lf",&x[i],&y[i]);
                if (n<3){
                        printf("Impossible\n");
                        continue;
                }
                for(i=0;i<n;i++)
                        for(j=(i+1)/n;j<i-1;j++){
                                temp=(i+1)%n;
                                if (det(x[j],y[j],x[i],y[i],x[j+1],y[j+1])*det(x[j],y[j],x[temp],y[temp],x[j+1],y[j+1])<=0&&
                                        det(x[i],y[i],x[j],y[j],x[temp],y[temp])*det(x[i],y[i],x[j+1],y[j+1],x[temp],y[temp])<=0) {
                                        printf("Impossible\n");
                                        goto quit;
                                }
                         }
                area=0;
                for(i=0;i<n;i++){
                        area+=x[i]*y[(i+1)%n];
                        area-=y[i]*x[(i+1)%n];
                }
                if (area<0) area*=-1;
                printf("%.2lf\n",area/2);
quit:;
        }
}