clear; clc;
n=input('input a number: ');
n=n+1;
t=0 ;
while t==0;
    if isprime(n)==0;
        n=n+1 ,continue ;
    else isprime(n)==1;   
        for p=[1:sqrt(n)]
            for q=[1:sqrt(n)]
                if p^2 + q^2 ==n
                    t=1;
                    c=n;
                    m=p;
                    i=q;
                end
            end
        end
        if t==0
          n=n+1;
        end
    end
end
 switch t
     case {1}
 disp('the next Pythagorean prime is')
 disp(c)
 disp('the two squares are')
 disp(m^2)
 disp(i^2)
 
 end

   
    

    
               
                




