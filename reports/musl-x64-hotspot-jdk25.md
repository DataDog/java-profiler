---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 08:56:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 78-91 cores)</summary>

```
1794318777 78
1794318782 78
1794318787 78
1794318792 80
1794318797 80
1794318802 89
1794318807 89
1794318812 89
1794318817 89
1794318822 89
1794318827 89
1794318832 89
1794318837 89
1794318842 89
1794318847 89
1794318852 89
1794318857 89
1794318862 89
1794318867 89
1794318872 89
```
</details>

---

