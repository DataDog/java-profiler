---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 05:49:18 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 36-68 cores)</summary>

```
1786441467 36
1786441472 36
1786441477 36
1786441482 36
1786441487 36
1786441492 36
1786441497 36
1786441502 36
1786441507 36
1786441512 36
1786441517 36
1786441522 36
1786441527 36
1786441532 36
1786441537 36
1786441542 36
1786441547 36
1786441552 68
1786441557 68
1786441562 68
```
</details>

---

