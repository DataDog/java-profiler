---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 06:36:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1794569544 28
1794569549 28
1794569555 30
1794569560 30
1794569565 30
1794569570 30
1794569575 30
1794569580 30
1794569585 30
1794569590 30
1794569595 30
1794569600 30
1794569605 30
1794569610 30
1794569615 30
1794569620 30
1794569625 30
1794569630 30
1794569635 30
1794569640 30
```
</details>

---

