---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-14 08:29:03 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 8 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 13 |
| Allocations | 145 |

<details>
<summary>CPU Timeline (2 unique values: 39-48 cores)</summary>

```
1786710287 48
1786710292 48
1786710297 48
1786710302 48
1786710307 48
1786710312 48
1786710317 48
1786710322 48
1786710327 48
1786710332 48
1786710337 39
1786710342 39
1786710347 39
1786710352 39
1786710357 39
1786710362 39
1786710367 39
1786710372 39
1786710377 39
1786710382 39
```
</details>

---

