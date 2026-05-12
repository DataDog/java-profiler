---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 05:19:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 46-55 cores)</summary>

```
1778577327 51
1778577332 51
1778577337 51
1778577342 51
1778577347 51
1778577352 51
1778577357 51
1778577362 51
1778577367 51
1778577372 51
1778577377 51
1778577382 51
1778577387 51
1778577392 51
1778577397 51
1778577402 51
1778577407 55
1778577412 55
1778577417 51
1778577422 51
```
</details>

---

