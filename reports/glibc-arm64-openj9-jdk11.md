---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-02 05:49:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 267 |
| Sample Rate | 4.45/sec |
| Health Score | 278% |
| Threads | 13 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788342307 48
1788342312 48
1788342317 43
1788342322 43
1788342327 43
1788342332 43
1788342337 43
1788342342 43
1788342347 43
1788342352 43
1788342357 43
1788342363 43
1788342368 43
1788342373 43
1788342378 43
1788342383 43
1788342388 48
1788342393 48
1788342398 48
1788342403 48
```
</details>

---

