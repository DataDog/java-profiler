---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:53:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 46-51 cores)</summary>

```
1794498361 46
1794498366 46
1794498371 46
1794498376 46
1794498381 46
1794498386 46
1794498391 46
1794498396 46
1794498401 46
1794498406 46
1794498411 46
1794498416 46
1794498421 49
1794498426 49
1794498431 51
1794498436 51
1794498441 51
1794498446 51
1794498451 51
1794498456 51
```
</details>

---

