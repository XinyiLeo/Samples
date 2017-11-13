function [Burst,GP,BurstName]=Burst_Str(str_type)
    if(strcmp(str_type,'NB'))
        GP = 8.25;                                                          
        Burst = zeros(1,148);
        BurstName = cell(1,148);
        for i = 1:3
            BurstName{i} = 'TB';
        end
        for i = 4:60
            BurstName{i} = 'Encrtpted Bit';
        end
        for i = 61
            BurstName{i} = 'Sign';
        end
        for i = 62:87
            BurstName{i} = 'Trained Bit';
        end
        for i = 88
            BurstName{i} = 'Sign';
        end
        for i = 89:145
            BurstName{i} = 'Encrypted Bit';
        end
        for i = 145:148
            BurstName{i} = 'TB';
        end
    elseif(strcmp(str_type,'FB'))
        GP = 8.25;                                                          
        Burst = zeros(1,148);
        BurstName = cell(1,148);
        for i = 1:3
            BurstName{i} = 'TB';
        end
        for i = 4:145
            BurstName{i} = 'Fixed Bit';
        end
        for i = 146:148
            BurstName{i} = 'TB';
        end
     elseif(strcmp(str_type,'SB'))
        GP = 8.25;                                                          
        Burst = zeros(1,148);
        BurstName = cell(1,148);
        for i = 1:3
            BurstName{i} = 'TB';
        end
        for i = 4:42
            BurstName{i} = 'Encrypted Bit';
        end
        for i = 43:106
            BurstName{i} = 'Synchronized Bit';
        end
        for i = 107:145
            BurstName{i} = 'Encrypted Bit';
        end
        for i = 146:148
            BurstName{i} = 'TB';
        end
     elseif(strcmp(str_type,'AB'))
        GP = 68.25;                                                          
        Burst = zeros(1,88);
        BurstName = cell(1,88);
        for i = 1:8
            BurstName{i} = 'TB';
        end
        for i = 9:49
            BurstName{i} = 'Synchronized Bit';
        end
        for i = 50:85
            BurstName{i} = 'Encrypted Bit';
        end
        for i = 86:88
            BurstName{i} = 'TB';
        end
    end
end