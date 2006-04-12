#!/bin/bash

# Pass in name and status
function die { echo $1: status $2 ;  exit $2; }

F1=${LOCAL_TEST_DIR}/fpe_test.cfg

cmsRun $F1 >& /dev/null
status=$?
if [ $status -ne 134 ] ; then
 die "Failure using $F1" $status
fi



