clear all;
fs1=100e3;
fs2=200e3;
fs3=300e3;
fc1=1e6;
fc2=2e6;
fc3=3e6;

fs=12e6;
dt=1/fs;
T=1e-3;
t=0:dt:T;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%原始信号
s1=cos(2*pi*fs1*t);
c1=cos(2*pi*fc1*t);
s2=cos(2*pi*fs2*t);
c2=cos(2*pi*fc2*t);
s3=cos(2*pi*fs3*t);
c3=cos(2*pi*fc3*t);
figure(1)
subplot(3,2,1)
plot(t,s1);title('原始信号s1波形')
xlim([0 0.1e-3])
subplot(3,2,2)
spectrum2(s1,fs,T);title('原始信号s1频谱')
xlim([0 2e5])
subplot(3,2,3)
plot(t,s2);title('原始信号s2波形')
xlim([0 0.1e-3])
subplot(3,2,4)
spectrum2(s2,fs,T);title('原始信号s2频谱')
xlim([1e5 3e5])
subplot(3,2,5)
plot(t,s3);title('原始信号s3的波形')
xlim([0 0.1e-3])
subplot(3,2,6)
spectrum2(s3,fs,T);title('原始信号s3频谱')
xlim([2e5 4e5])

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%调制
y1=s1.*c1;
y2=s2.*c2;
y3=s3.*c3;
y=y1+y2+y3;
figure(2)
subplot(4,2,1)
plot(t,y1);title('s1调制后波形')
xlim([0 1e-4])
subplot(4,2,2)
spectrum2(y1,fs,T);title('s1调制后频谱')
xlim([0 2e6])
subplot(4,2,3)
plot(t,y2);title('s2调制后波形')
xlim([0 1e-4])
subplot(4,2,4)
spectrum2(y2,fs,T);title('s2调制后频谱')
xlim([1e6 3e6])
subplot(4,2,5)
plot(t,y3);title('s3调制后波形')
xlim([0 1e-4])
subplot(4,2,6)
spectrum2(y3,fs,T);title('s3调制后频谱')
xlim([2e6 4e6])
subplot(4,2,7)
plot(t,y);title('调制后信号相加波形')
xlim([0 1e-4])
subplot(4,2,8)
spectrum2(y,fs,T);title('调制后信号相加频谱')
xlim([0 4e6])

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%第一次滤波
%先用一个低通
N1=100;         %滤波器介数
fN1=1.2e6;      %通带的截止频率
wN1=fN1/(fs/2); %归一化频率
b1_1=fir1(N1,wN1,'low');
z1=filter(b1_1,1,y);
%再用一个带通
fP2=1.7e6;      %通带的起始频率
fN2=2.3e6;      %通带的截止频率
wP2=fP2/(fs/2); %归一化频率
wN2=fN2/(fs/2); %归一化频率
Wn=[wP2 wN2];
b1_2=fir1(N1,Wn,'bandpass');
z2=filter(b1_2,1,y);
%最后用高通
fP3=2.6e6;      %通带的起始频率
wP3=fP3/(fs/2); %归一化频率
b1_3=fir1(N1,wP3,'high');
z3=filter(b1_3,1,y);
figure(3)
subplot(3,2,1)
plot(t,z1);title('带通滤波波形1')
xlim([0 1e-4])
subplot(3,2,2)
spectrum2(z1,fs,T);title('带通滤波频谱1')
xlim([0 2e6])
subplot(3,2,3)
plot(t,z2);title('带通滤波波形2')
xlim([0 1e-4])
subplot(3,2,4)
spectrum2(z2,fs,T);title('带通滤波频谱2')
xlim([1e6 3e6])
subplot(3,2,5)
plot(t,z3);title('带通滤波波形3')
xlim([0 1e-4])
subplot(3,2,6)
spectrum2(z3,fs,T);title('带通滤波频谱3')
xlim([2e6 4e6])

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%解调
r1=z1.*c1;
r2=z2.*c2;
r3=z3.*c3;
% figure(4)
% subplot(3,1,1)
% spectrum2(r1,fs,T);title('解调后频谱1')
% subplot(3,1,2)
% spectrum2(r2,fs,T);title('解调后频谱2')
% subplot(3,1,3)
% spectrum2(r3,fs,T);title('解调后频谱3')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%第二次滤波
N_low=100;
wp1=fc1/(fs/2);
b2_1=fir1(N_low,wp1,'low');
Z1=filter(b2_1,1,r1);
wp2=fc2/(fs/2);
b2_2=fir1(N_low,wp2,'low');
Z2=filter(b2_2,1,r2);
wp3=fc3/(fs/2);
b2_3=fir1(N_low,wp3,'low');
Z3=filter(b2_3,1,r3);
figure(5)
subplot(3,2,1)
plot(t,Z1);title('恢复后s1波形')
xlim([1e-5 0.1e-3])
subplot(3,2,2)
spectrum2(Z1,fs,T);title('恢复后s1频谱')
xlim([0 2e5])
subplot(3,2,3)
plot(t,Z2);title('恢复后s2波形')
xlim([1e-5 0.1e-3])
subplot(3,2,4)
spectrum2(Z2,fs,T);title('恢复后s2频谱')
xlim([1e5 3e5])
subplot(3,2,5)
plot(t,Z3);title('恢复后s3波形')
xlim([1e-5 0.1e-3])
subplot(3,2,6)
spectrum2(Z3,fs,T);title('恢复后s3频谱')
xlim([2e5 4e5])
















