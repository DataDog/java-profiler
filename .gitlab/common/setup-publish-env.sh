#!/bin/bash

# setup-publish-env.sh - Install dependencies for GitHub Pages publishing
#
# This script auto-detects the package manager and installs required tools

set -euo pipefail

echo "=== Setting up publishing environment ==="
echo "Current user: $(whoami), UID: $(id -u)"
echo "Image: ${CI_JOB_IMAGE:-unknown}"

# Check if Python3 is already available
if command -v python3 >/dev/null 2>&1; then
  echo "Python3 already available: $(python3 --version)"
  echo "Skipping installation"
  exit 0
fi

echo "Python3 not found, attempting installation..."

# Check if we need sudo
SUDO=""
if [ "$(id -u)" -ne 0 ]; then
  if command -v sudo >/dev/null 2>&1; then
    echo "Running as non-root user, will use sudo"
    SUDO="sudo"
  else
    echo "ERROR: Running as non-root but sudo not available"
    echo "Current user: $(whoami), UID: $(id -u)"
    exit 1
  fi
fi

# Detect and use appropriate package manager
if command -v apt-get >/dev/null 2>&1; then
  echo "Detected: apt-get (Debian/Ubuntu)"
  $SUDO apt-get update -qq
  $SUDO apt-get install -y python3 git curl jq
elif command -v apk >/dev/null 2>&1; then
  echo "Detected: apk (Alpine)"
  $SUDO apk add --no-cache python3 git curl jq
elif command -v yum >/dev/null 2>&1; then
  echo "Detected: yum (RHEL/CentOS)"
  $SUDO yum install -y python3 git curl jq
elif command -v dnf >/dev/null 2>&1; then
  echo "Detected: dnf (Fedora/RHEL 8+)"
  $SUDO dnf install -y python3 git curl jq
else
  echo "ERROR: No supported package manager found (tried apt-get, apk, yum, dnf)"
  echo "Available commands:"
  command -v apt-get apk yum dnf 2>&1 || echo "None found"
  exit 1
fi

echo ""
echo "=== Verifying installations ==="
echo -n "Python3: "
python3 --version || (echo "FAILED" && exit 1)

echo -n "Git: "
git --version || echo "WARNING: git not found"

echo -n "curl: "
curl --version | head -1 || echo "WARNING: curl not found"

echo -n "jq: "
jq --version || echo "WARNING: jq not found"

echo -n "dd-octo-sts: "
dd-octo-sts version || echo "WARNING: dd-octo-sts not available or failed to run"

echo ""
echo "=== Environment ready for publishing ==="
