function Outage(DataSet,NodeMaxNum)
    x = 1 : NodeMaxNum;
    y = zeros(1,NodeMaxNum);
    
    for i = 1: NodeMaxNum
        HaveSet = zeros(1,1);
        for j = 1:length(DataSet{i})
            HaveSet = unique([DataSet{i}(2,j), HaveSet]);
        end
        HaveSet(HaveSet == 0) = [];
        y(i) = 1 - length(HaveSet)/i;
    end
    plot(x,y);
end