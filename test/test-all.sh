#!/bin/bash

set -e

for TEST in $(find . -name '*-test.sh'); do
    echo "=== $TEST"
    bash $TEST
done

echo "All tests passed"