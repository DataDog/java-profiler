---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 10:54:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (7 unique values: 72-87 cores)</summary>

```
1778165309 77
1778165314 72
1778165319 72
1778165324 72
1778165329 72
1778165334 74
1778165339 74
1778165344 76
1778165349 76
1778165354 76
1778165359 85
1778165364 85
1778165369 85
1778165374 87
1778165379 87
1778165384 87
1778165389 87
1778165394 87
1778165399 87
1778165404 87
```
</details>

---

