x=imread('p2','jpg');
a=x(:,:,1);
b=x(:,:,2);
c=x(:,:,3);
fd=fopen('picture.jpg','w');
subplot(1,3,1);
colormap gray;
plot(a);
subplot(1,3,2);
colormap gray;
plot(b);
subplot(1,3,3);
colormap gray;
plot(c);
title('Picture decomposition')
fclose(fd)
