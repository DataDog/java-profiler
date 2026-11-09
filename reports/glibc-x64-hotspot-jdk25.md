---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 12:24:37 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 78-85 cores)</summary>

```
1794244745 83
1794244750 83
1794244755 83
1794244760 83
1794244765 83
1794244770 83
1794244775 83
1794244780 83
1794244785 85
1794244790 85
1794244795 80
1794244800 80
1794244805 80
1794244810 80
1794244815 80
1794244820 80
1794244825 80
1794244830 80
1794244835 80
1794244840 80
```
</details>

---

