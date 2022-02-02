#include <bits/stdc++.h>
using namespace std;
 
typedef struct matrix
{
	int size;
	int ele[128][128];
} matrix;

matrix add(matrix x, matrix y) {
	matrix c;
	c.size=x.size;
	for(int i=0; i<c.size; i++) {
		for(int j=0; j<c.size; j++) {
			c.ele[i][j]=x.ele[i][j]+y.ele[i][j];
		}
	}
	return c;
}

matrix sub(matrix x, matrix y) {
	matrix c;
	c.size=x.size;
	for(int i=0; i<c.size; i++) {
		for(int j=0; j<c.size; j++) {
			c.ele[i][j]=x.ele[i][j]-y.ele[i][j];
		}
	}
	return c;
}

void split_matrix(matrix x, matrix *a, matrix *b, matrix *c, matrix *d) {
	int n=x.size;
	for(int i=0; i<n/2; i++) {
		for(int j=0; j<n/2; j++) {
			a->ele[i][j]=x.ele[i][j];
		}
	}
	for(int i=0; i<n/2; i++) {
		for(int j=0; j<n/2; j++) {
			(*b).ele[i][j]=x.ele[i][n/2+j];
		}
	}
	for(int i=0; i<n/2; i++) {
		for(int j=0; j<n/2; j++) {
			(*c).ele[i][j]=x.ele[i+n/2][j];
		}
	}
	for(int i=0; i<n/2; i++) {
		for(int j=0; j<n/2; j++) {
			(*d).ele[i][j]=x.ele[i+n/2][j+n/2];
		}
	}
	return;
}

matrix merge(matrix a, matrix b, matrix c, matrix d) {
    matrix ans;
    int n=a.size;
    ans.size=2*a.size;
    for(int i=0; i<a.size; i++) {
        for(int j=0; j<a.size; j++) {
            ans.ele[i][j]=a.ele[i][j];
        }
    }
    for(int i=0; i<a.size; i++) {
        for(int j=0; j<a.size; j++) {
            ans.ele[i][j+n]=b.ele[i][j];
        }
    }
    for(int i=0; i<a.size; i++) {
        for(int j=0; j<a.size; j++) {
            ans.ele[i+n][j]=c.ele[i][j];
        }
    }
    for(int i=0; i<a.size; i++) {
        for(int j=0; j<a.size; j++) {
            ans.ele[i+n][j+n]=d.ele[i][j];
        }
    }
    return ans;
}

matrix strassen(matrix x, matrix y) {
	if(x.size==1) {
		matrix ans;
		ans.size=1;
		ans.ele[0][0]=x.ele[0][0]*y.ele[0][0];
		return ans;
	}
	//spliting matrix
	matrix a,b,c,d,e,f,g,h;
	a.size=b.size=c.size=d.size=x.size/2;
	e.size=f.size=g.size=h.size=y.size/2;

	split_matrix(x,&a,&b,&c,&d);
	split_matrix(y,&e,&f,&g,&h);
	
	matrix p1,p2,p3,p4,p5,p6,p7;
	p1.size=p2.size=p3.size=p4.size=x.size/2;
	p5.size=p6.size=p7.size=x.size/2;
	p1 = strassen(a,sub(f,h)); 
    p2 = strassen(add(a,b), h);
    p3 = strassen(add(c,d), e);       
    p4 = strassen(d,sub(g,e));
    p5 = strassen(add(a,d),add(e,h));       
    p6 = strassen(sub(b,d),add(g,h));
    p7 = strassen(sub(a,c),add(e,f));
    
    matrix c11,c12,c21,c22;
    c11.size=c12.size=c21.size=c22.size=x.size/2;
    
    //c11 = p5 + p4 - p2 + p6 
    c11=add(p5,p4); c11=add(c11,p6); c11=sub(c11,p2);
    //c12 = p1 + p2          
    c12=add(p1,p2);
    //c21 = p3 + p4
    c21=add(p3,p4);
    //c22 = p1 + p5 - p3 - p7 
    c22=add(p1,p5); c22=sub(c22,p3); c22=sub(c22,p7);
    matrix ans;
    ans.size=x.size;
    ans=merge(c11,c12,c21,c22);
    return ans;
}

int main() {
  //matrix multiplication;
	matrix a,b;
	int n;
	cin>>n;
	int po=1;
	while(po<n) po*=2;
	a.size=b.size=po;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin>>a.ele[i][j];
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin>>b.ele[i][j];
		}
	}
	matrix ans=strassen(a,b);
	/*matrix p,q,r,s;
	split_matrix(a,&p,&q,&r,&s); */
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cout<<ans.ele[i][j]<<" ";
			//cout<<p.ele[i][j]<<' '<<q.ele[i][j]<<' '<<r.ele[i][j]<<' '<<s.ele[i][j]<<'\n';
		}
		cout<<'\n';
	}
	return 0;
}