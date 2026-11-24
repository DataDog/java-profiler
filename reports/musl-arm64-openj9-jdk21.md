---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 10:24:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 44 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 12 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 42-44 cores)</summary>

```
1795533328 42
1795533333 42
1795533338 42
1795533343 42
1795533348 42
1795533353 42
1795533358 42
1795533363 42
1795533368 42
1795533373 42
1795533378 42
1795533383 42
1795533388 42
1795533393 42
1795533398 42
1795533403 42
1795533408 44
1795533413 44
1795533418 44
1795533423 44
```
</details>

---

