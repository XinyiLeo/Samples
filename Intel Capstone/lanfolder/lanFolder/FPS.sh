#!/bin/bash
#Input Format: ./FPS.sh command flag thread
wholecommand="$1 $2"
${wholecommand} > thread$3.out
r=$(( $$ + 3 ))
echo "$3: $r" >> pidCollection.log
cat thread$3.out| grep -Eo 'fps = [0-9.]*' | grep -Eo '[0-9.]*'
rm thread$3.out
