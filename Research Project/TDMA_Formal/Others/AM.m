f1=10e3;
fc=1e6;
fs=10e6;
dt=1/fs;
T=0.0005;
t=0:dt:T;
s=cos(2*pi*f1*t);
c=cos(2*pi*fc*t);
y=c+s.*c;
figure(1)
subplot(3,2,1)
plot(t,s);title('sÊ±ÓòÍ¼')
subplot(3,2,2)
spectrum(s,fs,T);title('sÆµÆ×Í¼')
xlim([0 20e3])

subplot(3,2,3)
plot(t,c);title('cÊ±ÓòÍ¼')
subplot(3,2,4)
spectrum(c,fs,T);title('cÆµÆ×Í¼')
xlim([0 20e5])

subplot(3,2,5)
plot(t,y);title('yÊ±ÓòÍ¼')
subplot(3,2,6)
spectrum(y,fs,T);title('yÆµÆ×Í¼')
xlim([8e5 12e5])

r=y.*c;
figure(2)
subplot(2,2,1)
plot(t,r);title('rÊ±ÓòÍ¼')
subplot(2,2,2)
spectrum(r,fs,T);title('rÆµÆ×Í¼')
xlim([-0.25e8 1.25e8])

N=100;
wP=fc/(fs/2);%WN=fN/fs¹éÒ»»¯µÄÖµ
b=fir1(N,wP,'low');
z=filter(b,1,r);
subplot(2,2,3)
plot(t,z);title('µÍÍ¨ÂË²¨ºóÊ±ÓòÍ¼') 
subplot(2,2,4)
spectrum(z,fs,T);title('µÍÍ¨ÂË²¨ºóÆµÆ×Í¼')
xlim([5e3 2e4]);
figure(3)
freqz(b,1,N);title('ÆµÂÊÏìÓ¦Í¼')
 





