---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 11:44:55 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 13 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (4 unique values: 36-51 cores)</summary>

```
1794588044 51
1794588049 51
1794588054 51
1794588059 51
1794588064 51
1794588069 51
1794588074 46
1794588079 46
1794588084 41
1794588089 41
1794588094 41
1794588099 41
1794588104 41
1794588109 41
1794588114 41
1794588119 41
1794588124 36
1794588130 36
1794588135 36
1794588140 36
```
</details>

---

