---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 09:03:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 8 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 27-87 cores)</summary>

```
1795442324 76
1795442329 76
1795442334 76
1795442339 85
1795442344 85
1795442349 85
1795442354 85
1795442359 85
1795442364 85
1795442369 85
1795442374 85
1795442379 87
1795442384 87
1795442389 87
1795442394 87
1795442399 87
1795442405 87
1795442410 87
1795442415 87
1795442420 87
```
</details>

---

