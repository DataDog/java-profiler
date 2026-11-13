---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 07:45:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 12 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 71-91 cores)</summary>

```
1794573565 73
1794573570 73
1794573575 73
1794573580 73
1794573585 73
1794573590 73
1794573595 73
1794573600 73
1794573605 73
1794573610 71
1794573615 71
1794573620 71
1794573625 71
1794573630 71
1794573635 71
1794573640 71
1794573645 71
1794573650 71
1794573655 71
1794573660 91
```
</details>

---

