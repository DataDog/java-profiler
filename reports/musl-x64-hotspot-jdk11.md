---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-07 08:18:44 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 81-86 cores)</summary>

```
1791375224 81
1791375229 81
1791375234 81
1791375239 81
1791375244 81
1791375249 86
1791375254 86
1791375259 86
1791375264 86
1791375269 86
1791375274 86
1791375279 86
1791375284 86
1791375289 86
1791375294 86
1791375299 84
1791375304 84
1791375309 82
1791375314 82
1791375319 82
```
</details>

---

