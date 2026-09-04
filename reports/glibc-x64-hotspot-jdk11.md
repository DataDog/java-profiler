---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-04 14:55:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 11-17 cores)</summary>

```
1788547924 15
1788547929 17
1788547934 17
1788547939 15
1788547944 15
1788547949 15
1788547954 15
1788547959 15
1788547964 15
1788547969 17
1788547974 17
1788547979 17
1788547984 17
1788547989 17
1788547994 17
1788547999 17
1788548004 17
1788548009 17
1788548014 17
1788548019 15
```
</details>

---

