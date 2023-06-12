#!/bin/bash

TESTS=$(find -wholename "*.test")
FAILED=""
SUCCESS=""

for test_file in $TESTS ; do
    python3 test/test.py $1 $test_file
    if [ $? != 0 ]; then
        FAILED="$FAILED $test_file"
    else
        SUCCESS="$SUCCESS $test_file"
    fi
done

F_COUNT=$(echo "$FAILED" | wc -w)
S_COUNT=$(echo "$SUCCESS" | wc -w)

printf "%d successful tests, %d failed tests\n" $S_COUNT $F_COUNT

if [ "$FAILED" != "" ]; then
    exit 1
fi
