%求频谱
function py=spectrum2(y,fs,T)
%生成信号并离散化

% f1=20e3;
% T=0.001;
% fs=200e3;  %fs=5倍的f1，规定
% 
% dt=1/fs;
% t=0:dt:T;
% y=cos(2*pi*f1*t);
% %plot(t,y); 

df=1/T;
dt=1/fs;
py=dt*abs(fft(y));
f=0:df:fs;
plot(f,py(1:length(f)));
xlim([0 fs/2])























