---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 10:21:29 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795447001 64
1795447006 64
1795447011 64
1795447016 64
1795447021 64
1795447026 64
1795447031 64
1795447036 64
1795447041 64
1795447046 64
1795447051 64
1795447056 59
1795447061 59
1795447066 59
1795447071 59
1795447076 59
1795447081 59
1795447086 59
1795447091 59
1795447096 59
```
</details>

---

