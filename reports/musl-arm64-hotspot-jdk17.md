---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 05:55:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 31-64 cores)</summary>

```
1791539329 31
1791539334 31
1791539339 31
1791539344 31
1791539349 31
1791539354 31
1791539359 31
1791539364 31
1791539369 31
1791539374 31
1791539379 64
1791539384 64
1791539389 64
1791539394 64
1791539399 64
1791539404 64
1791539409 64
1791539414 64
1791539419 64
1791539424 64
```
</details>

---

