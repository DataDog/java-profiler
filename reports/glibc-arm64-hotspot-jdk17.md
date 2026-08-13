---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-13 04:53:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786610875 48
1786610880 48
1786610885 48
1786610890 48
1786610895 48
1786610900 48
1786610905 48
1786610910 48
1786610915 48
1786610920 48
1786610925 48
1786610930 48
1786610935 43
1786610940 43
1786610945 43
1786610950 43
1786610955 43
1786610960 43
1786610965 43
1786610970 43
```
</details>

---

