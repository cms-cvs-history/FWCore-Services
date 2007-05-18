#!/bin/bash

status=0

cmsRun -e -p ${LOCAL_TEST_DIR}/fpe_test.cfg

exit $status
