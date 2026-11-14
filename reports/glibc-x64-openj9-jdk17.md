---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-14 05:57:11 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 10 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (2 unique values: 55-72 cores)</summary>

```
1794653561 55
1794653566 55
1794653571 55
1794653576 55
1794653581 55
1794653586 55
1794653591 55
1794653596 55
1794653601 72
1794653606 72
1794653611 72
1794653616 72
1794653621 72
1794653626 72
1794653631 72
1794653636 72
1794653641 72
1794653646 72
1794653651 72
1794653656 72
```
</details>

---

