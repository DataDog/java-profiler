---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-30 05:30:10 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 818 |
| Sample Rate | 13.63/sec |
| Health Score | 852% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (4 unique values: 71-92 cores)</summary>

```
1777541135 75
1777541140 75
1777541145 71
1777541150 71
1777541155 92
1777541160 92
1777541165 92
1777541171 92
1777541176 92
1777541181 92
1777541186 92
1777541191 92
1777541196 92
1777541201 92
1777541206 83
1777541211 83
1777541216 83
1777541221 83
1777541226 83
1777541231 83
```
</details>

---

