---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 05:55:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 216 |
| Sample Rate | 3.60/sec |
| Health Score | 225% |
| Threads | 10 |
| Allocations | 137 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1791539311 35
1791539316 35
1791539321 35
1791539326 35
1791539331 35
1791539336 35
1791539341 35
1791539346 35
1791539351 35
1791539356 35
1791539362 35
1791539367 40
1791539372 40
1791539377 40
1791539382 40
1791539387 40
1791539392 40
1791539397 40
1791539402 40
1791539407 40
```
</details>

---

