---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:42:59 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 77-85 cores)</summary>

```
1778582334 77
1778582339 77
1778582344 77
1778582349 77
1778582354 80
1778582359 80
1778582364 80
1778582369 85
1778582374 85
1778582379 85
1778582384 85
1778582389 85
1778582394 85
1778582399 85
1778582404 85
1778582409 85
1778582414 85
1778582419 85
1778582424 85
1778582429 85
```
</details>

---

