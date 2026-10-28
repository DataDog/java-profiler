---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 12:39:36 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793205304 30
1793205309 30
1793205314 30
1793205319 30
1793205324 30
1793205329 30
1793205334 30
1793205339 32
1793205344 32
1793205349 32
1793205354 32
1793205359 30
1793205364 30
1793205369 30
1793205374 30
1793205379 30
1793205384 30
1793205389 30
1793205394 30
1793205399 30
```
</details>

---

