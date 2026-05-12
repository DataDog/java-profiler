---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:42:59 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 40-51 cores)</summary>

```
1778582339 40
1778582344 40
1778582349 40
1778582354 40
1778582359 40
1778582364 40
1778582369 40
1778582374 40
1778582379 51
1778582384 51
1778582389 51
1778582394 51
1778582399 51
1778582404 51
1778582409 51
1778582414 51
1778582419 51
1778582424 51
1778582429 51
1778582434 51
```
</details>

---

