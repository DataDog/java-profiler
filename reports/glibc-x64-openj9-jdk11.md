---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 14:12:55 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1790618909 56
1790618914 56
1790618919 56
1790618924 58
1790618929 58
1790618934 58
1790618939 58
1790618944 58
1790618949 58
1790618954 58
1790618959 58
1790618964 58
1790618969 58
1790618974 58
1790618979 58
1790618984 58
1790618989 58
1790618994 58
1790618999 58
1790619004 58
```
</details>

---

