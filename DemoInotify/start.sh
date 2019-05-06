#!/bin/bash
echo "$1-$2"
result=$(ps aux | grep -i "start.sh" | grep -v "grep" | wc -l)
Ruta=$1 #c9.io

if [ $result -eq 1 ] & [ $result -eq 2 ]
then
	echo "Arrancando el demonio.."
	cd $1
	$(./copy "$2" &)
else
	if [ $result -gt 1 ]
	then
		echo "Ya se está ejecutando el demonio.. finalice la ejecución y vuelva a empezar."
	fi
fi
exit 0
