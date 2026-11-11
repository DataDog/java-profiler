---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 05:46:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794393797 48
1794393802 48
1794393807 48
1794393812 48
1794393817 43
1794393822 43
1794393827 43
1794393832 43
1794393837 43
1794393842 43
1794393847 43
1794393852 43
1794393857 43
1794393862 43
1794393867 43
1794393873 43
1794393878 43
1794393883 48
1794393888 48
1794393893 48
```
</details>

---

