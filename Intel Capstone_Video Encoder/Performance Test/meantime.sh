#!/bin/bash
#Input Format: ./bash.sh Inspect_Interval command flag thread
#example: ./bash.sh 0.1 yamitranscode "-i /media/encoderbitstreams/1080p_blue_sky.yuv -s I420 -W 1920 -H 1080 --qp 28 -c AVC -o test.h264" 1
#Attention! if command changes, FPS file may need to be revise.
#Output Format: Taskname: MAX%CPU MIN%CPU AVG%CPU MAX%MEM MIN%MEM AVG%MEM FPS
#Temp File: Taskname.log (Includes all running information about the task.)

interval="0.1"
if [ $1 ]
then
interval=$1
fi

commandName="yamitranscode"
if [ $2 ]
then
commandName=$2
fi

flag="-i /media/encoderbitstreams/1080p_blue_sky.yuv -s I420 -W 1920 -H 1080 --qp 28 -c AVC -o test.h264"
if [ $3 ]
then
flag=$3
fi

thread=4
if [ $4 ]
then
thread=$4
fi

outputFileName=${Commandname}".log"

if test -s ${outputFileName};
then
        rm ${outputFileName}
fi

wholecommand="$commandName $flag"

for ((i=1; i<=${thread}; i++))do
{
        if test -s info$i.out;
        then
                rm info$i.out
        fi
        #/usr/bin/time -v ${wholecommand}
        /usr/bin/time -f"\t %e real,\t%K MEM,\t%P CPU, \t%M Resident MEM" -a -o $i.out ${wholecommand}| grep -Eo 'fps = [0-9.]*' | grep -Eo '[0-9.]*' >> fps$i.out &
        #/usr/bin/time -v -a -o info$i.out ${wholecommand} | grep -Eo 'fps = [0-9.]*' | grep -Eo '[0-9.]*' >> fps$i.out &
}
done
wait

#for ((i=1; i<=${thread}; i++))do
#{
#       grep "Elapsed" info$i.out | grep -Eo ': [0-9:.]*' | grep -Eo '[0-9:.]*' >> time$i.out
#       grep "total size" info$i.out | grep -Eo ': [0-9]*'| grep -Eo '[0-9]*' >> mem$i.out
#        grep "Percent od CPU" info$i.out | grep -Eo ': [0-9]*'| grep -Eo '[0-9]*' >> cpu$i.out
#}
#done

for ((i=1; i<=${thread}; i++))do
{
        echo "Thread $i"
        cat $i.out fps$i.out
        rm $i.out fps$i.out
#       cat fps$i.out time$i.out mem$i.out cpu$i.out
#       cat info$i.out > ${outputFileName}
#       rm fps$i.out time$i.out mem$i.out cpu$i.out info$i.out
}
done

