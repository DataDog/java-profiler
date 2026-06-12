#!/usr/bin/env bash
set -euo pipefail

FUZZ_IMAGE="${FUZZ_IMAGE:-registry.ddbuild.io/java-profiler-fuzz}"
GIT_SHA="${CI_COMMIT_SHORT_SHA:-$(git rev-parse --short HEAD)}"

export FUZZYDOG_AUTH_TOKEN
FUZZYDOG_AUTH_TOKEN=$(vault read -field=token identity/oidc/token/security-fuzzing-platform)

# Build and push the compiled image (all fuzz binaries + fuzzydog)
docker buildx build \
    --target build \
    -f docker/Dockerfile.fuzz \
    --build-arg "FUZZYDOG_VERSION=${FUZZYDOG_VERSION}" \
    -t "${FUZZ_IMAGE}:${GIT_SHA}" \
    --push \
    --metadata-file compiled-metadata.json \
    .

COMPILED_DIGEST=$(jq -r '."containerimage.digest"' compiled-metadata.json)

# Extract binary list via the manifest target
docker buildx build \
    --target manifest \
    -f docker/Dockerfile.fuzz \
    --build-arg "FUZZYDOG_VERSION=${FUZZYDOG_VERSION}" \
    --output "type=local,dest=manifest-out" \
    .

# For each binary: build thin per-binary image, sign, replicate, register
while IFS= read -r binary; do
    [ -z "${binary}" ] && continue
    # Normalize to k8s-safe label: camelCase -> lowercase-hyphenated, prefixed with repo name
    normalized=$(printf '%s' "${binary}" | sed 's/[A-Z]/-&/g' | tr '[:upper:]' '[:lower:]' | sed 's/^-//')
    fuzz_app="java-profiler-${normalized}"
    IMAGE_REF="${FUZZ_IMAGE}:${GIT_SHA}-${normalized}"

    printf 'FROM %s@%s\nENV FUZZ_APP=%s\nENV FUZZ_BUILD_ID=%s\nRUN ln -sf /fuzzer/builds/%s /fuzzer/builds/%s\n' \
        "${FUZZ_IMAGE}" "${COMPILED_DIGEST}" "${fuzz_app}" "${GIT_SHA}" "${binary}" "${GIT_SHA}" \
        | docker buildx build - \
            -t "${IMAGE_REF}" \
            --push \
            --metadata-file "meta-${binary}.json"

    ddsign sign "${IMAGE_REF}" --docker-metadata-file "meta-${binary}.json"
    ddsign replicate --to us1.ddbuild.io \
        "${FUZZ_IMAGE}@$(jq -r '."containerimage.digest"' "meta-${binary}.json")"

    fuzzydog fuzzer create "${fuzz_app}" \
        --image "${IMAGE_REF}" \
        --version "${GIT_SHA}" \
        --type libfuzzer \
        --team profiling \
        --slack-channel profiling-java \
        --repository-url https://github.com/DataDog/java-profiler
done < manifest-out/fuzz_binaries.txt
