---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:22:20 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 86-90 cores)</summary>

```
1794582919 86
1794582924 86
1794582929 86
1794582934 86
1794582939 88
1794582944 88
1794582949 88
1794582954 86
1794582959 86
1794582964 86
1794582969 86
1794582974 86
1794582979 86
1794582984 86
1794582989 88
1794582994 88
1794582999 90
1794583004 90
1794583009 90
1794583014 90
```
</details>

---

