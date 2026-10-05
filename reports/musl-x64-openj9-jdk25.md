---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-05 16:36:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (5 unique values: 74-86 cores)</summary>

```
1791232291 84
1791232296 84
1791232301 84
1791232306 84
1791232311 86
1791232316 86
1791232321 86
1791232326 86
1791232331 86
1791232336 86
1791232341 86
1791232346 86
1791232351 86
1791232356 78
1791232361 78
1791232366 78
1791232371 78
1791232376 78
1791232381 78
1791232386 78
```
</details>

---

