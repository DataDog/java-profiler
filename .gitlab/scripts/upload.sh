#!/bin/bash

# Unless explicitly stated otherwise all files in this repository are licensed under the Apache License Version 2.0.
# This product includes software developed at Datadog (https://www.datadoghq.com/). Copyright 2021-Present Datadog, Inc.

# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail
IFS=$'\n\t'

# Load centralized configuration
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
if [ -f "${SCRIPT_DIR}/../../.gitlab/config.env" ]; then
  source "${SCRIPT_DIR}/../../.gitlab/config.env"
fi

# Helper functions
print_help() {
  echo "binary artifact upload tool

  -f
    path to local file
  -n
    what to name the object in S3
  -p
    prefix for key (e.g., jplib/<version>)
  -b
    S3 bucket (default: ${S3_BUCKET:-binaries.ddbuild.io})
  -h
    print this help and exit
"
}

# Parameters
BUCKET="${S3_BUCKET:-binaries.ddbuild.io}"
PRE=""
NAME=""
FILE=""
DRY="no"
CMD="aws s3 cp --region ${AWS_REGION:-us-east-1} --sse AES256 --acl bucket-owner-full-control"

if [ $# -eq 0 ]; then print_help && exit 0; fi
while getopts ":f:n:b:p:dh" arg; do
  case $arg in
    f)
      FILE=${OPTARG}
      ;;
    n)
      NAME=${OPTARG}
      ;;
    b)
      BUCKET=${OPTARG}
      ;;
    p)
      PRE=${OPTARG}
      ;;
    d)
      DRY="yes"
      ;;
    h)
      print_help
      exit 0
      ;;
  esac
done

if [ -z "$NAME" ]; then
  echo "No name (-n) given, error"
  exit -1
fi

if [ -z "$FILE" ]; then
  echo "No file (-f) given, error"
  exit -1
fi

if [ ! -f "$FILE" ]; then
  echo "File ($FILE) does not exist, error"
  exit -1
fi

SHA_FILE="/tmp/$(basename ${FILE}).sha"
sha256sum ${FILE} > ${SHA_FILE}

if [ "yes" == ${DRY} ]; then
  echo ${CMD} ${FILE} s3://${BUCKET}/${PRE}/${NAME}
  echo ${CMD} ${SHA_FILE} s3://${BUCKET}/${PRE}/${NAME}.sha
else
  eval ${CMD} ${FILE} s3://${BUCKET}/${PRE}/${NAME}
  eval ${CMD} ${SHA_FILE} s3://${BUCKET}/${PRE}/${NAME}.sha
fi