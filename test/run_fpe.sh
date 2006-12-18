#!/bin/bash
# If successful this will dump core so disable that... 
ulimit -c 0

# Pass in name and status
# function die { echo $1: status $2 ;  exit $2; }

F1=${LOCAL_TEST_DIR}/fpe_test.cfg

cmsRun $F1 >& /dev/null
status=$?
if [ $status -ne 134 ] ; then
 echo "Failure using $F1"
 exit 1
fi
