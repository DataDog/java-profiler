---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 14:37:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 14 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 31-44 cores)</summary>

```
1786386821 31
1786386826 31
1786386831 31
1786386836 31
1786386841 31
1786386846 44
1786386851 44
1786386856 44
1786386861 44
1786386866 44
1786386871 44
1786386876 44
1786386881 44
1786386886 44
1786386891 44
1786386896 44
1786386901 44
1786386906 44
1786386911 44
1786386916 44
```
</details>

---

