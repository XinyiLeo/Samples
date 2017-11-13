close all;
clear all;
Eb_N0_dB = 0:30; 
% plot
[QAM4_AWGN_theory, QAM4_AWGN_simulation] = synthesis('4QAM','AWGN');
[QAM4_rayleigh_theory, QAM4_rayleigh_simulation] = synthesis('4QAM','rayleigh');

figure
semilogy(Eb_N0_dB,QAM4_AWGN_theory,Eb_N0_dB,QAM4_AWGN_simulation,'o');
hold on
semilogy(Eb_N0_dB,QAM4_rayleigh_theory,Eb_N0_dB,QAM4_rayleigh_simulation,'o');

axis([0 30 10^-6 1])
grid on
legend('4QAM-AWGN-Theory', '4QAM-AWGN-Simulation',...
    '4QAM-Rayleigh-Theory', '4QAM-Rayleigh-Simulation');
xlabel('Eb/No, dB');
ylabel('Bit Error Rate');
title('BER for 4QAM modulation in AWGN and Rayleigh channel');