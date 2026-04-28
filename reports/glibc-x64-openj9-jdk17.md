---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-28 12:10:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (7 unique values: 71-82 cores)</summary>

```
1777392264 81
1777392269 80
1777392274 80
1777392279 80
1777392284 82
1777392289 82
1777392294 82
1777392299 82
1777392304 82
1777392309 82
1777392314 82
1777392319 82
1777392324 82
1777392329 82
1777392334 82
1777392339 82
1777392344 78
1777392349 78
1777392354 77
1777392359 77
```
</details>

---

