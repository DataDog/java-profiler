#!/bin/bash

set -euo pipefail

# install-prerequisites.sh - Set up prerequisites for integration tests
#
# This script installs and configures:
# - jbang (for jfr-shell)
# - Basic development tools
# - Creates output directories

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

function log_info() {
  echo -e "${GREEN}[INFO]${NC} $*"
}

function log_warn() {
  echo -e "${YELLOW}[WARN]${NC} $*"
}

log_info "Installing prerequisites for integration tests..."

# Retry configuration
MAX_RETRIES=3
RETRY_DELAY=5

# ========================================
# 1. Install jbang (if not present)
# ========================================
if ! command -v jbang &> /dev/null; then
    log_info "Installing jbang..."

    # Download and install jbang with retry logic
    for attempt in $(seq 1 $MAX_RETRIES); do
        log_info "jbang installation attempt $attempt of $MAX_RETRIES..."
        if curl -Ls https://sh.jbang.dev | bash -s - app setup; then
            break
        fi
        if [ "$attempt" -lt $MAX_RETRIES ]; then
            log_warn "jbang installation failed, retrying in ${RETRY_DELAY}s..."
            sleep $RETRY_DELAY
            RETRY_DELAY=$((RETRY_DELAY * 2))
        else
            log_warn "jbang installation failed after $MAX_RETRIES attempts"
        fi
    done

    # Add to PATH for current session
    export PATH="$HOME/.jbang/bin:$PATH"

    # Verify installation
    if command -v jbang &> /dev/null; then
        JBANG_VERSION=$(jbang version 2>&1 | head -1)
        log_info "jbang installed successfully: ${JBANG_VERSION}"
    else
        log_warn "jbang installation completed but not found in PATH"
        log_warn "Please ensure ~/.jbang/bin is in your PATH"
    fi
else
    JBANG_VERSION=$(jbang version 2>&1 | head -1)
    log_info "jbang already installed: ${JBANG_VERSION}"
fi

# Add jbang trust for jfr-shell from btraceio
log_info "Adding jbang trust for btraceio catalog..."
jbang trust add https://github.com/btraceio/ 2>/dev/null || true

# Pre-install JDK 25 for jbang (required by jfr-shell)
# First check if JDK 25 is already available (e.g., Java 25 test jobs)
log_info "Checking if JDK 25 is available for jbang..."
if jbang jdk list 2>&1 | grep -q "25"; then
    log_info "JDK 25 already available for jbang"
    JDK25_INSTALLED=true
else
    log_info "Pre-installing JDK 25 for jbang (required by jfr-shell)..."
    JDK25_INSTALLED=false

    # Try jbang's built-in install first
    for attempt in $(seq 1 $MAX_RETRIES); do
        log_info "JDK 25 installation attempt $attempt of $MAX_RETRIES (via jbang)..."
        if jbang jdk install 25 2>&1; then
            JDK25_INSTALLED=true
            log_info "JDK 25 installed for jbang"
            break
        fi
        if [ "$attempt" -lt $MAX_RETRIES ]; then
            log_warn "JDK 25 installation failed, retrying in ${RETRY_DELAY}s..."
            sleep $RETRY_DELAY
        fi
    done

    # Fallback: manually download from Adoptium if jbang failed (Foojay API down)
    if [ "$JDK25_INSTALLED" = "false" ]; then
        log_warn "jbang install failed (Foojay API may be down), trying direct Adoptium download..."

        # Detect architecture
        ARCH=$(uname -m)
        case "$ARCH" in
            x86_64|amd64) ADOPTIUM_ARCH="x64" ;;
            aarch64|arm64) ADOPTIUM_ARCH="aarch64" ;;
            *) log_warn "Unknown arch: $ARCH"; ADOPTIUM_ARCH="x64" ;;
        esac

        # Detect OS and libc
        if [ -f /etc/alpine-release ]; then
            ADOPTIUM_OS="alpine-linux"
        else
            ADOPTIUM_OS="linux"
        fi

        JBANG_JDK_DIR="$HOME/.jbang/cache/jdks/25"
        ADOPTIUM_URL="https://api.adoptium.net/v3/binary/latest/25/ga/${ADOPTIUM_OS}/${ADOPTIUM_ARCH}/jdk/hotspot/normal/eclipse"

        log_info "Downloading JDK 25 from Adoptium: $ADOPTIUM_URL"
        if curl -fsSL -o /tmp/jdk25.tar.gz "$ADOPTIUM_URL"; then
            mkdir -p "$JBANG_JDK_DIR"
            tar -xzf /tmp/jdk25.tar.gz -C "$JBANG_JDK_DIR" --strip-components=1
            rm -f /tmp/jdk25.tar.gz

            if [ -x "$JBANG_JDK_DIR/bin/java" ]; then
                JDK25_INSTALLED=true
                log_info "JDK 25 installed manually from Adoptium"
                "$JBANG_JDK_DIR/bin/java" -version 2>&1 | head -1
            else
                log_warn "JDK 25 extraction failed"
            fi
        else
            log_warn "Failed to download JDK 25 from Adoptium"
        fi
    fi
fi

if [ "$JDK25_INSTALLED" = "false" ]; then
    log_warn "Failed to install JDK 25 for jbang"
    log_warn "JFR validation will be skipped"
    echo "JDK 25 not available for jbang (Foojay API may be down)" > /tmp/skip-jfr-validation
fi

# ========================================
# Pre-warm jfr-shell backend
# ========================================
# jafar-shell resolves its backend plugin (io.btrace:jfr-shell-jafar) from Maven at
# runtime. If that artifact is unavailable (network restriction, version not yet
# published), every validation run fails. Detect this early so we can skip gracefully.
if [ ! -f /tmp/skip-jfr-validation ] && command -v jbang &> /dev/null; then
    log_info "Pre-warming jfr-shell backend..."
    PREWARM_OUT=$(jbang --java 25 jfr-shell@btraceio script /dev/null 2>&1 || true)
    if echo "$PREWARM_OUT" | grep -q "No backends found\|No JFR backends available\|Failed to resolve artifact.*jfr-shell-jafar"; then
        log_warn "jfr-shell backend unavailable (io.btrace:jfr-shell-jafar not resolvable from Maven)"
        log_warn "JFR validation will be skipped"
        echo "jfr-shell backend unavailable (io.btrace:jfr-shell-jafar not resolvable from Maven)" > /tmp/skip-jfr-validation
    else
        log_info "jfr-shell backend ready"
    fi
fi

# ========================================
# 2. Verify Java is available
# ========================================
if [ -z "${JAVA_HOME:-}" ]; then
    if command -v java &> /dev/null; then
        log_info "Java found in PATH"
        java -version 2>&1 | head -3
    else
        echo "ERROR: Java not found. Please set JAVA_HOME or ensure java is in PATH"
        exit 1
    fi
else
    if [ ! -x "${JAVA_HOME}/bin/java" ]; then
        echo "ERROR: Java not found at: ${JAVA_HOME}/bin/java"
        exit 1
    fi

    log_info "Java found at JAVA_HOME: ${JAVA_HOME}"
    "${JAVA_HOME}/bin/java" -version 2>&1 | head -3
fi

# ========================================
# 3. Install basic tools (if needed)
# ========================================
# Check for javac (needed to compile test app)
if [ -n "${JAVA_HOME:-}" ]; then
    if [ ! -x "${JAVA_HOME}/bin/javac" ]; then
        log_warn "javac not found at ${JAVA_HOME}/bin/javac"
        log_warn "This may cause test app compilation to fail"
    fi
elif ! command -v javac &> /dev/null; then
    log_warn "javac not found in PATH"
    log_warn "This may cause test app compilation to fail"
fi

# ========================================
# 4. Create output directories
# ========================================
log_info "Creating output directories..."

mkdir -p integration-test-results
mkdir -p /tmp/jfr-validation

log_info "✓ Prerequisites installation complete"
log_info ""
log_info "Installed tools:"
log_info "  - jbang: $(command -v jbang || echo 'not in PATH')"
log_info "  - jbang JDKs: $(jbang jdk list 2>&1 | grep -v '^$' | tr '\n' ' ')"
log_info "  - java: $(command -v java || echo 'not in PATH')"
log_info "  - javac: $(command -v javac || echo 'not in PATH')"
log_info ""
