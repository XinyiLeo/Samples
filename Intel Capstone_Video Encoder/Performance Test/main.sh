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

thread=1
if [ $4 ] 
then
thread=$4
fi

outputFileName=${Commandname}".log"
pidFileName="pidCollection.log"

if test -s ${outputFileName};
then
	rm ${outputFileName}
fi

if test -s ${pidFileName};
then
	rm ${pidFileName}
fi

for ((i=1; i<=${thread}; i++))do
{
./FPS.sh ${commandName} "${flag}" $i>> FPS$i.out &
}
done


ps -cux|grep ${commandName} > tempnothing.out
while test -s tempnothing.out
	do
	ps -cux|grep ${commandName} >> ${outputFileName}
	ps -cux|grep ${commandName} > tempnothing.out
	sleep ${interval}s
done
wait

cat ${outputFileName} > Process.log
if test -s ${outputFileName};
then
	for ((i=1; i<=${thread}; i++))do
	{
		grep "$i:" ${pidFileName} | awk -F ' ' '{print $2;}' > PID$i.out
		pid=`cat PID$i.out`
		pid=$(( $pid + $thread - 1 ))
		./CPU.sh ${commandName} ${outputFileName} ${pid} >> CPU$i.out
		./MEM.sh ${commandName} ${outputFileName} ${pid} >> MEM$i.out
	}
	done
else
	echo "ERROR: "${1}" is not running."
fi

for ((i=1; i<=${thread}; i++))do
{
	echo "Thread $i"
	cat CPU$i.out MEM$i.out FPS$i.out
	rm CPU$i.out MEM$i.out FPS$i.out PID$i.out
}
done
rm tempnothing.out
rm ${outputFileName}
#time
#usr/bin/time