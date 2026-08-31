---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-30 21:21:12 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 990 |
| Sample Rate | 16.50/sec |
| Health Score | 1031% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788138979 43
1788138984 43
1788138989 43
1788138994 43
1788138999 43
1788139004 43
1788139009 43
1788139014 48
1788139019 48
1788139024 48
1788139029 48
1788139034 48
1788139039 48
1788139044 48
1788139049 48
1788139054 48
1788139059 48
1788139064 48
1788139069 48
1788139074 48
```
</details>

---

