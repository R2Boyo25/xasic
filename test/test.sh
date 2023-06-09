#!/bin/bash

set -xe

TESTS=$(find -wholename "*.test")

for test_file in $TESTS ; do
    python3 test/test.py $1 $test_file
done
