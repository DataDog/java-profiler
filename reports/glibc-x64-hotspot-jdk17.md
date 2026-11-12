---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 05:21:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 67-88 cores)</summary>

```
1794478548 69
1794478553 67
1794478558 67
1794478563 67
1794478568 69
1794478573 69
1794478578 69
1794478583 69
1794478588 69
1794478593 69
1794478598 69
1794478603 69
1794478608 69
1794478613 69
1794478618 71
1794478623 71
1794478628 88
1794478633 88
1794478638 88
1794478643 88
```
</details>

---

