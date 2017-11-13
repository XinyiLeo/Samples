clc;clear all;close all;

EbN0dB=1:11;%设定信噪比
errLimit=500;
N=100;
for ii=1:length(EbN0dB)
    errCount=0;
    totalN=0;
    sigma2(ii)=1/(4*(10^(EbN0dB(ii)/10)))*10;
    while errCount<errLimit
        bits = rand(1,N)>0.5;
        
        %编码调制
        for i=1:4:N-3
            d=bits(i:i+3);
            xd = (2*d(1,2)+1)*(-2*d(1,1)+1) + (2*d(1,4)+1)*(-2*d(1,3)+1) * j;   % modulation
            syms((i+3)/4)=xd;
        end
        
        ndi = sqrt(2*sigma2(ii))/2*randn(1,N/4) ;     %产生噪声
        ndq = sqrt(2*sigma2(ii))/2*randn(1,N/4) ;
        nd = ndi+j*ndq ;
        receiver = syms + nd ;
 
        %解调
        for i=1:4:N-3
            idata = real(receiver((i+3)/4));
            qdata = imag(receiver((i+3)/4));
            demo =[0 0 0 0];
            demo(1,1) = idata < 0;
            demo(1,2) = abs(idata) > 2;
            demo(1,3) = qdata < 0;
            demo(1,4) = abs(qdata) > 2;
        
            demodata(i:i+3)=demo;
        end
       
        temp = sum(abs(bits-demodata));
        errCount = errCount + temp;
        totalN = totalN + N;
    end
    ber(ii)=errCount/totalN;
end
semilogy(EbN0dB,ber,'r-o');
 
hold on;
grid on;
%理论性能曲线
berthe=berawgn(EbN0dB,'qam',16,1);
semilogy(EbN0dB,berthe,'b-*');
title('16QAM在AWGN信道下的仿真曲线与理论曲线');
axis([0 11 10^(-6) 1]);
xlabel('SNR in dB');
ylabel('BER');
legend('Simulation','Theoretical');
