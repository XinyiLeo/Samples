function result = TB_judge(channel_type,Eb_N0_dB)
    sr_br=1;                                                                % sr: symbol rate 
    PowS=1;      
    s = randi([0 1],1,3);
    EbN0Lin = 10^(Eb_N0_dB/10);                                             % multiple Eb/N0 values in linear
    PowN=sr_br*PowS/EbN0Lin;                                                % power of noise
    n = sqrt(PowN/2)*randn(1,3);                                            % Add white gaussian noise 
    if(strcmp(channel_type,'Rayleigh'))
        h = abs(1/sqrt(2)*(randn(1,3) + 1i*randn(1,3)));                    % Add rayleigh channel   
        y = s + n./h;                                                       % Rayleigh: Channel and noise Noise addition
    end
    sol = y > 0.5;
    result = size((find(sol - s)),2) >0;
end