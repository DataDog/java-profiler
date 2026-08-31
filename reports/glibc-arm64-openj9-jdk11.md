---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-30 21:21:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (4 unique values: 14-34 cores)</summary>

```
1788139019 14
1788139024 14
1788139029 14
1788139034 14
1788139039 14
1788139044 14
1788139049 14
1788139054 14
1788139059 14
1788139064 14
1788139069 14
1788139074 14
1788139079 14
1788139084 14
1788139089 14
1788139094 14
1788139099 14
1788139104 14
1788139109 34
1788139114 34
```
</details>

---

