---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 08:19:05 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 61-89 cores)</summary>

```
1790856899 89
1790856904 89
1790856909 89
1790856914 89
1790856919 80
1790856924 80
1790856929 80
1790856934 80
1790856939 78
1790856944 78
1790856949 78
1790856954 78
1790856959 78
1790856964 78
1790856969 78
1790856974 78
1790856979 78
1790856984 78
1790856989 78
1790856994 78
```
</details>

---

