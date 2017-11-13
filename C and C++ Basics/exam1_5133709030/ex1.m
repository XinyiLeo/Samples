function pl = ex1(p1,p2,p3,p4,step,size)
if p1+p2+p3+p4~=1
    disp('The sum of the probabilities should equal to 1')
end
x=zeros(step+1);
y=zeros(step+1);
 
 for i=2:step+1 
 a=rand;
 if a>= 0 && a<=p1
     x(i)=x(i-1);
     y(i)=y(i-1)+size;
 elseif a>p1 && a<=p1+p2
     x(i)=x(i-1)-size;
     y(i)=y(i-1);
 elseif a>p1+p2 && a<=p1+p2+p3
     x(i)=x(i-1);
     y(i)=y(i-1)-size;
 elseif a>p1+p2+p3 && a<=p1+p2+p3+p4
     x(i)=x(i-1)+size;
     y(i)=y(i-1);
 end
 end
 pl=plot(x,y);
 
     
         
