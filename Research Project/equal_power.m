clear all
clc
N0 = 1e-4;
B = 1;
Iteration = 1e2;                                                            % must be grater than 100
SNR_V_db = 1:30;
SNR_V    = 10.^(SNR_V_db/10);

    for i = 1 : length(SNR_V)
        Pt = N0 * SNR_V(i);
        for j = 1 : Iteration
            H = random('rayleigh',1,1,1);
            Capacity(i,j)=log2(1+Pt/(B*N0)* H);
        end
        Capacity_awgn(i)=log2(SNR_V(i));
    end
plot(SNR_V_db,mean(Capacity'))
hold on
plot(SNR_V_db,Capacity_awgn)
    
    
    
    