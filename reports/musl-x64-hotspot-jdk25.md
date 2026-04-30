---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-30 05:30:10 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (6 unique values: 21-29 cores)</summary>

```
1777541131 21
1777541136 21
1777541141 24
1777541146 24
1777541151 24
1777541156 24
1777541161 23
1777541166 23
1777541171 22
1777541176 22
1777541181 23
1777541186 23
1777541191 25
1777541196 25
1777541201 29
1777541206 29
1777541211 29
1777541216 29
1777541221 29
1777541226 29
```
</details>

---

