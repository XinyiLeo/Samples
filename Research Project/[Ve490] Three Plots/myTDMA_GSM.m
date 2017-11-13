%%%%%%TDMA GSM
clear all
TimeMax = 100000;                                                           % Number of time periods in slots
Allocated_bits = 100;                                                       % Allocated bits for a single slot
NodeMaxNum = 20;                                                            % Number of nodes we want to simulate
Allowed_Slots = 8;                                                          % Number of slots per frame
DataSet = cell(1,NodeMaxNum);                                               % Create a cell for all the datas. In cell 'i'
                                                                            % there are data when the number of nodes is 'i' 

for NodeNum = 1:NodeMaxNum                                                  % Write data into the cel
    Nodes = 1:NodeNum;
    DataSet{NodeNum}(1,:)=1:TimeMax;                                        % In each cell, the first line of data is time
    for i = 1:Allowed_Slots:TimeMax                                         % The second line is the allocated slot number
        if(NodeNum <= Allowed_Slots)                                        % The third line is the number of allocated bits in a slot
            DataSet{NodeNum}(2,i:i+NodeNum-1) = Nodes; 
        else
            DataSet{NodeNum}(2,i:i+Allowed_Slots-1) = Nodes(1:Allowed_Slots); 
        end
    end
    for i = 1:TimeMax
        if(DataSet{NodeNum}(2,i) ~= 0)
            DataSet{NodeNum}(3,i) = Allocated_bits;
        end
    end
end

figure(1)                                                                   % Plot the throughput vs. nodes
Throughput(DataSet,NodeMaxNum,Allowed_Slots);
xlabel('Number of Nodes','FontSize',10);
ylabel('Throughput(Gbps)','FontSize',10);
legend('Accumulative Throughtput','Average Throughput');
title('Throughput vs. Number of Nodes');

figure(2)                                                                   % Plot the throughput vs. nodes
Outage(DataSet,NodeMaxNum);
xlabel('Number of Nodes','FontSize',10);
ylabel('Outage Probability','FontSize',10);
title('Outage Probability vs. Number of Nodes');

figure(3)                                                                   % Plot of maximum delays vs. nodes
Delay(DataSet,NodeMaxNum,Allowed_Slots);
xlabel('Number of Nodes','FontSize',10);
ylabel('Maximum Delay(ms)','FontSize',10);
title('Maximum Delay vs. Number of Nodes');



