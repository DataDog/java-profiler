---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 10:05:26 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 890 |
| Sample Rate | 14.83/sec |
| Health Score | 927% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 82-90 cores)</summary>

```
1778507998 85
1778508003 84
1778508008 84
1778508013 84
1778508018 82
1778508023 82
1778508028 82
1778508033 82
1778508038 82
1778508043 82
1778508048 82
1778508053 82
1778508058 82
1778508063 82
1778508068 82
1778508073 82
1778508078 82
1778508083 82
1778508088 82
1778508093 85
```
</details>

---

