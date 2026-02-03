---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 09:59:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 10 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (5 unique values: 56-75 cores)</summary>

```
1770130599 62
1770130604 62
1770130609 62
1770130614 62
1770130619 62
1770130624 62
1770130629 62
1770130634 56
1770130639 56
1770130644 56
1770130649 56
1770130654 56
1770130659 56
1770130664 58
1770130669 58
1770130674 58
1770130679 61
1770130684 61
1770130689 61
1770130694 61
```
</details>

---

