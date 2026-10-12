---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-12 04:43:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 14 |
| Allocations | 67 |

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

