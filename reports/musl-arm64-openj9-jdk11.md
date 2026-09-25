---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 07:37:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 10-18 cores)</summary>

```
1790335974 18
1790335979 18
1790335984 18
1790335989 18
1790335994 18
1790335999 18
1790336004 18
1790336009 18
1790336014 18
1790336019 18
1790336024 18
1790336029 18
1790336034 18
1790336039 18
1790336044 18
1790336049 10
1790336054 10
1790336059 10
1790336064 10
1790336069 10
```
</details>

---

