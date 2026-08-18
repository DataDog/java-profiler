---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-18 05:49:27 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 12 |
| Allocations | 101 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1787046242 32
1787046247 27
1787046252 27
1787046257 27
1787046262 27
1787046267 27
1787046272 27
1787046277 27
1787046282 27
1787046287 27
1787046292 27
1787046297 27
1787046302 27
1787046307 27
1787046312 27
1787046317 27
1787046322 27
1787046327 27
1787046332 27
1787046337 27
```
</details>

---

