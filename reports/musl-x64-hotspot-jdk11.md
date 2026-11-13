---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:36:51 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
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
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1794569540 91
1794569545 91
1794569550 91
1794569555 91
1794569560 91
1794569565 91
1794569570 91
1794569575 91
1794569580 91
1794569585 91
1794569590 91
1794569595 91
1794569600 89
1794569605 89
1794569610 89
1794569615 89
1794569620 89
1794569625 89
1794569630 89
1794569635 89
```
</details>

---

