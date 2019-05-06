#!/bin/bash
start="/home/ubuntu/workspace/start.sh "
stop="/home/ubuntu/workspace/stop.sh "



start(){
   file="/home/ubuntu/workspace/Midemo.log"
    if [[ ! -f "$file" ]]
    then
            $( echo date > $file)
    fi

    $1"/start.sh" $1 $2 "&"
    exit 0
    
}
stop(){
    $1"/stop.sh"
    exit 0
    
}
case "$1" in
 start)
        start $2 $3
    ;;
 stop)
        stop
    ;;
  *)
        echo $"parametro incorrecto"
        exit 1
        esac
exit 0
