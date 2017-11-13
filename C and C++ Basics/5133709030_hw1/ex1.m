m=input('input a distance in meter: ');
A=m/400;
B=floor(A);
w=rem(m,400);
e=400-w;
disp(sprintf('He has covered %dlaps',B));
disp(sprintf('The distance remain to the next round is %dmeters' ,e));


