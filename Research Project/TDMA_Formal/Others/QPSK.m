%QPSK调制

%生成M个bits，均匀分布随机数
clear
M=1e3;
A=rand(1,M);
B(find(A<0.5))=-1;
B(find(A>=0.5))=1;%或者用randint（1，100）

%生成发送信号
R=B(1,1:2:M-1);
I=B(1,2:2:M);
S=1/sqrt(2)*(R+j*I);
figure(1)
plot(S,'*');title('原始信号')
EbN0=30;%单位比特信噪比
deta=0.5*10^(-EbN0/20);
N=deta*(randn(1,length(S))+j*randn(1,length(S)));%噪声
%接收信号
Rec=S+N;
figure(2)
plot(Rec,'.');title('加噪后信号') 

%解调，硬判决，恢复出原始比特数据流
s=[];
for m=1:length(S)
    if real(Rec(m))>=0 & imag(Rec(m))>=0
        s=[s 1 1];
    end
    if real(Rec(m))<0 & imag(Rec(m))>=0
        s=[s -1 1];
    end
    if real(Rec(m))<0 & imag(Rec(m))<0
        s=[s -1 -1];
    end
    if real(Rec(m))>=0 & imag(Rec(m))<0
        s=[s 1 -1];
    end
end
figure(3)
plot(s,'*')
error=s-B;
a1=find(error~=0);
rate=length(a1)/M;
ber(x)=log10(h/length(RE));
q(x)=log10(qfunc(sqrt(2*10^(EbN0(x)/10))));






