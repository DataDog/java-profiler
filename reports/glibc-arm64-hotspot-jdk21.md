---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-03 04:34:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1791016268 27
1791016273 27
1791016278 27
1791016283 27
1791016288 27
1791016293 27
1791016298 27
1791016303 27
1791016308 27
1791016313 27
1791016318 27
1791016323 27
1791016328 32
1791016333 32
1791016338 32
1791016343 32
1791016348 32
1791016353 32
1791016358 32
1791016363 32
```
</details>

---

