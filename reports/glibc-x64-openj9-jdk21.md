---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 08:22:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 58-67 cores)</summary>

```
1795007921 67
1795007926 67
1795007931 67
1795007936 67
1795007941 67
1795007946 67
1795007951 58
1795007956 58
1795007961 58
1795007966 58
1795007971 58
1795007976 58
1795007981 58
1795007986 58
1795007991 58
1795007996 58
1795008001 58
1795008006 58
1795008011 58
1795008016 58
```
</details>

---

