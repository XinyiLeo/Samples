close all;
clear all;
Eb_N0_dB = 0:30; 
% plot
[QAM16_AWGN_theory, QAM16_AWGN_simulation] = synthesis('16QAM','AWGN');
[QAM16_rayleigh_theory, QAM16_rayleigh_simulation] = synthesis('16QAM','rayleigh');

figure
semilogy(Eb_N0_dB,QAM16_AWGN_theory,Eb_N0_dB,QAM16_AWGN_simulation,'o');
hold on
semilogy(Eb_N0_dB,QAM16_rayleigh_theory,Eb_N0_dB,QAM16_rayleigh_simulation,'o');

axis([0 30 10^-6 1])
grid on
legend('16QAM-AWGN-Theory',...
    '16QAM-AWGN-Simulation', '16QAM-Rayleigh-Theory', '16QAM-Rayleigh-Simulation');
xlabel('Eb/No, dB');
ylabel('Bit Error Rate');
title('BER for 16QAM modulation in AWGN and Rayleigh channel');