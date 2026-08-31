---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-30 21:21:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 12 |
| Allocations | 82 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788138994 43
1788138999 43
1788139004 43
1788139009 43
1788139014 43
1788139019 43
1788139024 43
1788139029 43
1788139034 43
1788139039 43
1788139044 43
1788139049 43
1788139054 43
1788139059 43
1788139064 48
1788139069 48
1788139074 48
1788139079 48
1788139084 48
1788139089 48
```
</details>

---

