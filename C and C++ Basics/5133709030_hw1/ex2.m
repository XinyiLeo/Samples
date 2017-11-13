 stadia=5000;
 meter=stadia*157.5;
 angle=7.2;
 circumference=(meter*360)/angle;
 circumferencekm=circumference/1000;
 radius=circumferencekm/(2*pi);
 fprintf('The circumference of the earth %gkm\n' ,circumferencekm);
 fprintf('The radius of the earth %gkm' ,radius);
