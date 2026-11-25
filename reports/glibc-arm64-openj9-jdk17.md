---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:01:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1795625818 16
1795625823 16
1795625828 16
1795625833 16
1795625838 16
1795625843 16
1795625848 16
1795625853 16
1795625858 16
1795625863 16
1795625868 16
1795625873 16
1795625878 16
1795625883 16
1795625888 16
1795625893 16
1795625898 16
1795625903 16
1795625908 16
1795625913 16
```
</details>

---

