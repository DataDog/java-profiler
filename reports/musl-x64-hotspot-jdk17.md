---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-28 12:45:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 950 |
| Sample Rate | 15.83/sec |
| Health Score | 989% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 45-60 cores)</summary>

```
1777394297 45
1777394302 45
1777394307 60
1777394312 60
1777394317 45
1777394322 45
1777394327 45
1777394332 45
1777394337 45
1777394342 45
1777394347 45
1777394352 45
1777394357 45
1777394362 45
1777394367 45
1777394372 45
1777394377 45
1777394382 45
1777394387 45
1777394392 45
```
</details>

---

