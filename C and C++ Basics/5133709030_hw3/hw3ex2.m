clear all; clc;
f=input('Input a function:');
i=input('Input an inteval:');
c=input('Input a precision');
a=i(1,1);
b=i(1,2);
cnt=0;
while b-(c/2) >= a+(c/2)   && cnt<=10000
    r= (a*f(b)-b*f(a))/(f(b)-f(a));
    if f(r)*f(a) >0 
        a=r;
    elseif f(r)*f(a) <0
        b=r;
    else 
         break
    end
    cnt=cnt+1;
end
disp(r);
format long;

    