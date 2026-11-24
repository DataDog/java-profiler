---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 13:41:38 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 55-67 cores)</summary>

```
1795545452 55
1795545457 55
1795545462 55
1795545467 55
1795545472 55
1795545477 55
1795545482 55
1795545487 55
1795545492 55
1795545497 55
1795545502 55
1795545507 55
1795545512 55
1795545517 55
1795545522 57
1795545527 57
1795545532 57
1795545537 67
1795545542 67
1795545547 67
```
</details>

---

