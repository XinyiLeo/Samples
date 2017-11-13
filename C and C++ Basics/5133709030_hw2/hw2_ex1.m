clear; clc
while true
year=input('input a year: ');
a=mod(year,4);
b=mod(year,100);
c=mod(year,400);
switch a
    case {0}
        switch b
            case {0}
                switch c
                    case {0}
                        disp('it is leap year');
                    otherwise 
                        disp('it is common year');
                end
            otherwise
                disp('it is leap year');
        end
    otherwise
        disp('it is common year');
end
end

                      
    
