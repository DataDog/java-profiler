---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 08:19:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 887 |
| Sample Rate | 14.78/sec |
| Health Score | 924% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 30-33 cores)</summary>

```
1790856899 33
1790856904 33
1790856909 33
1790856914 33
1790856919 33
1790856924 33
1790856929 33
1790856934 33
1790856939 33
1790856944 30
1790856949 30
1790856954 30
1790856959 30
1790856964 30
1790856969 30
1790856974 30
1790856979 30
1790856984 30
1790856989 30
1790856994 30
```
</details>

---

