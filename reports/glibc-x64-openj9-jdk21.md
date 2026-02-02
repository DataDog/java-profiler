---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-02 12:03:38 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 8 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 12 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 22-58 cores)</summary>

```
1770051357 22
1770051362 22
1770051367 22
1770051372 22
1770051377 22
1770051382 58
1770051387 58
1770051392 58
1770051397 58
1770051402 58
1770051407 58
1770051412 58
1770051417 58
1770051422 58
1770051427 58
1770051432 58
1770051437 58
1770051442 58
1770051447 58
1770051452 58
```
</details>

---

