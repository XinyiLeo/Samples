function Throughput(DataSet,NodeMaxNum,Allowed_Slots)
    x = 1 : NodeMaxNum;
    y = zeros(1,NodeMaxNum);
    avg = zeros(1,NodeMaxNum);
    
    for i = 1: NodeMaxNum
        NumofFrame = floor(length(DataSet{i})/Allowed_Slots) ;
        y(i) = sum(DataSet{i}(3,:))./NumofFrame;                            % Total 
        avg(i) = y(i)/i;
    end
    plot(x,y);
    hold on;
    plot(x,avg);
end