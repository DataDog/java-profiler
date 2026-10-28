---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 12:39:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 10 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 72-80 cores)</summary>

```
1793205318 75
1793205323 75
1793205328 75
1793205333 75
1793205338 75
1793205343 75
1793205348 75
1793205353 75
1793205358 75
1793205363 75
1793205368 72
1793205373 72
1793205378 72
1793205383 72
1793205388 72
1793205393 72
1793205398 72
1793205403 72
1793205408 72
1793205413 72
```
</details>

---

