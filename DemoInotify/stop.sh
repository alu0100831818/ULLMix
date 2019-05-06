#!/bin/bash

result=`ps aux | grep -i "start.sh" | grep -v "grep" | wc -l`
if [ $result -ge 1 ]
   then
        echo "Finalizando el demonio"
        del=`ps axf | grep "copy" | grep -v grep | awk '{print "kill -9 " $1}' | sh`
        $del
        
        del=`ps axf | grep "start.sh" | grep -v grep | awk '{print "kill -9 " $1}' | sh`
        $del
        
        #del=`ps axf | grep "midemo.sh" | grep -v grep | awk '{print "kill -9 " $1}' | sh`
        #$del
        
        
	sleep 5
   else 
        echo "El demonio no esta en ejecucion, inicielo."
fi 
