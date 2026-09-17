---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 15:36:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 841 |
| Sample Rate | 14.02/sec |
| Health Score | 876% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 35-60 cores)</summary>

```
1789673434 60
1789673439 40
1789673444 40
1789673449 40
1789673454 40
1789673459 40
1789673464 40
1789673469 35
1789673474 35
1789673479 35
1789673484 35
1789673489 35
1789673494 35
1789673499 35
1789673504 35
1789673509 35
1789673514 35
1789673519 35
1789673524 35
1789673529 35
```
</details>

---

