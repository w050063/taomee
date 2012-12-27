#!/bin/bash
cd $(dirname $0 ) 
echo "ser shell exec ..."
if [ "$1" = "stop" ] ; then
#	ps -ef |grep ./ser | awk '{print "kill -15 " $2}'|sh
	ps -ef |grep "\<popdb\>" | awk '{print "kill -9 " $2}'|sh
elif [ "$1" = "restart" ]; then
	ps -ef |grep "\<popdb\>" | awk '{print "kill -9 " $2}'|sh
	./popdb ../conf/bench.conf ./libdb.so 
elif [ "$1" = "start" ]; then
#	 valgrind --leak-check=full ./popdb ../conf/bench.conf ./libtest.so -s 4096
	./popdb ../conf/bench.conf ./libdb.so 
elif [ "$1" = "--help" ] || [ "$1" = "-h" ]; then
	echo "daemon.sh start|stop|restart"
fi
ls ./popdb ../conf/bench.conf ./libdb.so
