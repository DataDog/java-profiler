---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 09:20:16 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (5 unique values: 56-75 cores)</summary>

```
1791465214 56
1791465220 56
1791465225 56
1791465230 56
1791465235 61
1791465240 61
1791465245 61
1791465250 61
1791465255 61
1791465260 59
1791465265 59
1791465270 73
1791465275 73
1791465280 73
1791465285 73
1791465290 73
1791465295 73
1791465300 73
1791465305 73
1791465310 73
```
</details>

---

