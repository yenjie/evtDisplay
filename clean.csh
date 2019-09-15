ps ax|grep draw|awk '{print "kill "$1}'|sh
ps ax|grep root|awk '{print "kill "$1}'|sh
