---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 11:08:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 10 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (5 unique values: 78-93 cores)</summary>

```
1794931427 78
1794931432 78
1794931437 78
1794931442 78
1794931447 78
1794931452 78
1794931457 78
1794931462 78
1794931467 78
1794931472 80
1794931477 80
1794931482 80
1794931487 80
1794931492 85
1794931497 85
1794931502 85
1794931507 91
1794931512 91
1794931517 91
1794931522 91
```
</details>

---

