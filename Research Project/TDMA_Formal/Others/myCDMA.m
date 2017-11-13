%%%%%CDMA
clear all
f1=10;
f2=20;
f3=60;
tap=8; 
fs=0.5e3;
dt=1/fs;
T=1;
t=0:dt:T;
x1=cos(2*pi*f1*t);
x2=cos(2*pi*f2*t);
x3=cos(2*pi*f3*t);
pn1=2*(ms_gen(tap,1))-1;
pn2=2*(ms_gen(tap,2))-1;
pn3=2*(ms_gen(tap,3))-1;

figure(1)
subplot(3,2,1)
plot(t,x1);title('��Դ1����ͼ')
subplot(3,2,2)
spectrum2(x1,fs,T);title('��Դ1Ƶ��ͼ')
xlim([0 20])

subplot(3,2,3)
plot(t,x2);title('��Դ2����ͼ')
subplot(3,2,4)
spectrum2(x2,fs,T);title('��Դ2Ƶ��ͼ')
xlim([10 30])

subplot(3,2,5)
plot(t,x3);title('��Դ3����ͼ')
xlim([0 0.5])
subplot(3,2,6)
spectrum2(x3,fs,T);title('��Դ3Ƶ��ͼ')
xlim([50 70])

figure(2)
y1=x1'*pn1;
y1=reshape(y1',1,length(x1)*(2^tap-1));
% subplot(2,2,1)
% spectrum2(y1,fs*255,T);
% xlim([0 fs])
y2=x2'*pn2;
y2=reshape(y2',1,length(x2)*(2^tap-1));
% subplot(2,2,2)
% spectrum2(y2,fs*255,T);
% xlim([0 fs])
y3=x3'*pn3;
y3=reshape(y3',1,length(x3)*(2^tap-1));
% subplot(2,2,3)
% spectrum2(y3,fs*255,T);
% xlim([0 fs])
y=y1+y2+y3;
% subplot(2,2,4) 
% spectrum2(y,fs*255,T);
% xlim([0 fs])
t1=linspace(0,T,length(y));
subplot(2,1,1)
plot(t1,y);title('�����źŵ�ʱ��ͼ')
subplot(2,1,2)
spectrum2(y,fs*255,T);title('�����źŵ�Ƶ��ͼ')


figure(3)
r1=reshape(y,length(pn1),length(x1))';
z1=(r1*pn1')/length(pn1);
subplot(3,2,1)
plot(t,z1);title('����1����ͼ')
ylim([-1 1])
subplot(3,2,2)
spectrum2(z1,fs,T);title('����1Ƶ��ͼ')
xlim([0 20])
r2=reshape(y,length(pn2),length(x2))';
z2=(r2*pn2')/length(pn2);
subplot(3,2,3)
plot(t,z2);title('����2Ƶ����ͼ')
ylim([-1 1])
subplot(3,2,4)
spectrum2(z2,fs,T);title('����2Ƶ��ͼ')
xlim([10 30])
r3=reshape(y,length(pn3),length(x3))';
z3=(r3*pn3')/length(pn3);
subplot(3,2,5)
plot(t,z3);title('����3����ͼ')
ylim([-1 1])
xlim([0 0.5])
subplot(3,2,6)
spectrum2(z3,fs,T);title('����3Ƶ��ͼ')
xlim([50 70])
















