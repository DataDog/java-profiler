---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-16 06:16:40 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1792145516 62
1792145521 62
1792145526 62
1792145531 62
1792145536 62
1792145541 62
1792145546 62
1792145551 62
1792145556 62
1792145561 62
1792145566 62
1792145571 62
1792145576 62
1792145581 62
1792145586 60
1792145591 60
1792145596 60
1792145601 60
1792145606 60
1792145611 60
```
</details>

---

