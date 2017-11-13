function V = ex2(a,b,p,n)
h= p*n*b;
j= -1 * (n^2) * a;
k= (n^3) *a*b;
V1= (-j+sqrt(j^2 -4*h*k))/(2*h);
V2= (-j-sqrt(j^2 -4*h*k))/(2*h);
V=[V1 V2];



