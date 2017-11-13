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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ԭʼ�ź�
s1=cos(2*pi*fs1*t);
c1=cos(2*pi*fc1*t);
s2=cos(2*pi*fs2*t);
c2=cos(2*pi*fc2*t);
s3=cos(2*pi*fs3*t);
c3=cos(2*pi*fc3*t);
figure(1)
subplot(3,2,1)
plot(t,s1);title('ԭʼ�ź�s1����')
xlim([0 0.1e-3])
subplot(3,2,2)
spectrum2(s1,fs,T);title('ԭʼ�ź�s1Ƶ��')
xlim([0 2e5])
subplot(3,2,3)
plot(t,s2);title('ԭʼ�ź�s2����')
xlim([0 0.1e-3])
subplot(3,2,4)
spectrum2(s2,fs,T);title('ԭʼ�ź�s2Ƶ��')
xlim([1e5 3e5])
subplot(3,2,5)
plot(t,s3);title('ԭʼ�ź�s3�Ĳ���')
xlim([0 0.1e-3])
subplot(3,2,6)
spectrum2(s3,fs,T);title('ԭʼ�ź�s3Ƶ��')
xlim([2e5 4e5])

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%����
y1=s1.*c1;
y2=s2.*c2;
y3=s3.*c3;
y=y1+y2+y3;
figure(2)
subplot(4,2,1)
plot(t,y1);title('s1���ƺ���')
xlim([0 1e-4])
subplot(4,2,2)
spectrum2(y1,fs,T);title('s1���ƺ�Ƶ��')
xlim([0 2e6])
subplot(4,2,3)
plot(t,y2);title('s2���ƺ���')
xlim([0 1e-4])
subplot(4,2,4)
spectrum2(y2,fs,T);title('s2���ƺ�Ƶ��')
xlim([1e6 3e6])
subplot(4,2,5)
plot(t,y3);title('s3���ƺ���')
xlim([0 1e-4])
subplot(4,2,6)
spectrum2(y3,fs,T);title('s3���ƺ�Ƶ��')
xlim([2e6 4e6])
subplot(4,2,7)
plot(t,y);title('���ƺ��ź���Ӳ���')
xlim([0 1e-4])
subplot(4,2,8)
spectrum2(y,fs,T);title('���ƺ��ź����Ƶ��')
xlim([0 4e6])

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%��һ���˲�
%����һ����ͨ
N1=100;         %�˲�������
fN1=1.2e6;      %ͨ���Ľ�ֹƵ��
wN1=fN1/(fs/2); %��һ��Ƶ��
b1_1=fir1(N1,wN1,'low');
z1=filter(b1_1,1,y);
%����һ����ͨ
fP2=1.7e6;      %ͨ������ʼƵ��
fN2=2.3e6;      %ͨ���Ľ�ֹƵ��
wP2=fP2/(fs/2); %��һ��Ƶ��
wN2=fN2/(fs/2); %��һ��Ƶ��
Wn=[wP2 wN2];
b1_2=fir1(N1,Wn,'bandpass');
z2=filter(b1_2,1,y);
%����ø�ͨ
fP3=2.6e6;      %ͨ������ʼƵ��
wP3=fP3/(fs/2); %��һ��Ƶ��
b1_3=fir1(N1,wP3,'high');
z3=filter(b1_3,1,y);
figure(3)
subplot(3,2,1)
plot(t,z1);title('��ͨ�˲�����1')
xlim([0 1e-4])
subplot(3,2,2)
spectrum2(z1,fs,T);title('��ͨ�˲�Ƶ��1')
xlim([0 2e6])
subplot(3,2,3)
plot(t,z2);title('��ͨ�˲�����2')
xlim([0 1e-4])
subplot(3,2,4)
spectrum2(z2,fs,T);title('��ͨ�˲�Ƶ��2')
xlim([1e6 3e6])
subplot(3,2,5)
plot(t,z3);title('��ͨ�˲�����3')
xlim([0 1e-4])
subplot(3,2,6)
spectrum2(z3,fs,T);title('��ͨ�˲�Ƶ��3')
xlim([2e6 4e6])

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%���
r1=z1.*c1;
r2=z2.*c2;
r3=z3.*c3;
% figure(4)
% subplot(3,1,1)
% spectrum2(r1,fs,T);title('�����Ƶ��1')
% subplot(3,1,2)
% spectrum2(r2,fs,T);title('�����Ƶ��2')
% subplot(3,1,3)
% spectrum2(r3,fs,T);title('�����Ƶ��3')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%�ڶ����˲�
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
plot(t,Z1);title('�ָ���s1����')
xlim([1e-5 0.1e-3])
subplot(3,2,2)
spectrum2(Z1,fs,T);title('�ָ���s1Ƶ��')
xlim([0 2e5])
subplot(3,2,3)
plot(t,Z2);title('�ָ���s2����')
xlim([1e-5 0.1e-3])
subplot(3,2,4)
spectrum2(Z2,fs,T);title('�ָ���s2Ƶ��')
xlim([1e5 3e5])
subplot(3,2,5)
plot(t,Z3);title('�ָ���s3����')
xlim([1e-5 0.1e-3])
subplot(3,2,6)
spectrum2(Z3,fs,T);title('�ָ���s3Ƶ��')
xlim([2e5 4e5])
















