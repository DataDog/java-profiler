---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:18:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 56-88 cores)</summary>

```
1786972376 88
1786972381 88
1786972386 88
1786972391 56
1786972396 56
1786972401 56
1786972406 56
1786972411 56
1786972416 56
1786972421 56
1786972426 56
1786972431 56
1786972436 56
1786972441 56
1786972446 56
1786972452 56
1786972457 56
1786972462 56
1786972467 56
1786972472 56
```
</details>

---

