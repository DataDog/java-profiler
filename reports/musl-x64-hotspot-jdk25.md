---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 12:37:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (6 unique values: 42-75 cores)</summary>

```
1794850060 42
1794850065 42
1794850070 43
1794850075 43
1794850080 53
1794850085 53
1794850090 75
1794850095 75
1794850100 73
1794850105 73
1794850110 73
1794850115 73
1794850120 73
1794850125 73
1794850130 73
1794850135 71
1794850140 71
1794850145 71
1794850150 71
1794850155 71
```
</details>

---

