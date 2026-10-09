---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-09 05:55:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 10 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (7 unique values: 35-48 cores)</summary>

```
1791539309 43
1791539314 43
1791539319 43
1791539324 48
1791539329 48
1791539334 48
1791539339 38
1791539344 38
1791539349 38
1791539354 38
1791539359 38
1791539364 38
1791539369 38
1791539374 38
1791539379 38
1791539384 38
1791539389 35
1791539394 35
1791539399 35
1791539404 35
```
</details>

---

