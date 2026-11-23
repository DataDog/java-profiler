---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 09:03:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 11 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (3 unique values: 39-41 cores)</summary>

```
1795442324 40
1795442329 40
1795442334 40
1795442339 40
1795442344 40
1795442349 40
1795442354 40
1795442359 40
1795442364 40
1795442369 40
1795442374 40
1795442379 40
1795442384 40
1795442389 40
1795442394 40
1795442399 40
1795442404 40
1795442409 40
1795442414 40
1795442419 41
```
</details>

---

