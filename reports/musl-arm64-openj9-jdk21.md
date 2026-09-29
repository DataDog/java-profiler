---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 06:43:05 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 815 |
| Sample Rate | 13.58/sec |
| Health Score | 849% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1790678309 45
1790678314 45
1790678319 40
1790678324 40
1790678329 40
1790678334 40
1790678339 40
1790678344 40
1790678349 40
1790678354 40
1790678359 40
1790678364 40
1790678370 40
1790678375 40
1790678380 40
1790678385 40
1790678390 40
1790678395 40
1790678400 40
1790678405 40
```
</details>

---

