---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 12:45:15 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 12 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777394307 64
1777394312 64
1777394317 64
1777394322 64
1777394327 64
1777394332 64
1777394337 64
1777394342 64
1777394347 64
1777394352 64
1777394357 64
1777394362 64
1777394367 64
1777394372 64
1777394377 64
1777394382 64
1777394387 64
1777394392 64
1777394397 64
1777394402 64
```
</details>

---

