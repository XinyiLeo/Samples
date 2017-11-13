close all;
clear all;
Eb_N0_dB = 0:30; 
% plot
[BPSK_AWGN_theory, BPSK_AWGN_simulation] = synthesis('BPSK','AWGN');
[BPSK_rayleigh_theory, BPSK_rayleigh_simulation] = synthesis('BPSK','rayleigh');
[QAM4_AWGN_theory, QAM4_AWGN_simulation] = synthesis('4QAM','AWGN');
[QAM4_rayleigh_theory, QAM4_rayleigh_simulation] = synthesis('4QAM','rayleigh');
[QAM16_AWGN_theory, QAM16_AWGN_simulation] = synthesis('16QAM','AWGN');
[QAM16_rayleigh_theory, QAM16_rayleigh_simulation] = synthesis('16QAM','rayleigh');

figure
semilogy(Eb_N0_dB,BPSK_AWGN_theory,Eb_N0_dB,BPSK_AWGN_simulation,'o');
hold on
semilogy(Eb_N0_dB,BPSK_rayleigh_theory,Eb_N0_dB,BPSK_rayleigh_simulation,'o');
hold on
semilogy(Eb_N0_dB,QAM4_AWGN_theory,Eb_N0_dB,QAM4_AWGN_simulation,'o');
hold on
semilogy(Eb_N0_dB,QAM4_rayleigh_theory,Eb_N0_dB,QAM4_rayleigh_simulation,'o');
hold on
semilogy(Eb_N0_dB,QAM16_AWGN_theory,Eb_N0_dB,QAM16_AWGN_simulation,'o');
hold on
semilogy(Eb_N0_dB,QAM16_rayleigh_theory,Eb_N0_dB,QAM16_rayleigh_simulation,'o');

axis([0 30 10^-6 1])
grid on
legend('BPSK-AWGN-Theory', 'BPSK-AWGN-Simulation','BPSK-Rayleigh-Theory', ...
    'BPSK-Rayleigh-Simulation','4QAM-AWGN-Theory', '4QAM-AWGN-Simulation',...
    '4QAM-Rayleigh-Theory', '4QAM-Rayleigh-Simulation','16QAM-AWGN-Theory',...
    '16QAM-AWGN-Simulation', '16QAM-Rayleigh-Theory', '16QAM-Rayleigh-Simulation');
xlabel('Eb/No, dB');
ylabel('Bit Error Rate');
title('BER for Three different modulations in AWGN and Rayleigh channel');