#!/bin/bash

status=0
LOCAL_TEST_DIR=`pwd`
cmsRun -e -p ${LOCAL_TEST_DIR}/fpe_test.cfg

exit $status
