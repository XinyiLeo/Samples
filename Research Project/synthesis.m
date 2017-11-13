function [ber_theory,ber_sim]=synthesis(mod_type,channel)
         %Preparition part - Parameter setting
    N = 10^6;                                                                   % number of bits
    sr_br=1;                                                                    % for bpsk, br=sr. where br: bit rate  sr: symbol rate 
    PowS=1;      
    alpha16qam = [-3 -1 1 3];                                                   % 16-QAM alphabets
    Eb_N0_dB = 0:30;                                                            % multiple Eb/N0 values
    EbN0Lin = 10.^(Eb_N0_dB/10);                                                % multiple Eb/N0 values in linear
    
        % Transmitter
    if(strcmp(mod_type,'BPSK'))
        ip = rand(1,N)>0.5;                                                     % BPSK modulation 
        s = 2*ip-1;  
    elseif(strcmp(mod_type,'4QAM'))
        ip = rand(1,N) > 0.5 + 1i * rand(1,N) > 0.5;                            % 4QAM modulation
        s = (1/sqrt(2))*(2*ip - 1 - 1i);                                        % normalization of energy to 1
    elseif(strcmp(mod_type,'16QAM'))
        ip_re_fir = rand(1,N) > 0.5;                                            % 16QAM modulation
        ip_re_sec = rand(1,N) > 0.5;
        ip_im_fir = rand(1,N) > 0.5;
        ip_im_sec = rand(1,N) > 0.5;
        s = (2 * ip_re_sec + 1).*(-2 * ip_re_fir + 1) + (2 * ip_im_sec + 1).*(-2 * ip_im_fir + 1) * 1i; 
    end
    
    for ii = 1:length(Eb_N0_dB),  
        
        PowN=sr_br*PowS/EbN0Lin(ii);                                                  % power of noise
        if(strcmp(mod_type,'BPSK'))
            n = sqrt(PowN/2)*randn(1,N);                                             % Add white gaussian noise 
        elseif(strcmp(mod_type,'4QAM'))
            n = sqrt(PowN)/2*(randn(1,N)+1i*randn(1,N));                          
        elseif(strcmp(mod_type,'16QAM'))
            n = sqrt(5*PowN)/2 * (randn(1,N)+1i*randn(1,N));
        end
        
        h = abs(1/sqrt(2)*(randn(1,N) + 1i*randn(1,N)));                        % Add rayleigh channel
       
        if(strcmp(channel,'AWGN'))
             y = s + n;                                                         % AWGN:¡¡Only noise addition
        elseif(strcmp(channel,'rayleigh'))
             y = s + n./h;                                                      % Rayleigh: Channel and noise Noise addition
        end
               %demodulation
        if(strcmp(mod_type,'BPSK'))                                             % demoulation
            ipHat = real(y)>0;  
            nErr(ii) = size(find(ip- ipHat),2); 
        elseif(strcmp(mod_type,'4QAM'))
            ipHat_re = real(y)>0; % real
            ipHat_im = imag(y)>0; % imaginary
            nErr(ii) = (size(find((real(ip)- ipHat_re)),2) + size(find((imag(ip)- ipHat_im)),2))/2;     
        elseif(strcmp(mod_type,'16QAM'))
            ipHat_re = real(y); % real part
            ipHat_im = imag(y); % imaginary part

            ipHat_re_fir = ipHat_re < 0;
            ipHat_re_sec = abs(ipHat_re) > 2;
            ipHat_im_fir = ipHat_im < 0;
            ipHat_im_sec = abs(ipHat_im) > 2;
            
            nErr(ii) = (size(find(ip_re_fir- ipHat_re_fir),2)...
                + size(find(ip_re_sec- ipHat_re_sec),2)...
                + size(find(ip_im_fir- ipHat_im_fir),2)...
                + size(find(ip_im_sec- ipHat_im_sec),2)...
                )/4;   
        end                              
    end
    ber_sim = nErr/N;                                                            % simulated ber
    
    if(strcmp(mod_type,'BPSK') && strcmp(channel,'AWGN'))
        ber_theory = berawgn(Eb_N0_dB,'psk',2,'nodiff');                    % ber_theory = 0.5*erfc(sqrt(EbN0Lin));
    elseif(strcmp(mod_type,'BPSK') && strcmp(channel,'rayleigh'))
        ber_theory = berfading(Eb_N0_dB,'psk',2,1);                         % ber_theory = 0.5.*(1-sqrt(EbN0Lin./(EbN0Lin+1)));
    elseif(strcmp(mod_type,'4QAM') && strcmp(channel,'AWGN'))
        ber_theory = berawgn(Eb_N0_dB,'qam',4,'nodiff');                    % ber_theory = erfc(sqrt(0.5*EbN0Lin)) - (1/4)*(erfc(sqrt(0.5*EbN0Lin))).^2;
    elseif(strcmp(mod_type,'4QAM') && strcmp(channel,'rayleigh'))
        ber_theory = berfading(Eb_N0_dB,'qam',4,1);                         % ber_theory = 0.5.*(1-sqrt(EbN0Lin./(EbN0Lin+1)));
    elseif(strcmp(mod_type,'16QAM') && strcmp(channel,'AWGN'))
        ber_theory = berawgn(Eb_N0_dB,'qam',16,1);                           % ber_theory = 3/2*erfc(sqrt(0.1*EbN0Lin));
    elseif(strcmp(mod_type,'16QAM') && strcmp(channel,'rayleigh'))
        ber_theory = berfading(Eb_N0_dB,'qam',16,1);                         % ber_theory = 0.5.*(1-sqrt(((2/5)*EbN0Lin)./((2/5)*EbN0Lin+1)));
    end
end


