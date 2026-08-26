---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-26 06:37:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 281 |
| Sample Rate | 4.68/sec |
| Health Score | 292% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 221 |
| Sample Rate | 3.68/sec |
| Health Score | 230% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 44-54 cores)</summary>

```
1787740366 54
1787740371 54
1787740376 54
1787740381 54
1787740386 54
1787740391 54
1787740396 54
1787740401 54
1787740406 54
1787740411 54
1787740416 44
1787740421 44
1787740426 44
1787740431 44
1787740436 44
1787740441 44
1787740446 44
1787740451 44
1787740457 44
1787740462 44
```
</details>

---

