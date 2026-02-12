#!/bin/bash
# Copyright 2026, Datadog, Inc
#
# Run tests in Docker with various OS/libc/JDK combinations (similar to CI)
# Uses two-level Docker image caching:
#   1. Base image with OS + build tools (java-profiler-base:<libc>-<arch>)
#   2. JDK-specific image on top (java-profiler-test:<libc>-jdk<version>-<arch>)
#
# Usage: ./utils/run-docker-tests.sh [options]
#   --libc=glibc|musl        (default: glibc)
#   --jdk=8|11|17|21|25|8-j9|11-j9|17-j9|21-j9  (default: 21)
#   --arch=x64|aarch64       (default: auto-detect)
#   --config=debug|release|asan|tsan   (default: debug)
#   --tests="TestPattern"    (optional, specific test to run)
#   --gtest                  (enable C++ gtests, disabled by default)
#   --shell                  (drop to shell instead of running tests)
#   --mount                  (mount local repo instead of cloning - faster but may have stale artifacts)
#   --rebuild                (force rebuild of Docker images)
#   --rebuild-base           (force rebuild of base image only)
#   --help                   (show this help)

set -e

# Defaults
LIBC="glibc"
JDK_VERSION="21"
ARCH=""
CONFIG="debug"
TESTS=""
SHELL_MODE=false
MOUNT_MODE=false
GTEST_ENABLED=false
REBUILD=false
REBUILD_BASE=false
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BASE_IMAGE_PREFIX="java-profiler-base"
IMAGE_PREFIX="java-profiler-test"

# Auto-detect architecture
detect_arch() {
    local machine
    machine=$(uname -m)
    case "$machine" in
        x86_64|amd64)
            echo "x64"
            ;;
        aarch64|arm64)
            echo "aarch64"
            ;;
        *)
            echo "x64"  # default fallback
            ;;
    esac
}

# JDK Download URLs (Bellsoft Liberica for musl)
get_musl_jdk_url() {
    local version=$1
    local arch=$2

    case "$version-$arch" in
        8-x64)      echo "https://download.bell-sw.com/java/8u462+11/bellsoft-jdk8u462+11-linux-x64-musl-lite.tar.gz" ;;
        8-aarch64)  echo "https://download.bell-sw.com/java/8u462+11/bellsoft-jdk8u462+11-linux-aarch64-musl-lite.tar.gz" ;;
        11-x64)     echo "https://download.bell-sw.com/java/11.0.28+12/bellsoft-jdk11.0.28+12-linux-x64-musl-lite.tar.gz" ;;
        11-aarch64) echo "https://download.bell-sw.com/java/11.0.28+12/bellsoft-jdk11.0.28+12-linux-aarch64-musl-lite.tar.gz" ;;
        17-x64)     echo "https://download.bell-sw.com/java/17.0.16+12/bellsoft-jdk17.0.16+12-linux-x64-musl-lite.tar.gz" ;;
        17-aarch64) echo "https://download.bell-sw.com/java/17.0.16+12/bellsoft-jdk17.0.16+12-linux-aarch64-musl-lite.tar.gz" ;;
        21-x64)     echo "https://download.bell-sw.com/java/21.0.8+12/bellsoft-jdk21.0.8+12-linux-x64-musl-lite.tar.gz" ;;
        21-aarch64) echo "https://download.bell-sw.com/java/21.0.8+12/bellsoft-jdk21.0.8+12-linux-aarch64-musl-lite.tar.gz" ;;
        25-x64)     echo "https://download.bell-sw.com/java/25+37/bellsoft-jdk25+37-linux-x64-musl-lite.tar.gz" ;;
        25-aarch64) echo "https://download.bell-sw.com/java/25+37/bellsoft-jdk25+37-linux-aarch64-musl-lite.tar.gz" ;;
        *)          echo "" ;;
    esac
}

# JDK Download URLs (Eclipse Temurin for glibc)
get_glibc_jdk_url() {
    local version=$1
    local arch=$2

    case "$version-$arch" in
        8-x64)      echo "https://github.com/adoptium/temurin8-binaries/releases/download/jdk8u432-b06/OpenJDK8U-jdk_x64_linux_hotspot_8u432b06.tar.gz" ;;
        8-aarch64)  echo "https://github.com/adoptium/temurin8-binaries/releases/download/jdk8u432-b06/OpenJDK8U-jdk_aarch64_linux_hotspot_8u432b06.tar.gz" ;;
        11-x64)     echo "https://github.com/adoptium/temurin11-binaries/releases/download/jdk-11.0.25%2B9/OpenJDK11U-jdk_x64_linux_hotspot_11.0.25_9.tar.gz" ;;
        11-aarch64) echo "https://github.com/adoptium/temurin11-binaries/releases/download/jdk-11.0.25%2B9/OpenJDK11U-jdk_aarch64_linux_hotspot_11.0.25_9.tar.gz" ;;
        17-x64)     echo "https://github.com/adoptium/temurin17-binaries/releases/download/jdk-17.0.13%2B11/OpenJDK17U-jdk_x64_linux_hotspot_17.0.13_11.tar.gz" ;;
        17-aarch64) echo "https://github.com/adoptium/temurin17-binaries/releases/download/jdk-17.0.13%2B11/OpenJDK17U-jdk_aarch64_linux_hotspot_17.0.13_11.tar.gz" ;;
        21-x64)     echo "https://github.com/adoptium/temurin21-binaries/releases/download/jdk-21.0.5%2B11/OpenJDK21U-jdk_x64_linux_hotspot_21.0.5_11.tar.gz" ;;
        21-aarch64) echo "https://github.com/adoptium/temurin21-binaries/releases/download/jdk-21.0.5%2B11/OpenJDK21U-jdk_aarch64_linux_hotspot_21.0.5_11.tar.gz" ;;
        25-x64)     echo "https://github.com/adoptium/temurin25-binaries/releases/download/jdk-25%2B3-ea-beta/OpenJDK25U-jdk_x64_linux_hotspot_25_3-ea.tar.gz" ;;
        25-aarch64) echo "https://github.com/adoptium/temurin25-binaries/releases/download/jdk-25%2B3-ea-beta/OpenJDK25U-jdk_aarch64_linux_hotspot_25_3-ea.tar.gz" ;;
        *)          echo "" ;;
    esac
}

# JDK Download URLs (IBM Semeru OpenJ9)
get_j9_jdk_url() {
    local version=$1
    local arch=$2

    case "$version-$arch" in
        8-x64)      echo "https://github.com/ibmruntimes/semeru8-binaries/releases/download/jdk8u482-b08_openj9-0.57.0/ibm-semeru-open-jdk_x64_linux_8u482b08_openj9-0.57.0.tar.gz" ;;
        8-aarch64)  echo "https://github.com/ibmruntimes/semeru8-binaries/releases/download/jdk8u482-b08_openj9-0.57.0/ibm-semeru-open-jdk_aarch64_linux_8u482b08_openj9-0.57.0.tar.gz" ;;
        11-x64)     echo "https://github.com/ibmruntimes/semeru11-binaries/releases/download/jdk-11.0.30%2B7_openj9-0.57.0/ibm-semeru-open-jdk_x64_linux_11.0.30_7_openj9-0.57.0.tar.gz" ;;
        11-aarch64) echo "https://github.com/ibmruntimes/semeru11-binaries/releases/download/jdk-11.0.30%2B7_openj9-0.57.0/ibm-semeru-open-jdk_aarch64_linux_11.0.30_7_openj9-0.57.0.tar.gz" ;;
        17-x64)     echo "https://github.com/ibmruntimes/semeru17-binaries/releases/download/jdk-17.0.18%2B8_openj9-0.57.0/ibm-semeru-open-jdk_x64_linux_17.0.18_8_openj9-0.57.0.tar.gz" ;;
        17-aarch64) echo "https://github.com/ibmruntimes/semeru17-binaries/releases/download/jdk-17.0.18%2B8_openj9-0.57.0/ibm-semeru-open-jdk_aarch64_linux_17.0.18_8_openj9-0.57.0.tar.gz" ;;
        21-x64)     echo "https://github.com/ibmruntimes/semeru21-binaries/releases/download/jdk-21.0.10%2B7_openj9-0.57.0/ibm-semeru-open-jdk_x64_linux_21.0.9_10_openj9-0.56.0.tar.gz" ;;
        21-aarch64) echo "https://github.com/ibmruntimes/semeru21-binaries/releases/download/jdk-21.0.10%2B7_openj9-0.57.0/ibm-semeru-open-jdk_aarch64_linux_21.0.9_10_openj9-0.56.0.tar.gz" ;;
        *)          echo "" ;;
    esac
}

usage() {
    head -n 19 "$0" | tail -n 16
    exit 0
}

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --libc=*)
            LIBC="${1#*=}"
            shift
            ;;
        --jdk=*)
            JDK_VERSION="${1#*=}"
            shift
            ;;
        --arch=*)
            ARCH="${1#*=}"
            shift
            ;;
        --config=*)
            CONFIG="${1#*=}"
            shift
            ;;
        --tests=*)
            TESTS="${1#*=}"
            shift
            ;;
        --shell)
            SHELL_MODE=true
            shift
            ;;
        --mount)
            MOUNT_MODE=true
            shift
            ;;
        --gtest)
            GTEST_ENABLED=true
            shift
            ;;
        --rebuild)
            REBUILD=true
            shift
            ;;
        --rebuild-base)
            REBUILD_BASE=true
            shift
            ;;
        --help|-h)
            usage
            ;;
        *)
            echo "Unknown option: $1"
            usage
            ;;
    esac
done

# Auto-detect architecture if not specified
if [[ -z "$ARCH" ]]; then
    ARCH=$(detect_arch)
fi

# Validate arguments
if [[ "$LIBC" != "musl" && "$LIBC" != "glibc" ]]; then
    echo "Error: --libc must be 'musl' or 'glibc'"
    exit 1
fi

if [[ "$ARCH" != "x64" && "$ARCH" != "aarch64" ]]; then
    echo "Error: --arch must be 'x64' or 'aarch64'"
    exit 1
fi

if [[ "$CONFIG" != "debug" && "$CONFIG" != "release" && "$CONFIG" != "asan" && "$CONFIG" != "tsan" ]]; then
    echo "Error: --config must be 'debug', 'release', 'asan', or 'tsan'"
    exit 1
fi

# Parse JDK version and variant (e.g., "21-j9" -> version="21", variant="j9")
JDK_BASE_VERSION="${JDK_VERSION%%-*}"
JDK_VARIANT="${JDK_VERSION#*-}"
if [[ "$JDK_VARIANT" == "$JDK_VERSION" ]]; then
    JDK_VARIANT=""  # No variant specified
fi

# Get JDK URL based on variant and libc
if [[ "$JDK_VARIANT" == "j9" ]]; then
    if [[ "$LIBC" == "musl" ]]; then
        echo "Error: J9/OpenJ9 is not available for musl libc"
        exit 1
    fi
    JDK_URL=$(get_j9_jdk_url "$JDK_BASE_VERSION" "$ARCH")
elif [[ "$LIBC" == "musl" ]]; then
    JDK_URL=$(get_musl_jdk_url "$JDK_BASE_VERSION" "$ARCH")
else
    JDK_URL=$(get_glibc_jdk_url "$JDK_BASE_VERSION" "$ARCH")
fi

if [[ -z "$JDK_URL" ]]; then
    echo "Error: --jdk must be one of: 8, 11, 17, 21, 25, 8-j9, 11-j9, 17-j9, 21-j9"
    exit 1
fi

# Image names for caching
BASE_IMAGE_NAME="${BASE_IMAGE_PREFIX}:${LIBC}-${ARCH}"
IMAGE_NAME="${IMAGE_PREFIX}:${LIBC}-jdk${JDK_VERSION}-${ARCH}"

# Docker platform for cross-architecture support
DOCKER_PLATFORM=""
if [[ "$ARCH" == "aarch64" ]]; then
    DOCKER_PLATFORM="--platform linux/arm64"
elif [[ "$ARCH" == "x64" ]]; then
    DOCKER_PLATFORM="--platform linux/amd64"
fi

echo "=== Docker Test Runner ==="
echo "LIBC:       $LIBC"
echo "Build JDK:  21 (Gradle 9 requirement)"
echo "Test JDK:   $JDK_VERSION"
echo "Arch:       $ARCH"
echo "Config:     $CONFIG"
echo "Tests:      ${TESTS:-<all>}"
echo "GTest:      $(if $GTEST_ENABLED; then echo 'enabled'; else echo 'disabled'; fi)"
echo "Mode:       $(if $SHELL_MODE; then echo 'shell'; else echo 'test'; fi)"
echo "Source:     $(if $MOUNT_MODE; then echo 'mount (local)'; else echo 'clone (clean)'; fi)"
echo "Base Image: $BASE_IMAGE_NAME"
echo "Image:      $IMAGE_NAME"
echo "=========================="

# Create temporary Dockerfile directory
DOCKERFILE_DIR=$(mktemp -d)
trap "rm -rf $DOCKERFILE_DIR" EXIT

# Copy gradle wrapper for caching
cp "$PROJECT_ROOT/gradlew" "$DOCKERFILE_DIR/"
cp -r "$PROJECT_ROOT/gradle" "$DOCKERFILE_DIR/"

# ========== Build Base Image (if needed) ==========
BASE_IMAGE_EXISTS=false
if [[ "$REBUILD" == "false" && "$REBUILD_BASE" == "false" ]]; then
    if docker image inspect "$BASE_IMAGE_NAME" >/dev/null 2>&1; then
        BASE_IMAGE_EXISTS=true
        echo ">>> Using cached base image: $BASE_IMAGE_NAME"
    fi
fi

if [[ "$BASE_IMAGE_EXISTS" == "false" ]]; then
    echo ">>> Building base image: $BASE_IMAGE_NAME"

    if [[ "$LIBC" == "musl" ]]; then
        cat > "$DOCKERFILE_DIR/Dockerfile.base" <<'EOF'
FROM alpine:3.21

# Install build dependencies
# - linux-headers provides linux/limits.h
# - compiler-rt provides sanitizer runtimes (ASan, TSan) for clang
# - llvm provides libFuzzer
# - openssh-client for git clone over SSH
RUN apk update && \
    apk add --no-cache \
        curl wget bash make g++ clang git jq cmake coreutils \
        gtest-dev gmock tar binutils musl-dbg linux-headers \
        compiler-rt llvm openssh-client

# Set up Gradle cache directory
ENV GRADLE_USER_HOME=/gradle-cache
RUN mkdir -p /gradle-cache

WORKDIR /workspace
EOF
    else
        cat > "$DOCKERFILE_DIR/Dockerfile.base" <<'EOF'
FROM ubuntu:22.04

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
# - libasan/libtsan for GCC sanitizers
# - clang provides sanitizer runtimes and libFuzzer
# - openssh-client for git clone over SSH
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        curl wget bash make g++ clang git jq cmake \
        libgtest-dev libgmock-dev tar binutils libc6-dbg \
        ca-certificates linux-libc-dev \
        libasan6 libtsan0 openssh-client && \
    rm -rf /var/lib/apt/lists/*

# Set up Gradle cache directory
ENV GRADLE_USER_HOME=/gradle-cache
RUN mkdir -p /gradle-cache

WORKDIR /workspace
EOF
    fi

    docker build $DOCKER_PLATFORM -t "$BASE_IMAGE_NAME" -f "$DOCKERFILE_DIR/Dockerfile.base" "$DOCKERFILE_DIR"
    echo ">>> Base image built: $BASE_IMAGE_NAME"
fi

# ========== Get Build JDK URL (always JDK 21 for Gradle 9) ==========
# Gradle 9 requires JDK 17+ to run; we use JDK 21 (LTS) as the build JDK
BUILD_JDK_VERSION="21"
if [[ "$LIBC" == "musl" ]]; then
    BUILD_JDK_URL=$(get_musl_jdk_url "$BUILD_JDK_VERSION" "$ARCH")
else
    BUILD_JDK_URL=$(get_glibc_jdk_url "$BUILD_JDK_VERSION" "$ARCH")
fi

# ========== Build JDK Image (if needed) ==========
IMAGE_EXISTS=false
if [[ "$REBUILD" == "false" ]]; then
    if docker image inspect "$IMAGE_NAME" >/dev/null 2>&1; then
        IMAGE_EXISTS=true
        echo ">>> Using cached image: $IMAGE_NAME"
    fi
fi

if [[ "$IMAGE_EXISTS" == "false" ]]; then
    echo ">>> Building JDK image: $IMAGE_NAME"
    echo ">>> Build JDK (for Gradle): $BUILD_JDK_VERSION"
    echo ">>> Test JDK: $JDK_VERSION"

    # Determine if we need two JDKs or just one
    if [[ "$JDK_BASE_VERSION" == "$BUILD_JDK_VERSION" && -z "$JDK_VARIANT" ]]; then
        # Test JDK is same as build JDK - use single installation
        cat > "$DOCKERFILE_DIR/Dockerfile" <<EOF
FROM $BASE_IMAGE_NAME

# Download and install JDK (used for both build and test)
RUN mkdir -p /jdk && \\
    wget -q "$JDK_URL" -O /tmp/jdk.tar.gz && \\
    tar xzf /tmp/jdk.tar.gz -C /jdk --strip-components=1 && \\
    rm /tmp/jdk.tar.gz

# Set JDK environment (same JDK for build and test)
ENV JAVA_HOME=/jdk
ENV JAVA_TEST_HOME=/jdk
ENV PATH="/jdk/bin:\$PATH"

# Verify JDK installation
RUN java -version

# Pre-cache Gradle wrapper
COPY gradlew /tmp/gradle-setup/
COPY gradle /tmp/gradle-setup/gradle
RUN cd /tmp/gradle-setup && \\
    chmod +x gradlew && \\
    ./gradlew --version && \\
    rm -rf /tmp/gradle-setup

WORKDIR /workspace
EOF
    else
        # Different JDKs for build and test
        cat > "$DOCKERFILE_DIR/Dockerfile" <<EOF
FROM $BASE_IMAGE_NAME

# Download and install Build JDK (JDK $BUILD_JDK_VERSION for Gradle 9)
RUN mkdir -p /jdk-build && \\
    wget -q "$BUILD_JDK_URL" -O /tmp/jdk-build.tar.gz && \\
    tar xzf /tmp/jdk-build.tar.gz -C /jdk-build --strip-components=1 && \\
    rm /tmp/jdk-build.tar.gz

# Download and install Test JDK (JDK $JDK_VERSION)
RUN mkdir -p /jdk-test && \\
    wget -q "$JDK_URL" -O /tmp/jdk-test.tar.gz && \\
    tar xzf /tmp/jdk-test.tar.gz -C /jdk-test --strip-components=1 && \\
    rm /tmp/jdk-test.tar.gz

# Set JDK environment
# JAVA_HOME = Build JDK (for running Gradle)
# JAVA_TEST_HOME = Test JDK (for running tests)
ENV JAVA_HOME=/jdk-build
ENV JAVA_TEST_HOME=/jdk-test
ENV PATH="/jdk-build/bin:\$PATH"

# Verify JDK installations
RUN echo "Build JDK:" && java -version
RUN echo "Test JDK:" && /jdk-test/bin/java -version

# Pre-cache Gradle wrapper
COPY gradlew /tmp/gradle-setup/
COPY gradle /tmp/gradle-setup/gradle
RUN cd /tmp/gradle-setup && \\
    chmod +x gradlew && \\
    ./gradlew --version && \\
    rm -rf /tmp/gradle-setup

WORKDIR /workspace
EOF
    fi

    docker build $DOCKER_PLATFORM -t "$IMAGE_NAME" -f "$DOCKERFILE_DIR/Dockerfile" "$DOCKERFILE_DIR"
    echo ">>> JDK image built: $IMAGE_NAME"
fi

# ========== Run Tests ==========

# Build gradle test command
# Note: Use -Ptests (not --tests) because config-specific tasks use Exec, not Test
GRADLE_CMD="./gradlew -PCI -PkeepJFRs :ddprof-test:test${CONFIG}"
if [[ -n "$TESTS" ]]; then
    GRADLE_CMD="$GRADLE_CMD -Ptests=\"$TESTS\""
fi
if ! $GTEST_ENABLED; then
    GRADLE_CMD="$GRADLE_CMD -Pskip-gtest"
fi
GRADLE_CMD="$GRADLE_CMD --no-daemon --parallel --build-cache --no-watch-fs"

# Build Docker run command base
DOCKER_CMD="docker run --rm"
if $SHELL_MODE; then
    DOCKER_CMD="$DOCKER_CMD -it"
fi
DOCKER_CMD="$DOCKER_CMD $DOCKER_PLATFORM"
DOCKER_CMD="$DOCKER_CMD -e LIBC=$LIBC"
DOCKER_CMD="$DOCKER_CMD -e SANITIZER=$CONFIG"
DOCKER_CMD="$DOCKER_CMD -e TEST_CONFIGURATION=$LIBC/${JDK_VERSION}-$CONFIG-$ARCH"
DOCKER_CMD="$DOCKER_CMD -e GRADLE_USER_HOME=/gradle-cache"

if $MOUNT_MODE; then
    # Mount mode: use local repo directly (faster, but may have stale artifacts)
    DOCKER_CMD="$DOCKER_CMD -v \"$PROJECT_ROOT\":/workspace"
    DOCKER_CMD="$DOCKER_CMD $IMAGE_NAME"

    if $SHELL_MODE; then
        CONTAINER_CMD="/bin/bash"
    else
        CONTAINER_CMD="$GRADLE_CMD"
    fi

    echo ""
    echo ">>> Running in container (mount mode)..."
    echo ">>> Command: $CONTAINER_CMD"
    eval "$DOCKER_CMD /bin/bash -c '$CONTAINER_CMD'"
else
    # Clone mode: shallow clone from mounted local repo for clean builds (default)
    # Mount the local repo as source, then clone from it to /workspace
    DOCKER_CMD="$DOCKER_CMD -v \"$PROJECT_ROOT\":/source:ro"
    DOCKER_CMD="$DOCKER_CMD $IMAGE_NAME"

    # Build clone and test command - clone from local mounted source
    if $SHELL_MODE; then
        CLONE_CMD="git clone --depth 1 file:///source /workspace && cd /workspace && /bin/bash"
    else
        CLONE_CMD="git clone --depth 1 file:///source /workspace && cd /workspace && $GRADLE_CMD"
    fi

    echo ""
    echo ">>> Running in container (clone mode)..."
    echo ">>> Cloning from local source to /workspace"
    eval "$DOCKER_CMD /bin/bash -c '$CLONE_CMD'"
fi
