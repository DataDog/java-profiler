#!/usr/bin/env bash

echo "Checking the requested modes [${MODES:=cpu,wall,alloc,memleak}] in [$RUN_MODE] ..."
RESULT="SKIP"
for MODE in ${MODES//,/$IFS}; do
    echo ":: $MODE -< $RUN_MODE"
    if [[ $RUN_MODE =~ .*?$MODE.* ]]; then
        RESULT="CONTINUE"
        break
    fi
done
echo $RESULT > .job_status
if [ "$RESULT" == "SKIP" ]; then
    echo "Skipping run for mode set: [$RUN_MODE]. It does not include any mode from ${MODES}."
fi