---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-05 08:26:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 14-64 cores)</summary>

```
1785932432 14
1785932437 14
1785932442 14
1785932447 14
1785932452 14
1785932457 14
1785932462 14
1785932467 14
1785932472 14
1785932477 44
1785932482 44
1785932487 44
1785932492 44
1785932497 44
1785932502 44
1785932507 64
1785932512 64
1785932517 64
1785932522 64
1785932527 64
```
</details>

---

