---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-01 08:19:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 8 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1790856894 11
1790856899 11
1790856904 11
1790856909 11
1790856914 11
1790856919 11
1790856924 11
1790856929 32
1790856934 32
1790856939 32
1790856944 32
1790856949 32
1790856954 32
1790856959 32
1790856964 32
1790856969 32
1790856974 32
1790856979 32
1790856984 32
1790856989 32
```
</details>

---

