---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 10:51:20 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 10 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (6 unique values: 53-79 cores)</summary>

```
1790865896 55
1790865901 55
1790865906 55
1790865911 55
1790865916 55
1790865921 55
1790865926 55
1790865931 53
1790865936 53
1790865941 79
1790865946 79
1790865951 79
1790865956 56
1790865961 56
1790865966 56
1790865971 56
1790865976 56
1790865981 56
1790865986 58
1790865991 58
```
</details>

---

