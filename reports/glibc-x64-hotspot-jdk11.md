---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-06 09:39:27 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 911 |
| Sample Rate | 15.18/sec |
| Health Score | 949% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1770388402 31
1770388407 31
1770388412 31
1770388417 31
1770388422 31
1770388427 31
1770388432 32
1770388437 32
1770388442 32
1770388447 32
1770388452 32
1770388457 32
1770388462 32
1770388467 32
1770388472 32
1770388477 32
1770388482 32
1770388487 32
1770388492 32
1770388497 32
```
</details>

---

