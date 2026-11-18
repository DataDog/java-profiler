---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 08:22:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1795007896 72
1795007901 72
1795007906 72
1795007911 72
1795007916 72
1795007921 72
1795007926 70
1795007931 70
1795007936 70
1795007941 70
1795007946 70
1795007951 70
1795007956 70
1795007961 70
1795007966 70
1795007971 70
1795007976 72
1795007981 72
1795007986 72
1795007991 72
```
</details>

---

