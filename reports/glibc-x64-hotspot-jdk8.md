---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-15 05:47:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 39-76 cores)</summary>

```
1786786949 39
1786786954 39
1786786959 39
1786786964 39
1786786969 41
1786786974 41
1786786979 41
1786786984 41
1786786989 41
1786786994 41
1786786999 61
1786787004 61
1786787009 76
1786787014 76
1786787019 76
1786787024 76
1786787029 76
1786787034 76
1786787039 76
1786787044 76
```
</details>

---

