---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-12 04:43:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 11 |
| Allocations | 90 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 41 |
| Sample Rate | 0.68/sec |
| Health Score | 42% |
| Threads | 13 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 54-64 cores)</summary>

```
1791794306 54
1791794311 54
1791794316 54
1791794321 54
1791794326 54
1791794331 54
1791794336 54
1791794341 54
1791794346 54
1791794351 54
1791794356 54
1791794361 54
1791794366 54
1791794371 54
1791794376 54
1791794381 54
1791794386 54
1791794391 54
1791794396 64
1791794401 64
```
</details>

---

