function Delay(DataSet,NodeMaxNum,Allowed_Slots)
    x = 1 : NodeMaxNum;
    y = zeros(1,NodeMaxNum);
   
    for i = 1: NodeMaxNum
        last = 0;
        for j = 0:Allowed_Slots:length(DataSet{i})                          % Find the last frame
            last = j;
        end
        PrevNode = DataSet{i}(2,last);
        Cur_Delay = 0;
        zero_count = 0;
        for j = last: -1: last - Allowed_Slots + 1                          % Find the manimum delay
            if(DataSet{i}(2,j) ~= 0)
                if(DataSet{i}(2,j) ~= PrevNode)
                    PrevNode = DataSet{i}(2,j);
                    Cur_Delay = last - j-zero_count;
                end
            else
                zero_count=zero_count+1;
            end
        end
        y(i) = Cur_Delay * 0.577;                                           % Unit delay time per slot in GSM
    end
    plot(x,y);
end