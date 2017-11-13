%%%%%%TDMA
clear all
f1=10;
fs=100;
dt=1/fs;
T=10;
T1=3*T+2*dt;
t=0:dt:T;
t1=0:dt:T1;

%生成三个信号源
y1=cos(2*pi*f1*t);
y2=t;
y2(1:5/dt+1)=0;
y2(5/dt+2:T/dt+1)=1;
y3=sin(2*pi*t);
y3(find(y3>=0))=1;
y3(find(y3<0))=0;

figure(1)
subplot(3,2,1)
plot(t,y1);title('Signal 1 Waveform')
xlim([0 1])
subplot(3,2,2)
spectrum2(y1,fs,T);title('Signal 1 Spectrum')
xlim([0 20])
subplot(3,2,3)
plot(t,y2);title('Signal 2 Waveform')
ylim([-1 2])
subplot(3,2,4)
spectrum2(y2,fs,T);title('Signal 2 Spectrum')
xlim([0 10])
subplot(3,2,5)
plot(t,y3);title('Signal 3 Waveform')
ylim([-1 2])
subplot(3,2,6)
spectrum2(y3,fs,T);title('Signal 3 Spectrum')
xlim([0 20])

%多址
y=t1;
y(1:3:length(t1))=y1;
y(2:3:length(t1))=y2;
y(3:3:length(t1))=y3;
%另外一种方法
%y=reshape([y1;y2;y3],1,3*length(t));

figure(2)
subplot(2,1,1)
plot(t1,y);title('Input Signal Waveform')
subplot(2,1,2)
spectrum2(y,fs,T1);title('Input Signal Spectrum')
xlim([0 100])

%拆开
y4=y(1:3:length(t1));
y5=y(2:3:length(t1));
y6=y(3:3:length(t1));
%另外一种方法
% r=reshape(y,3,length(t));
% y4=r(1,:);
% y5=r(2,:);
% y6=r(3,:);

figure(3)
subplot(3,2,1)
plot(t,y4);title('Recieve Waveform - Sig1')
xlim([0 1])
subplot(3,2,2)
spectrum2(y4,fs,T);title('Spec. Rec. 1')
xlim([0 20])
subplot(3,2,3)
plot(t,y5);title('Recieve Waveform - Sig1')
ylim([-1 2])
subplot(3,2,4)
spectrum2(y5,fs,T);title('Spec. Rec. 2')
xlim([0 10])
subplot(3,2,5)
plot(t,y6);title('Recieve Waveform - Sig1')
ylim([-1 2])
subplot(3,2,6)
spectrum2(y6,fs,T);title('Spec. Rec. 3')
xlim([0 20])






