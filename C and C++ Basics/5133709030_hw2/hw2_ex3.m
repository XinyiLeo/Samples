clear; clc;
item(1)=struct('type','Jumpers','color','Blue','quantity','[2]','bought','4/2005');
item(2)=struct('type','Jumpers','color','Brown','quantity','[3]','bought','2/2013');
item(3)=struct('type','Jumpers','color','Green','quantity','[5]','bought','1/2014');
item(4)=struct('type','Trousers','color','Black','quantity','[3]','bought','6/2012');
item(5)=struct('type','Trousers','color','Grey','quantity','[2]','bought','4/2011');
item(6)=struct('type','Trousers','color','White','quantity','[1]','bought','12/2013');
item(7)=struct('type','T-shirts','color','Blue','quantity','[1]','bought','5/2010');
item(8)=struct('type','T-shirts','color','Green','quantity','[2]','bought','9/2009');
item(9)=struct('type','T-shirts','color','Red','quantity','[3]','bought','1/2012');
item(10)=struct('type','T-shirts','color','White','quantity','[2]','bought','3/2008');
item(11)=struct('type','T-shirts','color','Yellow','quantity','[1]','bought','11/2012')
[m,i]=max([item(1:11).quantity])
item(i).type
item(i).color
a=[];
for t=1:11
space=strfind(item(t).bought,'/'); 
month(t)=str2num(item(t).bought(1:space-1)); 
year(t)=str2num(item(t).bought(space+1:end));
quantities(t)=str2num(item(t).quantity(2));
  if month(t)<=5
    age(t)=2014-year(t);
  else age(t)=2014-year(t)-1;
  end
product(t)= quantities(t) * age(t);
a=[a product(t)];
end
average=sum(a)/sum(quantities)


