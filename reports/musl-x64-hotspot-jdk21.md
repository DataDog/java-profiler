---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:21:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 10 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (2 unique values: 21-56 cores)</summary>

```
1789730246 56
1789730251 56
1789730256 56
1789730261 56
1789730266 56
1789730271 56
1789730276 56
1789730281 56
1789730286 56
1789730291 56
1789730296 56
1789730301 56
1789730306 21
1789730311 21
1789730316 21
1789730321 21
1789730326 21
1789730331 21
1789730336 21
1789730341 21
```
</details>

---

